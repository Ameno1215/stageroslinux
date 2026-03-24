#include "motion_control/motion_server.hpp"


namespace motion_control
{

    MotionServer::MotionServer(const rclcpp::NodeOptions& options)
    : rclcpp::Node("motion_server", options)
    {
        // Declare parameters for convenient launch-time configuration
        this->declare_parameter<std::string>("model", "vs060");
        this->declare_parameter<std::string>("planning_group", "arm");
        this->declare_parameter<double>("velocity_scale", 1.0);
        this->declare_parameter<double>("accel_scale", 1.0);
        this->set_parameter(rclcpp::Parameter("use_sim_time", true));

        // Initialisation du système d'écoute TF
        tf_buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
        tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
        rclcpp::QoS qos(10);
        qos.transient_local();
        visual_marker_pub_ = this->create_publisher<visualization_msgs::msg::Marker>("motion_server_markers", qos);

        srv_init_ = this->create_service<srv::InitRobot>(
            "init_robot",
            std::bind(&MotionServer::onInitRobot, this, std::placeholders::_1, std::placeholders::_2));

        srv_move_joints_ = this->create_service<srv::MoveJoints>(
            "move_joints",
            std::bind(&MotionServer::onMoveJoints, this, std::placeholders::_1, std::placeholders::_2));

        srv_move_pose_ = this->create_service<srv::MoveToPose>(
            "move_to_pose",
            std::bind(&MotionServer::onMoveToPose, this, std::placeholders::_1, std::placeholders::_2));

        srv_move_pose_via_joint_ = this->create_service<srv::MoveToPose>(
            "move_to_pose_via_joint",
            std::bind(&MotionServer::onMoveToPoseViaJoint, this, std::placeholders::_1, std::placeholders::_2));

        srv_move_waypoints_ = this->create_service<srv::MoveWaypoints>(
            "move_waypoints",
            std::bind(&MotionServer::onMoveWaypoints, this, std::placeholders::_1, std::placeholders::_2));

        srv_scaling_ = this->create_service<srv::SetScaling>(
            "set_scaling",
            std::bind(&MotionServer::onSetScaling, this, std::placeholders::_1, std::placeholders::_2));

        srv_get_joints_ = this->create_service<srv::GetJointState>(
            "get_joint_state",
            std::bind(&MotionServer::onGetJointState, this, std::placeholders::_1, std::placeholders::_2));

        srv_get_pose_ = this->create_service<srv::GetCurrentPose>(
            "get_current_pose",
            std::bind(&MotionServer::onGetCurrentPose, this, std::placeholders::_1, std::placeholders::_2));
        
        srv_virtual_cage_ = this->create_service<srv::SetVirtualCage>(
            "set_virtual_cage",
            std::bind(&MotionServer::onSetVirtualCage, this, std::placeholders::_1, std::placeholders::_2));

        srv_manage_box_ = this->create_service<srv::ManageBox>(
            "manage_box",
            std::bind(&MotionServer::onManageBox, this, std::placeholders::_1, std::placeholders::_2));
        
        srv_manage_mesh_ = this->create_service<srv::ManageMesh>(
            "manage_mesh",
            std::bind(&MotionServer::onManageMesh, this, std::placeholders::_1, std::placeholders::_2));

        RCLCPP_INFO(this->get_logger(), "MotionServer ready. Call /init_robot first");
    }

    bool MotionServer::ensureInitialized(std::string& why) const
        {
        if (!initialized_ || !move_group_) {
            why = "Robot not initialized. Call service /init_robot first";
            return false;
        }
        return true;
    }

    void MotionServer::onInitRobot(
        const std::shared_ptr<srv::InitRobot::Request> req,
        std::shared_ptr<srv::InitRobot::Response> res)
        {
        // Thread-safety: MoveGroupInterface is not designed to be called concurrently
        std::lock_guard<std::mutex> lock(mtx_);

        // If request fields are empty, fallback to node parameters
        auto model = req->model.empty() ? this->get_parameter("model").as_string() : req->model;
        auto group = req->planning_group.empty() ? this->get_parameter("planning_group").as_string() : req->planning_group;

        double v = req->velocity_scale > 0.0 ? req->velocity_scale : this->get_parameter("velocity_scale").as_double();
        double a = req->accel_scale > 0.0 ? req->accel_scale : this->get_parameter("accel_scale").as_double();

        model_ = model;
        planning_group_ = group;
        vel_scale_ = std::min(std::max(v, 0.0), 1.0);
        accel_scale_ = std::min(std::max(a, 0.0), 1.0);

        try {
            // Create MoveIt interfaces
            move_group_ = std::make_shared<moveit::planning_interface::MoveGroupInterface>(
            shared_from_this(), planning_group_);
            planning_scene_ = std::make_shared<moveit::planning_interface::PlanningSceneInterface>();

            // This gives us access to the full PlanningScene (collision world,
            // allowed collision matrix, robot state) needed by diagnostic helpers.
            psm_ = std::make_shared<planning_scene_monitor::PlanningSceneMonitor>(
            shared_from_this(), "robot_description");
            
            // Start listening to the planning scene topic published by move_group
            psm_->startSceneMonitor("/monitored_planning_scene");
            // Start listening to the robot's joint state for state updates
            psm_->startStateMonitor("/joint_states");
            // Wait briefly for the first scene to arrive
            if (!psm_->waitForCurrentRobotState(this->now(), 2.0)) {
                RCLCPP_WARN(this->get_logger(),
                    "PlanningSceneMonitor: timed out waiting for robot state. "
                    "Diagnostics may be incomplete on first call.");
            }

            move_group_->setMaxVelocityScalingFactor(vel_scale_);
            move_group_->setMaxAccelerationScalingFactor(accel_scale_);

            // Find best parameters for fast and reliable planning. These can be tuned based on the robot's performance and environment complexity.
            double p_time = req->planning_time > 0.0 ? req->planning_time : 5.0;
            int p_attempts = req->planning_attempts > 0 ? req->planning_attempts : 10;
            bool a_replan = req->allow_replanning;
            std::string planner_id = req->planner_id.empty() ? "PRMstar" : req->planner_id;
            
            move_group_->setPlanningTime(p_time); // Maximum time (in seconds) allowed for planning.
            move_group_->setNumPlanningAttempts(p_attempts);  //Number of attempts simultaneously launched by MoveIt to find a valid plan (with different random seeds).
            move_group_->allowReplanning(a_replan); // If true, MoveIt will automatically try to replan if the current plan fails during execution (e.g., due to a new obstacle).
            move_group_->setPlannerId(planner_id);

            // Log available joints and links
            auto names = move_group_->getRobotModel()->getLinkModelNames();
            RCLCPP_INFO(this->get_logger(), "--- Links available for this robot ---");
            for (const auto& name : names) {
                RCLCPP_INFO(this->get_logger(), "Link: %s", name.c_str());
            }

            std::ostringstream oss;
            oss << "Initialized with model=" << model_
                << ", group=" << planning_group_
                << ", vel_scale=" << vel_scale_
                << ", accel_scale=" << accel_scale_
                << ", plan_time=" << p_time
                << ", plan_attempts=" << p_attempts
                << ", replan=" << (a_replan ? "true" : "false")
                << ",planner_id=" << planner_id
                << ", planning_frame=" << move_group_->getPlanningFrame()
                << ", ee_link=" << move_group_->getEndEffectorLink();

            initialized_ = true;
            res->success = true;
            res->message = oss.str();
            RCLCPP_INFO(this->get_logger(), "%s", res->message.c_str());
        } catch (const std::exception& e) {
            initialized_ = false;
            move_group_.reset();
            planning_scene_.reset();
            res->success = false;
            res->message = std::string("Init failed: ") + e.what();
            RCLCPP_ERROR(this->get_logger(), "%s", res->message.c_str());
        }
    }

    planning_scene::PlanningSceneConstPtr MotionServer::getLockedPlanningScene() const
    {
        if (!psm_) return nullptr;

        planning_scene_monitor::LockedPlanningSceneRO locked_scene(psm_);
        return planning_scene::PlanningScene::clone(
            locked_scene.operator->()->shared_from_this());
    }

