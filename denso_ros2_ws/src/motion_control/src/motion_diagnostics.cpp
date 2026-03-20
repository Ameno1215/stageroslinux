#include "motion_control/motion_diagnostics.hpp"



namespace motion_control
{
    std::string DiagnosticReport::causeToString(Cause c)
    {
        switch (c) {
            case Cause::UNKNOWN:              return "UNKNOWN";
            case Cause::START_COLLISION:       return "START_STATE_IN_COLLISION";
            case Cause::GOAL_COLLISION:        return "GOAL_STATE_IN_COLLISION";
            case Cause::PATH_COLLISION:        return "PATH_COLLISION";
            case Cause::IK_UNREACHABLE:        return "IK_UNREACHABLE";
            case Cause::SINGULARITY:           return "NEAR_SINGULARITY";
            case Cause::JOINT_LIMITS:          return "JOINT_LIMITS_VIOLATED";
            case Cause::TIMEOUT:              return "PLANNING_TIMEOUT";
            case Cause::CONTROL_FAILED:        return "CONTROL_FAILED";
            case Cause::CARTESIAN_INCOMPLETE:  return "CARTESIAN_PATH_INCOMPLETE";
            case Cause::CONSTRAINT_VIOLATION:  return "CONSTRAINT_VIOLATION";
            case Cause::MULTIPLE_CAUSES:       return "MULTIPLE_CAUSES";
            default:                           return "UNKNOWN";
        }
    }

    void DiagnosticReport::buildSummary()
    {
        std::ostringstream oss;

        // Primary cause header
        oss << "[DIAG] Primary cause: " << causeToString(primary_cause);

        if (all_causes.size() > 1) {
            oss << " (+" << (all_causes.size() - 1) << " additional issue(s))";
        }
        oss << "\n";

        // Collision details
        if (start_in_collision) {
            oss << "  - Start state IS in collision.";
            if (!self_collision_pairs.empty()) {
                oss << " Self-collision: ";
                for (size_t i = 0; i < self_collision_pairs.size() && i < 3; ++i) {
                    if (i > 0) oss << ", ";
                    oss << self_collision_pairs[i];
                }
                if (self_collision_pairs.size() > 3) oss << " (+" << (self_collision_pairs.size() - 3) << " more)";
                oss << ".";
            }
            if (!env_collision_pairs.empty()) {
                oss << " Environment: ";
                for (size_t i = 0; i < env_collision_pairs.size() && i < 3; ++i) {
                    if (i > 0) oss << ", ";
                    oss << env_collision_pairs[i];
                }
                if (env_collision_pairs.size() > 3) oss << " (+" << (env_collision_pairs.size() - 3) << " more)";
                oss << ".";
            }
            if (self_collision_pairs.empty() && env_collision_pairs.empty() && !collision_pairs.empty()) {
                // Fallback: show raw pairs if classification wasn't done
                oss << " Pairs: ";
                for (size_t i = 0; i < collision_pairs.size() && i < 5; ++i) {
                    if (i > 0) oss << ", ";
                    oss << collision_pairs[i];
                }
                if (collision_pairs.size() > 5) oss << " (+" << (collision_pairs.size() - 5) << " more)";
            }
            oss << "\n";
        }
        if (goal_in_collision) {
            oss << "  - Goal state IS in collision.\n";
        }

        // IK
        if (ik_failed) {
            oss << "  - IK failed: " << ik_detail << "\n";
        }

        // Singularity
        if (near_singularity) {
            oss << "  - Near singularity at goal. Manipulability=" 
                << manipulability << " (threshold=" << singularity_threshold 
                << "), Jacobian condition=" << condition_number << "\n";
        }

        // Joint limits
        if (joints_out_of_bounds) {
            oss << "  - Joint limits violated: ";
            for (size_t i = 0; i < violating_joints.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << violating_joints[i];
            }
            oss << "\n";
        }

        // Cartesian
        if (cartesian_fraction >= 0.0) {
            oss << "  - Cartesian fraction achieved: " 
                << (cartesian_fraction * 100.0) << "%";
            if (cartesian_fail_waypoint_index >= 0) {
                oss << " (failure near waypoint #" << cartesian_fail_waypoint_index << ")";
            }
            oss << "\n";
        }

        // Timing
        if (planning_duration_s > 0.0) {
            oss << "  - Planning took " << planning_duration_s << "s\n";
        }

        summary = oss.str();
    }

