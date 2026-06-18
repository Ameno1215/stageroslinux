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

    std::string moveitErrorCodeToString(const moveit::core::MoveItErrorCode& code)
    {
        switch (code.val) {
            case moveit::core::MoveItErrorCode::SUCCESS: return "SUCCESS";
            case moveit::core::MoveItErrorCode::FAILURE: return "FAILURE";
            case moveit::core::MoveItErrorCode::PLANNING_FAILED: return "PLANNING_FAILED";
            case moveit::core::MoveItErrorCode::INVALID_MOTION_PLAN: return "INVALID_MOTION_PLAN";
            case moveit::core::MoveItErrorCode::MOTION_PLAN_INVALIDATED_BY_ENVIRONMENT_CHANGE: return "PLAN_INVALIDATED";
            case moveit::core::MoveItErrorCode::CONTROL_FAILED: return "CONTROL_FAILED";
            case moveit::core::MoveItErrorCode::TIMED_OUT: return "TIMED_OUT";
            case moveit::core::MoveItErrorCode::PREEMPTED: return "PREEMPTED";
            case moveit::core::MoveItErrorCode::NO_IK_SOLUTION: return "NO_IK_SOLUTION";
            case moveit::core::MoveItErrorCode::INVALID_OBJECT_NAME: return "INVALID_OBJECT_NAME";
            case moveit::core::MoveItErrorCode::FRAME_TRANSFORM_FAILURE: return "FRAME_TRANSFORM_FAILURE";
            case moveit::core::MoveItErrorCode::COLLISION_CHECKING_UNAVAILABLE: return "COLLISION_CHECKING_UNAVAILABLE";
            case moveit::core::MoveItErrorCode::ROBOT_STATE_STALE: return "ROBOT_STATE_STALE";
            case moveit::core::MoveItErrorCode::CRASH: return "CRASH";
            case moveit::core::MoveItErrorCode::ABORT: return "ABORT";
            default: return "UNKNOWN(" + std::to_string(code.val) + ")";
        }
    }

    void DiagnosticReport::buildSummary()
    {
        std::ostringstream oss;

        oss << "[DIAG] Primary cause: " << causeToString(primary_cause);
        if (all_causes.size() > 1) {
            oss << " | All causes: ";
            for (size_t i = 0; i < all_causes.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << causeToString(all_causes[i]);
            }
        }
        oss << "\n";

        auto appendCollisionDetails = [&oss](
            const std::string& label,
            const std::vector<std::string>& self_pairs,
            const std::vector<std::string>& env_pairs,
            const std::vector<std::string>& all_pairs)
        {
            oss << "  - " << label << " IS in collision.";
            if (!self_pairs.empty()) {
                oss << " Self-collision: ";
                for (size_t i = 0; i < self_pairs.size(); ++i) {
                    if (i > 0) oss << ", ";
                    oss << self_pairs[i];
                }
                oss << ".";
            }
            if (!env_pairs.empty()) {
                oss << " Environment: ";
                for (size_t i = 0; i < env_pairs.size(); ++i) {
                    if (i > 0) oss << ", ";
                    oss << env_pairs[i];
                }
                oss << ".";
            }
            if (self_pairs.empty() && env_pairs.empty() && !all_pairs.empty()) {
                oss << " Pairs: ";
                for (size_t i = 0; i < all_pairs.size(); ++i) {
                    if (i > 0) oss << ", ";
                    oss << all_pairs[i];
                }
            }
            oss << "\n";
        };

        if (start_in_collision) {
            appendCollisionDetails("Start state",
                start_self_collision_pairs, start_env_collision_pairs, start_collision_pairs);
        }
        if (goal_in_collision) {
            appendCollisionDetails("Goal state",
                goal_self_collision_pairs, goal_env_collision_pairs, goal_collision_pairs);
        }

        if (ik_failed) {
            oss << "  - IK failed: " << ik_detail << "\n";
        }
        if (near_singularity) {
            oss << "  - Near singularity. Manipulability="
                << manipulability << " (threshold=" << singularity_threshold
                << "), Jacobian condition=" << condition_number << "\n";
        }
        if (joints_out_of_bounds) {
            oss << "  - Joint limits violated: ";
            for (size_t i = 0; i < violating_joints.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << violating_joints[i];
            }
            oss << "\n";
        }
        if (cartesian_fraction >= 0.0) {
            oss << "  - Cartesian fraction achieved: "
                << (cartesian_fraction * 100.0) << "%";
            if (cartesian_fail_waypoint_index >= 0) {
                oss << " (failure near waypoint #" << cartesian_fail_waypoint_index << ")";
            }
            oss << "\n";
        }
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
        req.contacts = true;
        req.max_contacts = 10;
        req.verbose = false;

        collision_detection::CollisionResult result;
        scene->checkCollision(req, result, state);

        collision_pairs.clear();
        self_collision_pairs.clear();
        env_collision_pairs.clear();

        if (result.collision) {
            const auto& link_names = state.getRobotModel()->getLinkModelNames();
            std::set<std::string> robot_links(link_names.begin(), link_names.end());

            for (const auto& contact_pair : result.contacts) {
                std::string pair_str = contact_pair.first.first
                                    + " <-> "
                                    + contact_pair.first.second;
                collision_pairs.push_back(pair_str);

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

    std::vector<std::string> checkJointLimits(
        const moveit::core::RobotState& state,
        const std::string& group_name)
    {
        std::vector<std::string> violating;
        const auto* jmg = state.getRobotModel()->getJointModelGroup(group_name);
        if (!jmg) return violating;

        for (const auto* jm : jmg->getActiveJointModels()) {
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

        Eigen::Vector3d reference_point(0.0, 0.0, 0.0);
        Eigen::MatrixXd jacobian;

        if (!state.getJacobian(jmg, jmg->getLinkModels().back(), reference_point, jacobian)) {
            return metrics;
        }

        Eigen::JacobiSVD<Eigen::MatrixXd> svd(jacobian);
        Eigen::VectorXd sv = svd.singularValues();

        if (sv.size() == 0) return metrics;

        int effective_rank = std::min(jacobian.rows(), jacobian.cols());

        double sigma_max = sv(0);
        double sigma_min = sv(effective_rank - 1);

        metrics.manipulability = 1.0;
        for (int i = 0; i < effective_rank; ++i) {
            metrics.manipulability *= sv(i);
        }

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

        RCLCPP_WARN(logger, "[DIAG] MoveIt error code: %d (%s)",
            error_code.val, moveitErrorCodeToString(error_code).c_str());

        // Trust planner error codes as primary source of truth
        if (error_code.val == moveit_msgs::msg::MoveItErrorCodes::GOAL_IN_COLLISION) {
            report.goal_in_collision = true;
            report.all_causes.push_back(DiagnosticReport::Cause::GOAL_COLLISION);
        }

        const auto* jmg = move_group.getRobotModel()->getJointModelGroup(group_name);
        if (!jmg) {
            report.primary_cause = DiagnosticReport::Cause::UNKNOWN;
            report.summary = "[DIAG] Cannot diagnose: joint model group '" + group_name + "' not found.";
            return report;
        }

        // Get current state for IK seeding
        moveit::core::RobotStatePtr current_state = move_group.getCurrentState();

        // Construct a goal state and check it
        moveit::core::RobotState goal_state(move_group.getRobotModel());
        bool goal_state_valid = false;

        if (goal_joints && !goal_joints->empty()) {
            goal_state.setJointGroupPositions(jmg, *goal_joints);
            goal_state.update();
            goal_state_valid = true;
        }
        else if (goal_pose) {
            bool ik_ok = goal_state.setFromIK(jmg, *goal_pose, 0.1);
            if (!ik_ok) {
                // IK failed — is it because of collision or truly unreachable?
                // Retry with pure kinematics (no collision validation callback)
                moveit::core::RobotState ik_probe(move_group.getRobotModel());
                if (current_state) {
                    ik_probe = *current_state;
                }

                bool ik_no_collision = ik_probe.setFromIK(
                    jmg, *goal_pose, 0.1,
                    moveit::core::GroupStateValidityCallbackFn());

                if (ik_no_collision) {
                    // Kinematically reachable but IK rejected it — likely collision
                    goal_state = ik_probe;
                    goal_state.update();
                    goal_state_valid = true;
                    RCLCPP_WARN(logger,
                        "[DIAG] IK succeeded without collision check — "
                        "goal is reachable but likely in collision");
                } else {
                    // Truly unreachable
                    report.ik_failed = true;
                    report.ik_detail = "IK solver returned no solution for the target pose. "
                                    "The pose may be outside the workspace or near a singularity.";
                    report.all_causes.push_back(DiagnosticReport::Cause::IK_UNREACHABLE);
                }
            } else {
                goal_state_valid = true;
            }
        }

        if (goal_state_valid) {
            std::vector<double> valid_goal_joints;
            goal_state.copyJointGroupPositions(jmg, valid_goal_joints);
            // RCLCPP_WARN(logger, "[DIAG] Goal state joint values: %s",
            //     formatJoints(valid_goal_joints).c_str());

            // Collision check on goal state
            std::vector<std::string> goal_pairs, goal_self, goal_env;
            if (checkStateCollision(scene, goal_state, group_name, goal_pairs, goal_self, goal_env)) {
                report.goal_in_collision = true;
                report.goal_collision_pairs = goal_pairs;
                report.goal_self_collision_pairs = goal_self;
                report.goal_env_collision_pairs = goal_env;
                if (std::find(report.all_causes.begin(), report.all_causes.end(),
                            DiagnosticReport::Cause::GOAL_COLLISION) == report.all_causes.end()) {
                    report.all_causes.push_back(DiagnosticReport::Cause::GOAL_COLLISION);
                }
            }

            // Joint limits on goal state
            auto goal_violations = checkJointLimits(goal_state, group_name);
            if (!goal_violations.empty()) {
                report.joints_out_of_bounds = true;
                report.violating_joints = goal_violations;
                report.all_causes.push_back(DiagnosticReport::Cause::JOINT_LIMITS);
            }

            // Singularity check at goal state
            auto sing = computeSingularityMetrics(goal_state, jmg);
            report.manipulability = sing.manipulability;
            report.condition_number = sing.condition_number;
            if (sing.is_singular) {
                report.near_singularity = true;
                report.all_causes.push_back(DiagnosticReport::Cause::SINGULARITY);
            } else {
                RCLCPP_DEBUG(logger,
                    "[DIAG] Singularity OK: manipulability=%.6f, condition=%.1f",
                    sing.manipulability, sing.condition_number);
            }
        }

        // Check for timeout
        if (error_code.val == moveit_msgs::msg::MoveItErrorCodes::TIMED_OUT) {
            report.all_causes.push_back(DiagnosticReport::Cause::TIMEOUT);
        }

        // Determine primary cause
        if (report.all_causes.empty()) {
            report.primary_cause = DiagnosticReport::Cause::UNKNOWN;
        } else if (report.all_causes.size() == 1) {
            report.primary_cause = report.all_causes[0];
        } else {
            report.primary_cause = DiagnosticReport::Cause::MULTIPLE_CAUSES;
            for (auto c : {DiagnosticReport::Cause::GOAL_COLLISION,
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

    std::string diagnoseExecutionFailure(
        const moveit::core::MoveItErrorCode& exec_code,
        const moveit::planning_interface::MoveGroupInterface& move_group,
        const planning_scene::PlanningSceneConstPtr& scene,
        const std::string& group_name,
        const rclcpp::Logger& logger)
    {
        std::ostringstream oss;
        oss << "Execution failed: " << moveitErrorCodeToString(exec_code);

        // Log the current joint state at the point of failure
        auto current_state = move_group.getCurrentState(1.0);
        if (current_state) {
            std::vector<double> joint_vals;
            current_state->copyJointGroupPositions(group_name, joint_vals);
            oss << " | Interrupted joint state: [";
            for (size_t i = 0; i < joint_vals.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << std::fixed << std::setprecision(4) << joint_vals[i];
            }
            oss << "]";

            // Run collision check at interrupted state
            if (scene) {
                std::vector<std::string> pairs, self_pairs, env_pairs;
                if (checkStateCollision(scene, *current_state, group_name,
                                        pairs, self_pairs, env_pairs)) {
                    oss << " | IN COLLISION at interrupted state: ";
                    for (size_t i = 0; i < pairs.size() && i < 5; ++i) {
                        if (i > 0) oss << ", ";
                        oss << pairs[i];
                    }
                    if (!self_pairs.empty()) oss << " (" << self_pairs.size() << " self-collision)";
                    if (!env_pairs.empty()) oss << " (" << env_pairs.size() << " env-collision)";
                }

                // Singularity check at interrupted state
                const auto* jmg = move_group.getRobotModel()->getJointModelGroup(group_name);
                if (jmg) {
                    auto sing = computeSingularityMetrics(*current_state, jmg);
                    if (sing.is_singular) {
                        oss << " | NEAR SINGULARITY: manipulability=" << sing.manipulability
                            << ", condition=" << sing.condition_number;
                    }
                }
            }
        } else {
            oss << " | WARNING: Could not retrieve robot state after execution failure";
        }

        std::string result = oss.str();
        RCLCPP_ERROR(logger, "[EXEC-DIAG] %s", result.c_str());
        return result;
    }

}  // namespace motion_control