    bool MotionServer::solveIKAndPlanJoints(
        const geometry_msgs::msg::Pose& target_pose,
        bool execute,
        std::string& out_msg)
    {
        const auto* jmg = move_group_->getRobotModel()->getJointModelGroup(planning_group_);
        if (!jmg) {
            out_msg = "Unknown planning group: " + planning_group_;
            return false;
        }

        moveit::core::RobotStatePtr current_state = move_group_->getCurrentState(2.0);
        if (!current_state) {
            out_msg = "Failed to obtain current robot state";
            return false;
        }

        // Capture current joint positions as the reference for cost comparison
        std::vector<double> current_joints;
        current_state->copyJointGroupPositions(jmg, current_joints);

        // Multi-seed IK search: keep the solution closest to current config
        constexpr int    NUM_ATTEMPTS  = 32;
        constexpr double IK_TIMEOUT    = 0.1;   // per-attempt timeout (seconds)

        double best_cost = std::numeric_limits<double>::max();
        std::vector<double> best_joints;

        // Reusable scratch state (avoids repeated allocation)
        auto candidate = std::make_shared<moveit::core::RobotState>(*current_state);

        for (int i = 0; i < NUM_ATTEMPTS; ++i)
        {
            if (i == 0) {
                // First attempt: seed with the actual current state (often already good)
                *candidate = *current_state;
            } else {
                // Subsequent attempts: random seed to explore other IK branches
                candidate->setToRandomPositions(jmg);
            }

            if (!candidate->setFromIK(jmg, target_pose, IK_TIMEOUT)) {
                continue;  // This seed didn't converge — try next
            }

            candidate->enforceBounds(jmg);

            std::vector<double> candidate_joints;
            candidate->copyJointGroupPositions(jmg, candidate_joints);
            
            std::vector<double> weights = {1.0, 3.0, 3.0, .0, 1.0, 1.0};
            double cost = 0.0;
            for (std::size_t j = 0; j < candidate_joints.size(); ++j) {
                double diff = candidate_joints[j] - current_joints[j];
                cost += weights[j] * diff * diff;
            }

            if (cost < best_cost) {
                best_cost   = cost;
                best_joints = std::move(candidate_joints);
            }
        }

        if (best_joints.empty()) {
            out_msg = "IK failed: pose is unreachable (out of workspace or near singularity) "
                    "after " + std::to_string(NUM_ATTEMPTS) + " attempts";
            return false;
        }

        return planAndExecuteJoints(best_joints, false, execute, out_msg);
    }

    bool MotionServer::planAndMaybeExecutePose(
        const geometry_msgs::msg::PoseStamped& target,
        bool execute,
        std::string& out_msg)
    {
        move_group_->setPoseTarget(target);
        move_group_->setMaxVelocityScalingFactor(vel_scale_);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);

        // RCLCPP_DEBUG(this->get_logger(),
        //     "[PlanPose] Target: pos=[%.4f, %.4f, %.4f] quat=[%.4f, %.4f, %.4f, %.4f] execute=%s",
        //     target.pose.position.x, target.pose.position.y, target.pose.position.z,
        //     target.pose.orientation.x, target.pose.orientation.y,
        //     target.pose.orientation.z, target.pose.orientation.w,
        //     execute ? "true" : "false");

        // --- Strategy 1: Standard pose target ---
        moveit::planning_interface::MoveGroupInterface::Plan plan;
        auto start_time = std::chrono::high_resolution_clock::now();
        auto code = move_group_->plan(plan);
        auto end_time = std::chrono::high_resolution_clock::now();
        double planning_duration = std::chrono::duration<double>(end_time - start_time).count();

        if (code != moveit::core::MoveItErrorCode::SUCCESS) {
            // Build diagnostic message for logging
            std::string diag_msg;
            auto scene = getLockedPlanningScene();
            if (scene) {
                auto report = diagnosePlanningFailure(
                    code, *move_group_, scene, planning_group_,
                    &target.pose, nullptr,
                    planning_duration, this->get_logger());
                diag_msg = moveitErrorCodeToString(code) + " | " + report.summary;
            } else {
                diag_msg = moveitErrorCodeToString(code) + " [diagnostic scene unavailable]";
            }

            // --- Strategy 2: Fallback to explicit IK + joint-space planning ---
            // RCLCPP_WARN(this->get_logger(),
            //     "Pose target planning failed: %s (%.2fs) — Falling back to IK + joint-space...",
            //     diag_msg.c_str(), planning_duration);

            move_group_->clearPoseTargets();

            std::string fallback_msg;
            bool fallback_ok = solveIKAndPlanJoints(target.pose, execute, fallback_msg);

            if (fallback_ok) {
                out_msg = "[FALLBACK IK+Joint] " + fallback_msg;
                // RCLCPP_INFO(this->get_logger(), "Fallback succeeded: %s", fallback_msg.c_str());
                return true;
            }

            // Both strategies failed
            out_msg = "Both strategies failed. "
                    "Pose target: " + diag_msg + " (" + std::to_string(planning_duration) + "s) | "
                    "IK+Joint fallback: " + fallback_msg;
            return false;
        }

        RCLCPP_DEBUG(this->get_logger(),
            "[PlanPose] Plan OK: %zu points, planning took %.3fs",
            plan.trajectory_.joint_trajectory.points.size(), planning_duration);

        // Execute strategy 1 if it's possible
        move_group_->clearPoseTargets();

        if (execute) {
            // Validate trajectory before sending to controller
            std::string traj_err;
            if (!validateTrajectory(plan.trajectory_, traj_err)) {
                out_msg = traj_err;
                return false;
            }

            auto exec_code = move_group_->execute(plan);
            if (exec_code != moveit::core::MoveItErrorCode::SUCCESS) {
                // Run post-execution diagnostics
                out_msg = diagnoseExecutionFailure(exec_code);
                return false;
            }
            out_msg = "Planned and executed pose target successfully (took " + std::to_string(planning_duration) + "s)";
            return true;
        }