    bool checkStateCollision(
        const planning_scene::PlanningSceneConstPtr& scene,
        const moveit::core::RobotState& state,
        const std::string& group_name,
        std::vector<std::string>& collision_pairs,
        std::vector<std::string>& self_collision_pairs,
        std::vector<std::string>& env_collision_pairs)
    {
        collision_detection::CollisionRequest req;
        req.group_name = group_name;
        req.contacts = true;       // We want to know WHAT is colliding
        req.max_contacts = 10;     // Limit to avoid flooding
        req.verbose = false;       // We extract info ourselves

        collision_detection::CollisionResult result;
        scene->checkCollision(req, result, state);

        collision_pairs.clear();
        self_collision_pairs.clear();
        env_collision_pairs.clear();

        if (result.collision) {
            // Collect all robot link names to distinguish self vs env
            const auto& link_names = state.getRobotModel()->getLinkModelNames();
            std::set<std::string> robot_links(link_names.begin(), link_names.end());

            for (const auto& contact_pair : result.contacts) {
                std::string pair_str = contact_pair.first.first 
                                    + " <-> " 
                                    + contact_pair.first.second;
                collision_pairs.push_back(pair_str);

                // Classify: if both bodies are robot links, it's self-collision
                bool first_is_robot = robot_links.count(contact_pair.first.first) > 0;
                bool second_is_robot = robot_links.count(contact_pair.first.second) > 0;

                if (first_is_robot && second_is_robot) {
                    self_collision_pairs.push_back(pair_str);
                } else {
                    env_collision_pairs.push_back(pair_str);
                }
            }
        }
        return result.collision;
    }

    // TODO CHECK les limites et retrouner une erreur
    std::vector<std::string> checkJointLimits(
        const moveit::core::RobotState& state,
        const std::string& group_name)
    {
        std::vector<std::string> violating;
        const auto* jmg = state.getRobotModel()->getJointModelGroup(group_name);
        if (!jmg) return violating;

        for (const auto* jm : jmg->getActiveJointModels()) {
            // Check each variable of the joint against its bounds
            const auto& bounds = jm->getVariableBounds();
            const auto& names  = jm->getVariableNames();
            for (size_t i = 0; i < names.size(); ++i) {
                double val = state.getVariablePosition(names[i]);
                if (bounds[i].position_bounded_) {
                    if (val < bounds[i].min_position_ || val > bounds[i].max_position_) {
                        std::ostringstream oss;
                        oss << names[i] << "=" << val 
                            << " [" << bounds[i].min_position_ 
                            << ", " << bounds[i].max_position_ << "]";
                        violating.push_back(oss.str());
                    }
                }
            }
        }
        return violating;
    }

    SingularityMetrics computeSingularityMetrics(
        const moveit::core::RobotState& state,
        const moveit::core::JointModelGroup* jmg,
        double threshold)
    {
        SingularityMetrics metrics;
        metrics.manipulability = 0.0;
        metrics.condition_number = std::numeric_limits<double>::infinity();
        metrics.is_singular = true;

        if (!jmg) return metrics;

        // Get the Jacobian at the current state for the tip link of the group
        Eigen::Vector3d reference_point(0.0, 0.0, 0.0);
        Eigen::MatrixXd jacobian;

        // getJacobian() returns the geometric Jacobian (6 x n_joints)
        if (!state.getJacobian(jmg, jmg->getLinkModels().back(), reference_point, jacobian)) {
            // Failed to compute Jacobian — treat as singular
            return metrics;
        }

        // SVD decomposition to get singular values
        Eigen::JacobiSVD<Eigen::MatrixXd> svd(jacobian);
        Eigen::VectorXd sv = svd.singularValues();

        if (sv.size() == 0) return metrics;

        double sigma_min = sv(sv.size() - 1);
        double sigma_max = sv(0);

        // Yoshikawa manipulability: sqrt(det(J * J^T))
        // Equivalent to product of singular values
        metrics.manipulability = 1.0;
        for (int i = 0; i < sv.size(); ++i) {
            metrics.manipulability *= sv(i);
        }

        // Condition number: sigma_max / sigma_min
        if (sigma_min > 1e-12) {
            metrics.condition_number = sigma_max / sigma_min;
        } else {
            metrics.condition_number = std::numeric_limits<double>::infinity();
        }

        metrics.is_singular = (metrics.manipulability < threshold);
        return metrics;
    }

    DiagnosticReport diagnosePlanningFailure(
        const moveit::core::MoveItErrorCode& error_code,
        const moveit::planning_interface::MoveGroupInterface& move_group,
        const planning_scene::PlanningSceneConstPtr& scene,
        const std::string& group_name,
        const geometry_msgs::msg::Pose* goal_pose,
        const std::vector<double>* goal_joints,
        double planning_duration_s,
        const rclcpp::Logger& logger)
    {
        DiagnosticReport report;
        report.planning_duration_s = planning_duration_s;

        const auto* jmg = move_group.getRobotModel()->getJointModelGroup(group_name);
        if (!jmg) {
            report.primary_cause = DiagnosticReport::Cause::UNKNOWN;
            report.summary = "[DIAG] Cannot diagnose: joint model group '" + group_name + "' not found.";
            return report;
        }

        // 1. Check start state for collision
        moveit::core::RobotStatePtr start_state = move_group.getCurrentState();
        if (start_state) {
            std::vector<std::string> pairs, self_pairs, env_pairs;
            if (checkStateCollision(scene, *start_state, group_name, pairs, self_pairs, env_pairs)) {
                report.start_in_collision = true;
                report.collision_pairs = pairs;
                report.self_collision_pairs = self_pairs;
                report.env_collision_pairs = env_pairs;
                report.all_causes.push_back(DiagnosticReport::Cause::START_COLLISION);
                // RCLCPP_WARN(logger, "[DIAG] Start state is in collision with %zu contact pair(s) "
                //             "(%zu self-collision, %zu environment)",
                //             pairs.size(), self_pairs.size(), env_pairs.size());
            }

            // Also check joint limits on the current state
            auto violations = checkJointLimits(*start_state, group_name);
            if (!violations.empty()) {
                RCLCPP_WARN(logger, "[DIAG] Start state has %zu joint(s) out of bounds", violations.size());
            }
        }

        // 2. Construct a goal state and check it
        moveit::core::RobotState goal_state(move_group.getRobotModel());
        bool goal_state_valid = false;

        if (goal_joints && !goal_joints->empty()) {
            // Joint-space goal: directly set joint values
            goal_state.setJointGroupPositions(jmg, *goal_joints);
            goal_state.update();
            goal_state_valid = true;
        }
        else if (goal_pose) {
            // Cartesian goal: attempt IK to get a joint-space representation
            bool ik_ok = goal_state.setFromIK(jmg, *goal_pose, 0.1 /* timeout */);
            if (!ik_ok) {
                report.ik_failed = true;
                report.ik_detail = "IK solver returned no solution for the target pose. "
                                "The pose may be outside the workspace or near a singularity.";
                report.all_causes.push_back(DiagnosticReport::Cause::IK_UNREACHABLE);
                // RCLCPP_WARN(logger, "[DIAG] IK failed for goal pose — unreachable or singular");
            } else {
                goal_state_valid = true;
            }
        }

        if (goal_state_valid) {
            // 2a. Collision check on goal state
            std::vector<std::string> goal_pairs, goal_self, goal_env;
            if (checkStateCollision(scene, goal_state, group_name, goal_pairs, goal_self, goal_env)) {
                report.goal_in_collision = true;
                if (report.collision_pairs.empty()) {
                    report.collision_pairs = goal_pairs;
                    report.self_collision_pairs = goal_self;
                    report.env_collision_pairs = goal_env;
                } else {
                    report.collision_pairs.insert(
                        report.collision_pairs.end(), goal_pairs.begin(), goal_pairs.end());
                    report.self_collision_pairs.insert(
                        report.self_collision_pairs.end(), goal_self.begin(), goal_self.end());
                    report.env_collision_pairs.insert(
                        report.env_collision_pairs.end(), goal_env.begin(), goal_env.end());
                }
                report.all_causes.push_back(DiagnosticReport::Cause::GOAL_COLLISION);
                // RCLCPP_WARN(logger, "[DIAG] Goal state is in collision with %zu pair(s) "
                //             "(%zu self, %zu env)", goal_pairs.size(), goal_self.size(), goal_env.size());
            }

            // 2b. Joint limits on goal state
            auto goal_violations = checkJointLimits(goal_state, group_name);
            if (!goal_violations.empty()) {
                report.joints_out_of_bounds = true;
                report.violating_joints = goal_violations;
                report.all_causes.push_back(DiagnosticReport::Cause::JOINT_LIMITS);
                // RCLCPP_WARN(logger, "[DIAG] Goal state violates joint limits on %zu joint(s)",
                //             goal_violations.size());
            }

            // 2c. Singularity check at goal state
            auto sing = computeSingularityMetrics(goal_state, jmg);
            report.manipulability = sing.manipulability;
            report.condition_number = sing.condition_number;
            if (sing.is_singular) {
                report.near_singularity = true;
                report.all_causes.push_back(DiagnosticReport::Cause::SINGULARITY);
                // RCLCPP_WARN(logger,
                //     "[DIAG] Goal is near singularity: manipulability=%.6f, condition=%.1f",
                //     sing.manipulability, sing.condition_number);
            } else {
                RCLCPP_DEBUG(logger,
                    "[DIAG] Singularity OK: manipulability=%.6f, condition=%.1f",
                    sing.manipulability, sing.condition_number);
            }
        }

        // 3. Check for timeout
        if (error_code.val == moveit_msgs::msg::MoveItErrorCodes::TIMED_OUT) {
            report.all_causes.push_back(DiagnosticReport::Cause::TIMEOUT);
        }

        // 4. Determine primary cause
        if (report.all_causes.empty()) {
            report.primary_cause = DiagnosticReport::Cause::UNKNOWN;
        } else if (report.all_causes.size() == 1) {
            report.primary_cause = report.all_causes[0];
        } else {
            // Priority order: collision > IK > singularity > limits > timeout
            // Pick the most actionable one
            report.primary_cause = DiagnosticReport::Cause::MULTIPLE_CAUSES;
            for (auto c : {DiagnosticReport::Cause::START_COLLISION,
                        DiagnosticReport::Cause::GOAL_COLLISION,
                        DiagnosticReport::Cause::IK_UNREACHABLE,
                        DiagnosticReport::Cause::SINGULARITY,
                        DiagnosticReport::Cause::JOINT_LIMITS,
                        DiagnosticReport::Cause::TIMEOUT}) {
                if (std::find(report.all_causes.begin(), report.all_causes.end(), c)
                    != report.all_causes.end()) {
                    report.primary_cause = c;
                    break;
                }
            }
        }

        report.buildSummary();
        RCLCPP_WARN(logger, "%s", report.summary.c_str());
        return report;
    }