        out_msg = "Planned pose target successfully (execute=false) (took " + std::to_string(planning_duration) + "s)";
        return true;
    }

    void MotionServer::onSetScaling(
        const std::shared_ptr<srv::SetScaling::Request> req,
        std::shared_ptr<srv::SetScaling::Response> res)
        {
        // Thread-safety: MoveGroupInterface is not designed to be called concurrently
        std::lock_guard<std::mutex> lock(mtx_);

        // Clamp to [0, 1]
        const double v = std::min(std::max(req->velocity_scale, 0.0), 1.0);
        const double a = std::min(std::max(req->accel_scale, 0.0), 1.0);

        vel_scale_ = v;
        accel_scale_ = a;

        // If MoveGroupInterface is already initialized, apply immediately
        if (move_group_) {
            move_group_->setMaxVelocityScalingFactor(vel_scale_);
            move_group_->setMaxAccelerationScalingFactor(accel_scale_);
        }

        std::ostringstream oss;
        oss << "Scaling updated: velocity_scale=" << vel_scale_
            << ", accel_scale=" << accel_scale_
            << ". This will be used for all subsequent motions";

        res->success = true;
        res->message = oss.str();

        RCLCPP_INFO(this->get_logger(), "%s", res->message.c_str());
    }

    std::optional<geometry_msgs::msg::PoseStamped> MotionServer::computeAbsoluteTarget(
        double x, double y, double z,
        double r1, double r2, double r3, double r4,
        const std::string& rot_format,
        const std::string& ref_frame,
        bool is_relative,
        std::string& out_error_msg)
    {
        geometry_msgs::msg::PoseStamped final_pose;
        final_pose.header.frame_id = "world";
        final_pose.header.stamp = this->now();

        // Prepare the target transformation (Delta or Absolute)
        tf2::Vector3 target_translation(x, y, z);
        tf2::Quaternion target_rotation;

        if (rot_format == "RPY") {
            target_rotation.setRPY(r1, r2, r3); // r1=Roll, r2=Pitch, r3=Yaw
        } else {
            target_rotation = tf2::Quaternion(r1, r2, r3, r4); // X, Y, Z, W
            target_rotation.normalize();
        }

        tf2::Transform target_transform(target_rotation, target_translation);

        // If it's absolute in the WORLD framework, we're done!
        if (!is_relative && ref_frame == "WORLD") {
            tf2::toMsg(target_transform, final_pose.pose);
            return final_pose;
        }

        // Otherwise, we need the current position to calculate the relative or tool coordinate system
        geometry_msgs::msg::PoseStamped current_pose_msg;
        try {
            std::string ee_link = move_group_->getEndEffectorLink();
            geometry_msgs::msg::TransformStamped t = tf_buffer_->lookupTransform(
                "world", ee_link, tf2::TimePointZero, tf2::durationFromSec(0.5));

            current_pose_msg.header = t.header;
            current_pose_msg.pose.position.x = t.transform.translation.x;
            current_pose_msg.pose.position.y = t.transform.translation.y;
            current_pose_msg.pose.position.z = t.transform.translation.z;
            current_pose_msg.pose.orientation = t.transform.rotation;

            RCLCPP_DEBUG(this->get_logger(),
                "Current pose (TF2): position(%.3f, %.3f, %.3f) orientation(%.4f, %.4f, %.4f, %.4f)",
                current_pose_msg.pose.position.x,
                current_pose_msg.pose.position.y,
                current_pose_msg.pose.position.z,
                current_pose_msg.pose.orientation.x,
                current_pose_msg.pose.orientation.y,
                current_pose_msg.pose.orientation.z,
                current_pose_msg.pose.orientation.w);
        } catch (const tf2::TransformException& e) {
            out_error_msg = std::string("TF2 lookup failed for current pose: ") + e.what();
            return std::nullopt;
        }
        
        tf2::Transform current_transform;
        tf2::fromMsg(current_pose_msg.pose, current_transform);

        tf2::Transform result_transform;

        if (is_relative && ref_frame == "TOOL") {
            // Relative motion in the tool's frame of reference (Fly-by-wire)
            // // MATHS: Post-multiplication
            result_transform = current_transform * target_transform;
        } 
        else if (is_relative && ref_frame == "WORLD") {
            // Relative motion in the world frame of reference (e.g., moving 10 cm on the world Z axis)
            // MATHS: Pre-multiplication for translation
            result_transform.setOrigin(current_transform.getOrigin() + target_translation);
            result_transform.setRotation(target_rotation * current_transform.getRotation());
        }
        else {
            out_error_msg = "Absolute combination + TOOL marker not supported. Please use WORLD reference for absolute poses";
            return std::nullopt;
        }

        tf2::toMsg(result_transform, final_pose.pose);
        return final_pose;
    }

    double MotionServer::computeCartesianPathRobust(
        const std::vector<geometry_msgs::msg::Pose>& waypoints,
        moveit_msgs::msg::RobotTrajectory& trajectory,
        std::string& out_msg)
    {
        // Attempt 1: standard
        double fraction = move_group_->computeCartesianPath(
            waypoints, 0.005, 3.0, trajectory);
        if (fraction >= 0.95) { out_msg = "OK (standard)"; return fraction; }

        // Attempt 2: coarser step (more permissive)
        RCLCPP_WARN(this->get_logger(),
            "Cartesian path attempt 1 failed (fraction: %.1f%%). Retrying with coarser step...",
            fraction * 100.0);

        fraction = move_group_->computeCartesianPath(
            waypoints, 0.01, 3.0, trajectory);
        if (fraction >= 0.95) {
            RCLCPP_WARN(this->get_logger(),
                "Cartesian path succeeded on fallback (coarser step). Fraction: %.1f%%",
                fraction * 100.0);
            out_msg = "OK (coarser step — fallback)";
            return fraction;
        }

        out_msg = "FAILED (best fraction: " + std::to_string(fraction * 100) + "%)";
        return fraction;
    }

    void MotionServer::applyVelocityScaling(moveit_msgs::msg::RobotTrajectory& trajectory)
    {
        // computeCartesianPath does NOT respect setMaxVelocityScalingFactor.
        // We must manually retime the trajectory using TOTG (Time Optimal Trajectory Generation).
        robot_trajectory::RobotTrajectory rt(
            move_group_->getRobotModel(), planning_group_);

        rt.setRobotTrajectoryMsg(*move_group_->getCurrentState(), trajectory);

        trajectory_processing::TimeOptimalTrajectoryGeneration totg;

        // Check return value — if retiming fails, the robot would
        // execute with the raw (unscaled) timestamps, potentially at full speed.
        // This is a SAFETY-CRITICAL check.
        bool ok = totg.computeTimeStamps(rt, vel_scale_, accel_scale_);
        if (!ok) {
            RCLCPP_ERROR(this->get_logger(),
                "SAFETY: TOTG retiming FAILED (vel=%.2f, accel=%.2f). "
                "Trajectory will NOT be executed to prevent uncontrolled speed. "
                "Clearing trajectory points as a safety measure.",
                vel_scale_, accel_scale_);
            // Clear the trajectory to prevent execution with raw timestamps
            trajectory.joint_trajectory.points.clear();
            return;
        }

        // Convert back to message with correct timestamps
        rt.getRobotTrajectoryMsg(trajectory);
    }

    // Trajectory sanity check before sending to the controller
    bool MotionServer::validateTrajectory(
        const moveit_msgs::msg::RobotTrajectory& trajectory,
        std::string& out_msg) const
    {
        const auto& points = trajectory.joint_trajectory.points;

        if (points.empty()) {
            out_msg = "SAFETY: Trajectory has 0 points — refusing execution";
            RCLCPP_ERROR(this->get_logger(), "%s", out_msg.c_str());
            return false;
        }

        double total_time = points.back().time_from_start.sec
                          + points.back().time_from_start.nanosec * 1e-9;

        RCLCPP_DEBUG(this->get_logger(),
            "[TRAJ] %zu points, total duration: %.4fs, joints: %zu",
            points.size(), total_time,
            trajectory.joint_trajectory.joint_names.size());

        // Check for suspiciously short segments that could cause controller jerk
        int short_segment_count = 0;
        for (size_t i = 1; i < points.size(); ++i) {
            double t_prev = points[i-1].time_from_start.sec + points[i-1].time_from_start.nanosec * 1e-9;
            double t_curr = points[i].time_from_start.sec + points[i].time_from_start.nanosec * 1e-9;
            double dt = t_curr - t_prev;
            if (dt < 1e-6) {
                short_segment_count++;
            }
        }
        if (short_segment_count > 0) {
            RCLCPP_WARN(this->get_logger(),
                "[TRAJ] WARNING: %d segment(s) with near-zero time delta detected — "
                "controller may experience jerk", short_segment_count);
        }

        return true;
    }

    // Post-execution diagnostics
    std::string MotionServer::diagnoseExecutionFailure(
        const moveit::core::MoveItErrorCode& exec_code)
    {
        std::ostringstream oss;
        oss << "Execution failed: " << moveitErrorCodeToString(exec_code);

        // Log the current joint state at the point of failure
        auto current_state = move_group_->getCurrentState(1.0);
        if (current_state) {
            std::vector<double> joint_vals;
            current_state->copyJointGroupPositions(planning_group_, joint_vals);
            oss << " | Interrupted joint state: [";
            for (size_t i = 0; i < joint_vals.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << std::fixed << std::setprecision(4) << joint_vals[i];
            }
            oss << "]";

            // Run collision check at interrupted state
            auto scene = getLockedPlanningScene();
            if (scene) {
                std::vector<std::string> pairs, self_pairs, env_pairs;
                if (checkStateCollision(scene, *current_state, planning_group_,
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
                const auto* jmg = move_group_->getRobotModel()->getJointModelGroup(planning_group_);
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
        RCLCPP_ERROR(this->get_logger(), "[EXEC-DIAG] %s", result.c_str());
        return result;
    }

    void MotionServer::onMoveToPose(
        const std::shared_ptr<motion_control::srv::MoveToPose::Request> req,
        std::shared_ptr<motion_control::srv::MoveToPose::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string error_msg;
        if (!ensureInitialized(error_msg)) { res->success = false; res->message = error_msg; return; }

        auto maybe_target = computeAbsoluteTarget(
            req->x, req->y, req->z, req->r1, req->r2, req->r3, req->r4,
            req->rotation_format, req->reference_frame, req->is_relative, error_msg
        );

        if (!maybe_target.has_value()) { res->success = false; res->message = error_msg; return; }
        auto target_pose = maybe_target.value();

        // Validate quaternion to catch NaN/Inf before sending to MoveIt
        {
            const auto& q = target_pose.pose.orientation;
            double norm = std::sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
            if (!std::isfinite(norm) || norm < 0.99 || norm > 1.01) {
                res->success = false;
                res->message = "Invalid quaternion after transformation (norm=" + std::to_string(norm) + "). Check rotation inputs.";
                return;
            }
        }

        // Log the resolved target on the path for post-incident reconstruction
        RCLCPP_DEBUG(this->get_logger(),
            "[MoveToPose] Resolved target: pos=[%.4f, %.4f, %.4f] quat=[%.4f, %.4f, %.4f, %.4f] "
            "frame=%s ref=%s relative=%s cartesian=%s execute=%s",
            target_pose.pose.position.x, target_pose.pose.position.y, target_pose.pose.position.z,
            target_pose.pose.orientation.x, target_pose.pose.orientation.y,
            target_pose.pose.orientation.z, target_pose.pose.orientation.w,
            target_pose.header.frame_id.c_str(),
            req->reference_frame.c_str(),
            req->is_relative ? "true" : "false",
            req->cartesian_path ? "true" : "false",
            req->execute ? "true" : "false");

        // Speed application
        move_group_->setMaxVelocityScalingFactor(vel_scale_);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);

        if (req->cartesian_path)
        {
            std::vector<geometry_msgs::msg::Pose> waypoints;
            waypoints.push_back(target_pose.pose);

            moveit_msgs::msg::RobotTrajectory trajectory;
            std::string cart_msg;

            auto start_time = std::chrono::high_resolution_clock::now();
            double fraction = computeCartesianPathRobust(waypoints, trajectory, cart_msg);
            auto end_time = std::chrono::high_resolution_clock::now();
            double planning_duration = std::chrono::duration<double>(end_time - start_time).count();

            RCLCPP_INFO(this->get_logger(), "Cartesian path result: %s (%.2fs)", 
                        cart_msg.c_str(), planning_duration);

            if (fraction < 0.95) {
                // --- Cartesian-specific diagnostic ---
                auto scene = getLockedPlanningScene();
                std::string diag_summary;
                if (scene) {
                    auto report = diagnoseCartesianFailure(
                        *move_group_, scene, planning_group_,
                        waypoints, fraction,
                        planning_duration, this->get_logger());
                    diag_summary = report.summary;
                }

                res->success = false;
                res->message = "Cartesian path failed — fraction: "
                            + std::to_string(fraction * 100.0) + "% | "
                            + cart_msg;
                if (!diag_summary.empty()) {
                    res->message += " | " + diag_summary;
                }
                res->message += " (took " + std::to_string(planning_duration) + "s)";
                return;
            }

            // Apply velocity/acceleration scaling to the raw Cartesian trajectory
            applyVelocityScaling(trajectory);

            // Validate trajectory before sending to controller
            std::string traj_err;
            if (!validateTrajectory(trajectory, traj_err)) {
                res->success = false;
                res->message = traj_err;
                return;
            }

            if (req->execute) {
                auto exec_code = move_group_->execute(trajectory);
                if (exec_code != moveit::core::MoveItErrorCode::SUCCESS) {
                    // Run post-execution diagnostics
                    res->success = false;
                    res->message = diagnoseExecutionFailure(exec_code);
                } else {
                    res->success = true;
                    res->message = "Cartesian path executed. " + cart_msg
                                 + " (took " + std::to_string(planning_duration) + "s)";
                }
            } else {
                res->success = true;
                res->message = "Cartesian path planned at "
                            + std::to_string(fraction * 100.0) + "% (execute=false) — " + cart_msg;
            }
        }
        else 
        {
            // Standard joint space planning
            std::string msg;
            res->success = planAndMaybeExecutePose(target_pose, req->execute, msg);
            res->message = msg;
        }
    }

    void MotionServer::onMoveWaypoints(
        const std::shared_ptr<motion_control::srv::MoveWaypoints::Request> req,
        std::shared_ptr<motion_control::srv::MoveWaypoints::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string why;
        if (!ensureInitialized(why)) { res->success = false; res->message = why; return; }

        if (req->waypoints.empty()) {
            res->success = false;
            res->message = "The list of waypoints is empty";
            return;
        }

        // --- VERIFY PARALLEL ARRAYS ---
        if (req->is_relative_list.size() != req->waypoints.size() || 
            req->reference_frame_list.size() != req->waypoints.size()) 
        {
            res->success = false;
            res->message = "Configuration arrays (is_relative_list, reference_frame_list) must match the waypoints array size.";
            return;
        }

        // Initial base point: The current position of the robot
        tf2::Transform current_base_tf;
        try {
            std::string ee_link = move_group_->getEndEffectorLink();
            geometry_msgs::msg::TransformStamped t = tf_buffer_->lookupTransform(
                "world", ee_link, tf2::TimePointZero, tf2::durationFromSec(0.5));

            geometry_msgs::msg::Pose current_pose;
            current_pose.position.x = t.transform.translation.x;
            current_pose.position.y = t.transform.translation.y;
            current_pose.position.z = t.transform.translation.z;
            current_pose.orientation = t.transform.rotation;
            tf2::fromMsg(current_pose, current_base_tf);
        } catch (const tf2::TransformException& e) {
            res->success = false;
            res->message = std::string("TF2 lookup failed for current pose: ") + e.what();
            return;
        }

        std::vector<geometry_msgs::msg::Pose> absolute_waypoints;

        // Conversion loop
        for (size_t i = 0; i < req->waypoints.size(); ++i) {
            tf2::Transform wp_tf;
            tf2::fromMsg(req->waypoints[i], wp_tf); 
            tf2::Transform target_tf;

            // Retrieve the specific configuration for THIS waypoint
            bool is_rel = req->is_relative_list[i];
            std::string ref_frame = req->reference_frame_list[i];

            if (is_rel) {
                if (ref_frame == "TOOL") {
                    // Post-multiplication: delta applied along the tool's axes
                    target_tf = current_base_tf * wp_tf;
                } else { // WORLD
                    // Pre-multiplication: delta applied along the fixed world axes
                    target_tf.setOrigin(current_base_tf.getOrigin() + wp_tf.getOrigin());
                    target_tf.setRotation(wp_tf.getRotation() * current_base_tf.getRotation());
                    target_tf.getRotation().normalize();
                }
            } else {
                // Absolute point
                target_tf = wp_tf;
            }

            // The point we just calculated becomes the new reference base for the next point!
            current_base_tf = target_tf;

            tf2::Quaternion q_check = target_tf.getRotation();
            double norm = q_check.length();
            if (!std::isfinite(norm) || norm < 0.99 || norm > 1.01) {
                res->success = false;
                res->message = "Invalid quaternion at waypoint " + std::to_string(i)
                            + " (norm=" + std::to_string(norm) + ")";
                return;
            }

            geometry_msgs::msg::Pose abs_pose;
            tf2::toMsg(target_tf, abs_pose);
            absolute_waypoints.push_back(abs_pose);

            // Log each resolved waypoint for post-incident reconstruction
            RCLCPP_DEBUG(this->get_logger(),
                "[MoveWaypoints] WP#%zu resolved: pos=[%.4f, %.4f, %.4f] "
                "quat=[%.4f, %.4f, %.4f, %.4f] (rel=%s frame=%s)",
                i, abs_pose.position.x, abs_pose.position.y, abs_pose.position.z,
                abs_pose.orientation.x, abs_pose.orientation.y,
                abs_pose.orientation.z, abs_pose.orientation.w,
                is_rel ? "true" : "false", ref_frame.c_str());
        }

        RCLCPP_DEBUG(this->get_logger(),
            "[MoveWaypoints] %zu waypoints resolved, cartesian=%s, execute=%s",
            absolute_waypoints.size(),
            req->cartesian_path ? "true" : "false",
            req->execute ? "true" : "false");

        // Apply velocity and acceleration scaling factors
        move_group_->setMaxVelocityScalingFactor(vel_scale_);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);

        if (req->cartesian_path)
        {

            moveit_msgs::msg::RobotTrajectory trajectory;
            std::string cart_msg;

            auto start_time = std::chrono::high_resolution_clock::now();
            double fraction = computeCartesianPathRobust(absolute_waypoints, trajectory, cart_msg);
            auto end_time = std::chrono::high_resolution_clock::now();
            double planning_duration = std::chrono::duration<double>(end_time - start_time).count();

            RCLCPP_INFO(this->get_logger(), "Cartesian path result: %s (%.2fs)", 
                        cart_msg.c_str(), planning_duration);

            if (fraction < 0.95) {
                auto scene = getLockedPlanningScene();
                std::string diag_summary;
                if (scene) {
                    auto report = diagnoseCartesianFailure(
                        *move_group_, scene, planning_group_,
                        absolute_waypoints, fraction,
                        planning_duration, this->get_logger());
                    diag_summary = report.summary;
                }

                res->success = false;
                res->message = "Cartesian path failed — fraction: "
                            + std::to_string(fraction * 100.0) + "% | "
                            + cart_msg;
                if (!diag_summary.empty()) {
                    res->message += " | " + diag_summary;
                }
                res->message += " (took " + std::to_string(planning_duration) + "s)";
                return;
            }

            // Apply velocity/acceleration scaling to the raw Cartesian trajectory
            applyVelocityScaling(trajectory);

            // Validate trajectory before sending to controller
            std::string traj_err;
            if (!validateTrajectory(trajectory, traj_err)) {
                res->success = false;
                res->message = traj_err;
                return;
            }

            if (req->execute) {
                auto exec_code = move_group_->execute(trajectory);
                if (exec_code != moveit::core::MoveItErrorCode::SUCCESS) {
                    // Run post-execution diagnostics
                    res->success = false;
                    res->message = diagnoseExecutionFailure(exec_code);
                } else {
                    res->success = true;
                    res->message = "Cartesian path executed. " + cart_msg
                                 + " (took " + std::to_string(planning_duration) + "s)";
                }
            } else {
                res->success = true;
                res->message = "Cartesian path planned at "
                            + std::to_string(fraction * 100.0) + "% (execute=false) — " + cart_msg;
            }
        }
        else {
            moveit_msgs::msg::RobotTrajectory combined_trajectory;
            combined_trajectory.joint_trajectory.joint_names = move_group_->getJointNames();
            
            // Get the current state to use as the starting point for the first segment
            moveit::core::RobotStatePtr current_start_state = move_group_->getCurrentState();
            
            int32_t acc_sec = 0;
            uint32_t acc_nanosec = 0;
            auto start_time = std::chrono::high_resolution_clock::now();
            
            for (size_t i = 0; i < absolute_waypoints.size(); ++i) {
                // Set the starting state for this segment
                move_group_->setStartState(*current_start_state);
                
                // Set the target
                move_group_->setPoseTarget(absolute_waypoints[i]);
                
                // Plan the segment (Strategy 1: pose target)
                moveit::planning_interface::MoveGroupInterface::Plan segment_plan;
                auto seg_t0 = std::chrono::high_resolution_clock::now();
                auto code = move_group_->plan(segment_plan);
                double seg_dt = std::chrono::duration<double>(
                    std::chrono::high_resolution_clock::now() - seg_t0).count();

                // Hygiene: clear pose targets after planning (same as planAndMaybeExecutePose)
                move_group_->clearPoseTargets();

                RCLCPP_DEBUG(this->get_logger(),
                    "[MoveWaypoints] Segment %zu/%zu planning: %s (%.3fs, %zu points)",
                    i + 1, absolute_waypoints.size(),
                    (code == moveit::core::MoveItErrorCode::SUCCESS) ? "OK" : "FAILED",
                    seg_dt,
                    segment_plan.trajectory_.joint_trajectory.points.size());

                if (code != moveit::core::MoveItErrorCode::SUCCESS) {
                    // Diagnostics for the pose-target failure
                    std::string diag_msg;
                    auto scene = getLockedPlanningScene();
                    if (scene) {
                        auto report = diagnosePlanningFailure(
                            code, *move_group_, scene, planning_group_,
                            &absolute_waypoints[i], nullptr,
                            seg_dt, this->get_logger());
                        diag_msg = report.summary;
                    }

                    // RCLCPP_WARN(this->get_logger(),
                    //     "[MoveWaypoints] Segment %zu -space...",
                    //     i + 1, diag_msg.c_str(), seg_pose-target failed: %s (%.2fs) "
                    //     "— Falling back to IK + jointdt);

                    // Strategy 2: Explicit IK + joint-space planning 
                    const auto* jmg = move_group_->getRobotModel()->getJointModelGroup(planning_group_);
                    bool fallback_ok = false;

                    if (jmg) {
                        // Use the chained start state for IK, not getCurrentState()
                        moveit::core::RobotState ik_state(*current_start_state);
                        if (ik_state.setFromIK(jmg, absolute_waypoints[i], 0.5)) {
                            ik_state.enforceBounds(jmg);

                            std::vector<double> joint_targets;
                            ik_state.copyJointGroupPositions(jmg, joint_targets);

                            // Set joint target instead of pose target
                            std::map<std::string, double> joint_map;
                            const auto& names = jmg->getVariableNames();
                            for (size_t j = 0; j < names.size(); ++j) {
                                joint_map[names[j]] = joint_targets[j];
                            }

                            move_group_->setStartState(*current_start_state);
                            move_group_->setJointValueTarget(joint_map);

                            auto fb_t0 = std::chrono::high_resolution_clock::now();
                            code = move_group_->plan(segment_plan);
                            double fb_dt = std::chrono::duration<double>(
                                std::chrono::high_resolution_clock::now() - fb_t0).count();

                            RCLCPP_DEBUG(this->get_logger(),
                                "[MoveWaypoints] Segment %zu fallback IK+Joint: %s (%.3fs)",
                                i + 1,
                                (code == moveit::core::MoveItErrorCode::SUCCESS) ? "OK" : "FAILED",
                                fb_dt);

                            if (code == moveit::core::MoveItErrorCode::SUCCESS) {
                                fallback_ok = true;
                                RCLCPP_INFO(this->get_logger(),
                                    "[MoveWaypoints] Segment %zu fallback succeeded", i + 1);
                            }
                        } else {
                            RCLCPP_WARN(this->get_logger(),
                                "[MoveWaypoints] Segment %zu IK failed during fallback", i + 1);
                        }
                    }

                    if (!fallback_ok) {
                        res->success = false;
                        res->message = "Both strategies failed at waypoint " + std::to_string(i + 1)
                                    + ". Pose target: " + moveitErrorCodeToString(code);
                        if (!diag_msg.empty()) {
                            res->message += " | " + diag_msg;
                        }
                        move_group_->setStartStateToCurrentState();
                        return;
                    }
                }
                            
                // Assemble the trajectory and adjust timing
                int32_t segment_duration_sec = 0;
                uint32_t segment_duration_nanosec = 0;
                
                // Warn about velocity discontinuity at segment junctions.
                // MoveIt plans each segment with zero-velocity endpoints. Skipping
                // points[0] avoids duplicate positions but does NOT guarantee
                // velocity continuity. The controller may experience a velocity jump.
                size_t start_index = (i == 0) ? 0 : 1; 

                if (i > 0 && !combined_trajectory.joint_trajectory.points.empty()
                    && segment_plan.trajectory_.joint_trajectory.points.size() > 1) {
                    // Log the velocity at the junction for debugging
                    const auto& last_pt = combined_trajectory.joint_trajectory.points.back();
                    const auto& next_pt = segment_plan.trajectory_.joint_trajectory.points[1]; // first used point
                    if (!last_pt.velocities.empty() && !next_pt.velocities.empty()) {
                        double max_vel_jump = 0.0;
                        for (size_t j = 0; j < last_pt.velocities.size() && j < next_pt.velocities.size(); ++j) {
                            max_vel_jump = std::max(max_vel_jump,
                                std::abs(last_pt.velocities[j] - next_pt.velocities[j]));
                        }
                        if (max_vel_jump > 0.1) {  // rad/s threshold
                            RCLCPP_WARN(this->get_logger(),
                                "[MoveWaypoints] Velocity discontinuity at segment %zu junction: "
                                "max delta=%.4f rad/s — controller may jerk", i, max_vel_jump);
                        }
                    }
                }
                
                for (size_t j = start_index; j < segment_plan.trajectory_.joint_trajectory.points.size(); ++j) {
                    auto pt = segment_plan.trajectory_.joint_trajectory.points[j];
                    
                    segment_duration_sec = pt.time_from_start.sec;
                    segment_duration_nanosec = pt.time_from_start.nanosec;
                    
                    uint32_t total_nanosec = pt.time_from_start.nanosec + acc_nanosec;
                    int32_t total_sec = pt.time_from_start.sec + acc_sec + (total_nanosec / 1000000000);
                    total_nanosec = total_nanosec % 1000000000;
                    
                    pt.time_from_start.sec = total_sec;
                    pt.time_from_start.nanosec = total_nanosec;
                    
                    combined_trajectory.joint_trajectory.points.push_back(pt);
                }
                
                // Accumulate time for the next segment
                acc_sec += segment_duration_sec;
                acc_nanosec += segment_duration_nanosec;
                if (acc_nanosec >= 1000000000) {
                    acc_sec += (acc_nanosec / 1000000000);
                    acc_nanosec = acc_nanosec % 1000000000;
                }
                
                // Update the start state for the next segment calculation
                if (segment_plan.trajectory_.joint_trajectory.points.empty()) {
                    res->success = false;
                    res->message = "Planner returned an empty trajectory at waypoint " + std::to_string(i+1);
                    move_group_->setStartStateToCurrentState();
                    return;
                }
                std::vector<double> last_positions = segment_plan.trajectory_.joint_trajectory.points.back().positions;
                current_start_state->setJointGroupPositions(planning_group_, last_positions);
            }
            
            // Restore normal state
            move_group_->clearPoseTargets();
            move_group_->setStartStateToCurrentState();
            
            auto end_time = std::chrono::high_resolution_clock::now();
            double planning_duration = std::chrono::duration<double>(end_time - start_time).count();

            // Retime the combined trajectory to eliminate velocity discontinuities
            // at segment junctions (same mechanism as cartesian paths)
            applyVelocityScaling(combined_trajectory);

            // Summary of the assembled multi-segment trajectory
            RCLCPP_DEBUG(this->get_logger(),
                "[MoveWaypoints] Combined trajectory: %zu points, total planning duration: %.3fs",
                combined_trajectory.joint_trajectory.points.size(),
                planning_duration);

            // Validate combined trajectory before sending to controller
            std::string traj_err;
            if (!validateTrajectory(combined_trajectory, traj_err)) {
                res->success = false;
                res->message = traj_err;
                return;
            }
            
            // Execute
            if (req->execute) {
                auto exec_code = move_group_->execute(combined_trajectory);
                if (exec_code != moveit::core::MoveItErrorCode::SUCCESS) {
                    // Run post-execution diagnostics
                    res->success = false;
                    res->message = diagnoseExecutionFailure(exec_code);
                } else {
                    res->success = true;
                    res->message = "Waypoint sequence executed successfully ("
                                 + std::to_string(planning_duration) + "s)";
                }
            } else {
                res->success = true;
                res->message = "Sequence planned successfully (execute=false).";
            }
        }
    }

    bool MotionServer::planAndExecuteJoints(
        const std::vector<double>& joints, bool is_relative, bool execute, std::string& out_msg)
    {
        const auto* jmg = move_group_->getRobotModel()->getJointModelGroup(planning_group_);
        const auto& names = jmg->getVariableNames();

        if (joints.size() != names.size()) {
            out_msg = "Incorrect joint size. Expected: " + std::to_string(names.size());
            return false;
        }

        std::map<std::string, double> target;
        std::vector<double> current = move_group_->getCurrentJointValues();

        for (size_t i = 0; i < names.size(); ++i) {
            target[names[i]] = is_relative ? current[i] + joints[i] : joints[i];
        }

        // Log target and current joints on the happy path
        {
            std::ostringstream oss_cur, oss_tgt;
            oss_cur << std::fixed << std::setprecision(4) << "[";
            oss_tgt << std::fixed << std::setprecision(4) << "[";
            for (size_t i = 0; i < names.size(); ++i) {
                if (i > 0) { oss_cur << ", "; oss_tgt << ", "; }
                oss_cur << current[i];
                oss_tgt << target[names[i]];
            }
            oss_cur << "]"; oss_tgt << "]";
            RCLCPP_DEBUG(this->get_logger(),
                "[PlanJoints] current=%s target=%s relative=%s execute=%s",
                oss_cur.str().c_str(), oss_tgt.str().c_str(),
                is_relative ? "true" : "false",
                execute ? "true" : "false");
        }

        move_group_->setJointValueTarget(target);
        move_group_->setMaxVelocityScalingFactor(vel_scale_);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);

        // --- Pre-planning validation (fast-fail before expensive planning) ---
        auto scene = getLockedPlanningScene();
        if (scene) {
            moveit::core::RobotState goal_state(move_group_->getRobotModel());
            std::vector<double> goal_vec;
            for (const auto& name : names) {
                goal_vec.push_back(target[name]);
            }
            goal_state.setJointGroupPositions(jmg, goal_vec);
            goal_state.update();

            // Check joint limits
            auto violations = checkJointLimits(goal_state, planning_group_);
            if (!violations.empty()) {
                out_msg = "Goal violates joint limits: ";
                for (size_t i = 0; i < violations.size(); ++i) {
                    if (i > 0) out_msg += ", ";
                    out_msg += violations[i];
                }
                return false;
            }

            // Check goal collision
            std::vector<std::string> pairs, self_pairs, env_pairs;
            if (checkStateCollision(scene, goal_state, planning_group_, pairs, self_pairs, env_pairs)) {
                out_msg = "Goal state is in collision: ";
                for (size_t i = 0; i < pairs.size() && i < 5; ++i) {
                    if (i > 0) out_msg += ", ";
                    out_msg += pairs[i];
                }
                return false;
            }
        }

        moveit::planning_interface::MoveGroupInterface::Plan plan;
        auto t0 = std::chrono::high_resolution_clock::now();
        auto code = move_group_->plan(plan);
        double dt = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t0).count();

        if (code != moveit::core::MoveItErrorCode::SUCCESS) {
            std::string diag_msg;
            if (scene) {
                // Convert target map to vector for diagnostics
                std::vector<double> goal_joints_vec;
                for (const auto& name : names) {
                    goal_joints_vec.push_back(target[name]);
                }
                auto report = diagnosePlanningFailure(
                    code, *move_group_, scene, planning_group_,
                    nullptr, &goal_joints_vec,
                    dt, this->get_logger());
                diag_msg = report.summary;
            }

            out_msg = "Planning failed: " + moveitErrorCodeToString(code)
                    + " (took " + std::to_string(dt) + "s)";
            if (!diag_msg.empty()) {
                out_msg += " | " + diag_msg;
            }
            return false;
        }

        // Log trajectory characteristics on the happy path
        RCLCPP_DEBUG(this->get_logger(),
            "[PlanJoints] Plan OK: %zu points, planning took %.3fs",
            plan.trajectory_.joint_trajectory.points.size(), dt);

        if (execute) {
            // Validate trajectory before execution
            std::string traj_err;
            if (!validateTrajectory(plan.trajectory_, traj_err)) {
                out_msg = traj_err;
                return false;
            }

            auto exec = move_group_->execute(plan);
            if (exec != moveit::core::MoveItErrorCode::SUCCESS) {
                // Run post-execution diagnostics
                out_msg = diagnoseExecutionFailure(exec);
                return false;
            }
            out_msg = "Joint trajectory executed (took " + std::to_string(dt) + "s)";
        } else {
            out_msg = "Joint trajectory planned (execute=false) (took " + std::to_string(dt) + "s)";
        }
        return true;
    }

    void MotionServer::onMoveJoints(
        const std::shared_ptr<motion_control::srv::MoveJoints::Request> req,
        std::shared_ptr<motion_control::srv::MoveJoints::Response> res) 
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string why;
        if (!ensureInitialized(why)) { res->success = false; res->message = why; return; }

        RCLCPP_DEBUG(this->get_logger(),
        "[MoveJoints] Request: %zu joints, relative=%s, execute=%s",
        req->joints.size(),
        req->is_relative ? "true" : "false",
        req->execute ? "true" : "false");

        std::string msg;
        res->success = planAndExecuteJoints(req->joints, req->is_relative, req->execute, msg);
        res->message = msg;
    }

    void MotionServer::onMoveToPoseViaJoint(
        const std::shared_ptr<motion_control::srv::MoveToPose::Request> req,
        std::shared_ptr<motion_control::srv::MoveToPose::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string error_msg;
        if (!ensureInitialized(error_msg)) { res->success = false; res->message = error_msg; return; }

        auto maybe_target = computeAbsoluteTarget(
            req->x, req->y, req->z,
            req->r1, req->r2, req->r3, req->r4,
            req->rotation_format, req->reference_frame,
            req->is_relative, error_msg);

        if (!maybe_target.has_value()) { res->success = false; res->message = error_msg; return; }
        auto target_pose = maybe_target.value();

        // Validate quaternion
        const auto& q = target_pose.pose.orientation;
        double norm = std::sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
        if (!std::isfinite(norm) || norm < 0.99 || norm > 1.01) {
            res->success = false;
            res->message = "Invalid quaternion after transformation (norm=" + std::to_string(norm) + "). Check rotation inputs.";
            return;
        }

        // Log the resolved target
        RCLCPP_DEBUG(this->get_logger(),
            "[MoveToPoseViaJoint] Target: pos=[%.4f, %.4f, %.4f] quat=[%.4f, %.4f, %.4f, %.4f]",
            target_pose.pose.position.x, target_pose.pose.position.y, target_pose.pose.position.z,
            target_pose.pose.orientation.x, target_pose.pose.orientation.y,
            target_pose.pose.orientation.z, target_pose.pose.orientation.w);

        std::string msg;
        res->success = solveIKAndPlanJoints(target_pose.pose, req->execute, msg);
        res->message = "[IK OK] " + msg;
    }

    void MotionServer::onGetJointState(
        const std::shared_ptr<srv::GetJointState::Request> /*req*/,
        std::shared_ptr<srv::GetJointState::Response> res)
        {
        // Thread-safety: MoveGroupInterface is not designed to be called concurrently
        std::lock_guard<std::mutex> lock(mtx_);

        // Check if MoveGroupInterface is initialized
        std::string why;
        if (!ensureInitialized(why)) {
            res->success = false;
            res->message = why;
            return;
        }

        // Get current joint values from MoveIt
        auto joints = move_group_->getCurrentJointValues();
        res->joints = joints;
        res->success = true;
        res->message = "OK";
        }

    void MotionServer::onGetCurrentPose(
        const std::shared_ptr<motion_control::srv::GetCurrentPose::Request> req,
        std::shared_ptr<motion_control::srv::GetCurrentPose::Response> res)
    {
        // Thread-safety: Protect MoveIt access
        std::lock_guard<std::mutex> lock(mtx_);

        // Handle default frames
        // If child_frame is empty, use the robot's End-Effector
        std::string target_frame = req->child_frame_id;
        if (target_frame.empty()) {
            if (move_group_) {
                target_frame = move_group_->getEndEffectorLink();
            } else {
                res->success = false;
                res->message = "MoveGroup not ready. Cannot determine End-Effector link";
                return;
            }
        }

        // If frame_id is empty, default to "world"
        std::string reference_frame = req->frame_id.empty() ? "world" : req->frame_id;

        try {
            // Lookup Transform via TF2
            geometry_msgs::msg::TransformStamped t;
            t = tf_buffer_->lookupTransform(
                reference_frame,
                target_frame,
                tf2::TimePointZero, // Get the latest available transform
                tf2::durationFromSec(0.5) // Timeout: fail fast if TF tree is broken
            );

            // Fill Standard Pose (Position + Quaternion)
            res->pose.header = t.header;
            res->pose.pose.position.x = t.transform.translation.x;
            res->pose.pose.position.y = t.transform.translation.y;
            res->pose.pose.position.z = t.transform.translation.z;
            res->pose.pose.orientation = t.transform.rotation;

            // Calculate Euler Angles (Always included)
            // Convert GeometryMsg Quaternion to TF2 Quaternion
            tf2::Quaternion q(
                t.transform.rotation.x,
                t.transform.rotation.y,
                t.transform.rotation.z,
                t.transform.rotation.w
            );

            // Convert to RPY (Roll-Pitch-Yaw / Extrinsic XYZ)
            tf2::Matrix3x3 m(q);
            double roll, pitch, yaw;
            m.getRPY(roll, pitch, yaw);
            
            // Fill the float array
            res->euler_rpy = {roll, pitch, yaw};

            res->success = true;
            res->message = "Pose retrieved via TF2 for link: " + target_frame;
        } 
        catch (const tf2::TransformException & ex) {
            // Handle TF2 errors (e.g., frame does not exist)
            res->success = false;
            res->message = std::string("TF2 Error: ") + ex.what();
            RCLCPP_ERROR(this->get_logger(), "%s", res->message.c_str());
        }
    }

    void MotionServer::onSetVirtualCage(
        const std::shared_ptr<srv::SetVirtualCage::Request> req,
        std::shared_ptr<srv::SetVirtualCage::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string why;
        if (!ensureInitialized(why)) { res->success = false; res->message = why; return; }

        std::vector<moveit_msgs::msg::CollisionObject> collision_objects;
        std::vector<std::string> wall_names = {"cage_front", "cage_back", "cage_left", "cage_right", "cage_top", "cage_bottom"};

        if (!req->enable) {
            // // Destroy the cage (MoveIt to REMOVE these objects)
            for (const auto& name : wall_names) {
                moveit_msgs::msg::CollisionObject obj;
                obj.id = name;
                obj.operation = obj.REMOVE;
                collision_objects.push_back(obj);
            }
            planning_scene_->applyCollisionObjects(collision_objects);
            res->success = true; res->message = "Virtual cage removed";
            return;
        }

        // Cage construction
        const double thickness = 0.01; // Walls tickness of 1cm

        // Utility function to generate a wall as a CollisionObject
        auto make_wall = [&](const std::string& id, double cx, double cy, double cz, double sx, double sy, double sz) {
            moveit_msgs::msg::CollisionObject obj;
            obj.header.frame_id = "world";
            obj.id = id;
            obj.operation = obj.ADD;
            
            shape_msgs::msg::SolidPrimitive primitive;
            primitive.type = primitive.BOX;
            primitive.dimensions = {sx, sy, sz};
            
            geometry_msgs::msg::Pose pose;
            pose.position.x = cx; pose.position.y = cy; pose.position.z = cz;
            pose.orientation.w = 1.0;
            
            obj.primitives.push_back(primitive);
            obj.primitive_poses.push_back(pose);
            return obj;
        };

        // Calculation of the cage's internal dimensions
        double dim_x = req->front + req->back;
        double dim_y = req->left + req->right;
        double dim_z = req->top + req->bottom;

        // Calculation of the overall center of the cage
        double cx = (req->front - req->back) / 2.0;
        double cy = (req->left - req->right) / 2.0;
        double cz = (req->top - req->bottom) / 2.0;

        // Front Wall (+X)
        collision_objects.push_back(make_wall("cage_front", req->front + thickness/2, cy, cz, thickness, dim_y, dim_z));
        // Back Wall (-X)
        collision_objects.push_back(make_wall("cage_back", -req->back - thickness/2, cy, cz, thickness, dim_y, dim_z));
        // Left Wall (+Y)
        collision_objects.push_back(make_wall("cage_left", cx, req->left + thickness/2, cz, dim_x + thickness*2, thickness, dim_z));
        // Right Wall (-Y)
        collision_objects.push_back(make_wall("cage_right", cx, -req->right - thickness/2, cz, dim_x + thickness*2, thickness, dim_z));
        // Ceiling (+Z)
        collision_objects.push_back(make_wall("cage_top", cx, cy, req->top + thickness/2, dim_x + thickness*2, dim_y + thickness*2, thickness));
        //  Floor (-Z)
        collision_objects.push_back(make_wall("cage_bottom", cx, cy, -req->bottom - thickness/2, dim_x + thickness*2, dim_y + thickness*2, thickness));

        
        moveit_msgs::msg::PlanningScene planning_scene_msg;
        planning_scene_msg.is_diff = true;
        
        std_msgs::msg::ColorRGBA cage_color;
        cage_color.r = req->r;
        cage_color.g = req->g;
        cage_color.b = req->b;
        cage_color.a = req->a; 

        for (const auto& obj : collision_objects) {
            moveit_msgs::msg::ObjectColor oc;
            oc.id = obj.id;
            oc.color = cage_color;
            planning_scene_msg.object_colors.push_back(oc);
        }
        
        // Apply the cage to the planning scene
        planning_scene_msg.world.collision_objects = collision_objects;
        planning_scene_->applyPlanningScene(planning_scene_msg);

        res->success = true;
        res->message = "Virtual cage successfully activated";
    }

    void MotionServer::onManageBox(
        const std::shared_ptr<srv::ManageBox::Request> req,
        std::shared_ptr<srv::ManageBox::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string why;
        if (!ensureInitialized(why)) { res->success = false; res->message = why; return; }

        // --- 1. Math and Pose Calculations ---
        tf2::Quaternion q;
        if (req->rotation_format == "RPY") {
            q.setRPY(req->r1, req->r2, req->r3);
        } else {
            q = tf2::Quaternion(req->r1, req->r2, req->r3, req->r4);
            q.normalize();
        }

        tf2::Matrix3x3 m(q);
        tf2::Vector3 z_vec = m.getColumn(2);

        double offset = req->size_z / 2.0;
        double cx = req->x + (offset * z_vec.x());
        double cy = req->y + (offset * z_vec.y());
        double cz = req->z + (offset * z_vec.z());

        geometry_msgs::msg::Pose pose;
        pose.position.x = cx;
        pose.position.y = cy;
        pose.position.z = cz;
        pose.orientation.x = q.x();
        pose.orientation.y = q.y();
        pose.orientation.z = q.z();
        pose.orientation.w = q.w();

        // --- 2. Setup MoveIt Object and RViz Marker ---
        moveit_msgs::msg::CollisionObject obj;
        obj.header.frame_id = "world";
        obj.id = req->box_id;

        visualization_msgs::msg::Marker marker;
        marker.header.frame_id = "world";
        marker.header.stamp = this->now();
        marker.ns = "boxes";
        marker.id = getMarkerId(req->box_id); 

        moveit_msgs::msg::PlanningScene planning_scene_msg;
        planning_scene_msg.is_diff = true; 

        // --- 3. Collision vs Visual Logic ---
        if (req->action == "REMOVE") {
            // Remove from both MoveIt and RViz
            obj.operation = moveit_msgs::msg::CollisionObject::REMOVE;
            marker.action = visualization_msgs::msg::Marker::DELETE;
        } else {
            if (req->enable_collision) {
                // COLLISION ON: MoveIt handles it
                obj.operation = moveit_msgs::msg::CollisionObject::ADD;

                shape_msgs::msg::SolidPrimitive primitive;
                primitive.type = primitive.BOX;
                primitive.dimensions = {req->size_x, req->size_y, req->size_z};

                obj.primitives.push_back(primitive);
                obj.primitive_poses.push_back(pose);

                moveit_msgs::msg::ObjectColor oc;
                oc.id = obj.id;
                oc.color.r = req->r;
                oc.color.g = req->g;
                oc.color.b = req->b;
                oc.color.a = req->a;
                planning_scene_msg.object_colors.push_back(oc);

                // Hide RViz marker
                marker.action = visualization_msgs::msg::Marker::DELETE;
            } else {
                // COLLISION OFF: Purely visual in RViz
                obj.operation = moveit_msgs::msg::CollisionObject::REMOVE; 

                marker.action = visualization_msgs::msg::Marker::ADD;
                marker.type = visualization_msgs::msg::Marker::CUBE;
                marker.pose = pose;
                marker.scale.x = req->size_x;
                marker.scale.y = req->size_y;
                marker.scale.z = req->size_z;
                marker.color.r = req->r;
                marker.color.g = req->g;
                marker.color.b = req->b;
                marker.color.a = req->a;
            }
        }

        // --- 4. Apply changes ---
        planning_scene_msg.world.collision_objects.push_back(obj);
        planning_scene_->applyPlanningScene(planning_scene_msg);
        visual_marker_pub_->publish(marker); 

        res->success = true;
        res->message = "Box '" + req->box_id + "' action '" + req->action + "' applied. Collision: " + (req->enable_collision ? "ON" : "OFF");
    }


    void MotionServer::onManageMesh(
        const std::shared_ptr<srv::ManageMesh::Request> req,
        std::shared_ptr<srv::ManageMesh::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string why;
        if (!ensureInitialized(why)) { res->success = false; res->message = why; return; }

        moveit_msgs::msg::CollisionObject obj;
        obj.header.frame_id = "world"; // Placed relative to the world frame
        obj.id = req->mesh_id;

        if (req->action == "REMOVE") {
            obj.operation = obj.REMOVE;
        } else {
            obj.operation = obj.ADD;

            // Create the scale vector
            Eigen::Vector3d scale(req->scale_x, req->scale_y, req->scale_z);
            
            // Load the mesh from the specified path (must start with file:// or package://)
            shapes::Mesh* m = shapes::createMeshFromResource(req->mesh_path, scale);
            
            if (!m) {
                res->success = false;
                res->message = "Failed to load mesh from: " + req->mesh_path;
                RCLCPP_ERROR(this->get_logger(), "%s", res->message.c_str());
                return;
            }

            // Convert to ROS message
            shape_msgs::msg::Mesh mesh_msg;
            shapes::ShapeMsg shape_msg;
            shapes::constructMsgFromShape(m, shape_msg);
            mesh_msg = boost::get<shape_msgs::msg::Mesh>(shape_msg);
            delete m; // Free the memory

            // Calculate the pose (Translation + Rotation)
            tf2::Quaternion q;
            if (req->rotation_format == "RPY") {
                q.setRPY(req->r1, req->r2, req->r3);
            } else {
                q = tf2::Quaternion(req->r1, req->r2, req->r3, req->r4);
                q.normalize();
            }

            geometry_msgs::msg::Pose pose;
            pose.position.x = req->x;
            pose.position.y = req->y;
            pose.position.z = req->z;
            pose.orientation.x = q.x();
            pose.orientation.y = q.y();
            pose.orientation.z = q.z();
            pose.orientation.w = q.w();

            // Add to the CollisionObject
            obj.meshes.push_back(mesh_msg);
            obj.mesh_poses.push_back(pose);
        }

        // Apply to the planning scene
        moveit_msgs::msg::PlanningScene planning_scene_msg;
        planning_scene_msg.is_diff = true;

        planning_scene_msg.world.collision_objects.push_back(obj);

        if (req->action != "REMOVE") {
            moveit_msgs::msg::ObjectColor oc;
            oc.id = obj.id;
            oc.color.r = req->r;
            oc.color.g = req->g;
            oc.color.b = req->b;
            oc.color.a = req->a;
            planning_scene_msg.object_colors.push_back(oc);
        }

        planning_scene_->applyPlanningScene(planning_scene_msg);

        res->success = true;
        res->message = "Mesh '" + req->mesh_id + "' action '" + req->action + "' applied with color.";
        RCLCPP_INFO(this->get_logger(), "%s", res->message.c_str());
    }



}  // namespace motion_control