    DiagnosticReport diagnoseCartesianFailure(
        const moveit::planning_interface::MoveGroupInterface& move_group,
        const planning_scene::PlanningSceneConstPtr& scene,
        const std::string& group_name,
        const std::vector<geometry_msgs::msg::Pose>& waypoints,
        double achieved_fraction,
        double planning_duration_s,
        const rclcpp::Logger& logger)
    {
        DiagnosticReport report;
        report.planning_duration_s = planning_duration_s;
        report.cartesian_fraction = achieved_fraction;

        const auto* jmg = move_group.getRobotModel()->getJointModelGroup(group_name);
        if (!jmg || waypoints.empty()) {
            report.primary_cause = DiagnosticReport::Cause::UNKNOWN;
            report.summary = "[DIAG] Cannot diagnose Cartesian failure: no waypoints or invalid group.";
            return report;
        }

        // 1. Check start state
        moveit::core::RobotStatePtr current = move_group.getCurrentState();
        if (current) {
            std::vector<std::string> pairs, self_pairs, env_pairs;
            if (checkStateCollision(scene, *current, group_name, pairs, self_pairs, env_pairs)) {
                report.start_in_collision = true;
                report.collision_pairs = pairs;
                report.self_collision_pairs = self_pairs;
                report.env_collision_pairs = env_pairs;
                report.all_causes.push_back(DiagnosticReport::Cause::START_COLLISION);
                RCLCPP_WARN(logger, "[DIAG-CART] Start state is in collision "
                            "(%zu self, %zu env)", self_pairs.size(), env_pairs.size());
            }
        }

        // 2. Walk through each waypoint: attempt IK, check collision & singularity
        //    This tells us WHERE and WHY the Cartesian path breaks.
        moveit::core::RobotState probe_state(move_group.getRobotModel());
        if (current) {
            probe_state = *current;
        }

        for (size_t i = 0; i < waypoints.size(); ++i) {
            // Try IK at this waypoint
            bool ik_ok = probe_state.setFromIK(jmg, waypoints[i], 0.1);

            if (!ik_ok) {
                report.ik_failed = true;
                report.cartesian_fail_waypoint_index = static_cast<int>(i);
                report.cartesian_fail_pose = waypoints[i];

                std::ostringstream oss;
                oss << "IK failed at waypoint #" << i
                    << " (pose: x=" << waypoints[i].position.x
                    << " y=" << waypoints[i].position.y
                    << " z=" << waypoints[i].position.z << ")";
                report.ik_detail = oss.str();
                report.all_causes.push_back(DiagnosticReport::Cause::IK_UNREACHABLE);
                RCLCPP_WARN(logger, "[DIAG-CART] %s", report.ik_detail.c_str());
                break;  // No point checking further waypoints
            }

            probe_state.update();

            // Collision check at this waypoint
            std::vector<std::string> wp_pairs, wp_self, wp_env;
            if (checkStateCollision(scene, probe_state, group_name, wp_pairs, wp_self, wp_env)) {
                report.goal_in_collision = true;
                report.cartesian_fail_waypoint_index = static_cast<int>(i);
                report.cartesian_fail_pose = waypoints[i];
                report.collision_pairs = wp_pairs;
                report.self_collision_pairs = wp_self;
                report.env_collision_pairs = wp_env;
                report.all_causes.push_back(DiagnosticReport::Cause::PATH_COLLISION);
                RCLCPP_WARN(logger,
                    "[DIAG-CART] Collision at waypoint #%zu: %zu pair(s) (%zu self, %zu env)",
                    i, wp_pairs.size(), wp_self.size(), wp_env.size());
                break;
            }

            // Singularity check at this waypoint
            auto sing = computeSingularityMetrics(probe_state, jmg);
            if (sing.is_singular) {
                report.near_singularity = true;
                report.manipulability = sing.manipulability;
                report.condition_number = sing.condition_number;
                report.cartesian_fail_waypoint_index = static_cast<int>(i);
                report.cartesian_fail_pose = waypoints[i];
                report.all_causes.push_back(DiagnosticReport::Cause::SINGULARITY);
                RCLCPP_WARN(logger,
                    "[DIAG-CART] Near singularity at waypoint #%zu: manipulability=%.6f",
                    i, sing.manipulability);
                // Don't break — singularity might not be the sole cause
            }
        }

        // 3. If no specific cause found, it's likely an interpolation issue
        //    (the path between waypoints crosses a collision/singularity)
        if (report.all_causes.empty()) {
            report.all_causes.push_back(DiagnosticReport::Cause::CARTESIAN_INCOMPLETE);
            RCLCPP_WARN(logger,
                "[DIAG-CART] All waypoints seem individually reachable. "
                "The interpolated path between them likely crosses a collision zone, "
                "singularity, or joint-limit boundary. Fraction=%.1f%%",
                achieved_fraction * 100.0);
        }

        // 4. Primary cause determination
        if (report.all_causes.size() == 1) {
            report.primary_cause = report.all_causes[0];
        } else {
            report.primary_cause = DiagnosticReport::Cause::MULTIPLE_CAUSES;
            for (auto c : {DiagnosticReport::Cause::START_COLLISION,
                        DiagnosticReport::Cause::PATH_COLLISION,
                        DiagnosticReport::Cause::IK_UNREACHABLE,
                        DiagnosticReport::Cause::SINGULARITY,
                        DiagnosticReport::Cause::CARTESIAN_INCOMPLETE}) {
                if (std::find(report.all_causes.begin(), report.all_causes.end(), c)
                    != report.all_causes.end()) {
                    report.primary_cause = c;
                    break;
                }
            }
        }

        report.buildSummary();
        RCLCPP_WARN(logger, "%s", report.summary.c_str());
        return report;
    }

}  // namespace motion_control
