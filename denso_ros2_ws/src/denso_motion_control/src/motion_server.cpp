#include "denso_motion_control/motion_server.hpp"

#include <sstream>

namespace denso_motion_control
{

    MotionServer::MotionServer(const rclcpp::NodeOptions& options)
    : rclcpp::Node("denso_motion_server", options)
    {
        // Declare parameters for convenient launch-time configuration
        this->declare_parameter<std::string>("model", "vs060");
        this->declare_parameter<std::string>("planning_group", "arm");
        this->declare_parameter<double>("velocity_scale", 0.1);
        this->declare_parameter<double>("accel_scale", 0.1);
        this->set_parameter(rclcpp::Parameter("use_sim_time", true));

        // Initialisation du système d'écoute TF
        tf_buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
        tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

        srv_init_ = this->create_service<srv::InitRobot>(
            "init_robot",
            std::bind(&MotionServer::onInitRobot, this, std::placeholders::_1, std::placeholders::_2));

        srv_move_joints_ = this->create_service<srv::MoveJoints>(
            "move_joints",
            std::bind(&MotionServer::onMoveJoints, this, std::placeholders::_1, std::placeholders::_2));

        srv_move_pose_ = this->create_service<srv::MoveToPose>(
            "move_to_pose",
            std::bind(&MotionServer::onMoveToPose, this, std::placeholders::_1, std::placeholders::_2));

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

        RCLCPP_INFO(this->get_logger(), "MotionServer ready. Call /init_robot first");
    }

    std::string MotionServer:: moveitErrorCodeToString(const moveit::core::MoveItErrorCode& code)
    {
        switch (code.val) {
            case moveit::core::MoveItErrorCode::SUCCESS: return "SUCCESS";
            case moveit::core::MoveItErrorCode::FAILURE: return "FAILURE";
            case moveit::core::MoveItErrorCode::PLANNING_FAILED: return "PLANNING_FAILED: No path found";
            case moveit::core::MoveItErrorCode::INVALID_MOTION_PLAN: return "INVALID_MOTION_PLAN: Trajectory contains errors";
            case moveit::core::MoveItErrorCode::MOTION_PLAN_INVALIDATED_BY_ENVIRONMENT_CHANGE: return "PLAN_INVALIDATED: Environment changed during execution";
            case moveit::core::MoveItErrorCode::CONTROL_FAILED: return "CONTROL_FAILED: Controller execution failed";
            case moveit::core::MoveItErrorCode::UNABLE_TO_AQUIRE_SENSOR_DATA: return "UNABLE_TO_AQUIRE_SENSOR_DATA";
            case moveit::core::MoveItErrorCode::TIMED_OUT: return "TIMED_OUT: Planning took too long";
            case moveit::core::MoveItErrorCode::PREEMPTED: return "PREEMPTED: Motion interrupted";
            case moveit::core::MoveItErrorCode::INVALID_OBJECT_NAME: return "INVALID_OBJECT_NAME: Unrecognized frame or object";
            case moveit::core::MoveItErrorCode::FRAME_TRANSFORM_FAILURE: return "FRAME_TRANSFORM_FAILURE: TF tree error";
            case moveit::core::MoveItErrorCode::COLLISION_CHECKING_UNAVAILABLE: return "COLLISION_CHECKING_UNAVAILABLE";
            case moveit::core::MoveItErrorCode::ROBOT_STATE_STALE: return "ROBOT_STATE_STALE: Robot state is too old";
            case moveit::core::MoveItErrorCode::SENSOR_INFO_STALE: return "SENSOR_INFO_STALE: Sensor data is too old";
            case moveit::core::MoveItErrorCode::CRASH: return "CRASH: Internal MoveIt crash";
            case moveit::core::MoveItErrorCode::ABORT: return "ABORT: Motion aborted";
            case moveit::core::MoveItErrorCode::NO_IK_SOLUTION: return "NO_IK_SOLUTION: Position unreachable (Out of workspace or singularity)";
            default: return "UNKNOWN_ERROR_CODE";
        }
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

            move_group_->setMaxVelocityScalingFactor(vel_scale_);
            move_group_->setMaxAccelerationScalingFactor(accel_scale_);

            // TODO configurable at launch
            // Find best parameters for fast and reliable planning. These can be tuned based on the robot's performance and environment complexity.
            move_group_->setPlanningTime(5.0); // Maximum time (in seconds) allowed for planning.
            move_group_->setNumPlanningAttempts(10); //Number of attempts simultaneously launched by MoveIt to find a valid plan (with different random seeds).
            move_group_->allowReplanning(true); // If true, MoveIt will automatically try to replan if the current plan fails during execution (e.g., due to a new obstacle).

            // Log available joints and links
            auto names = move_group_->getRobotModel()->getLinkModelNames();
            RCLCPP_INFO(this->get_logger(), "--- Links available for this robot ---");
            for (const auto& name : names) {
                RCLCPP_INFO(this->get_logger(), "Link: %s", name.c_str());
            }
            RCLCPP_INFO(this->get_logger(), "---------------------------------------");

            std::ostringstream oss;
            oss << "Initialized with model=" << model_
                << ", group=" << planning_group_
                << ", vel_scale=" << vel_scale_
                << ", accel_scale=" << accel_scale_
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

    bool MotionServer::planAndMaybeExecutePose(
        const geometry_msgs::msg::PoseStamped& target,
        bool execute,
        std::string& out_msg)
    {
        move_group_->setPoseTarget(target);

        move_group_->setMaxVelocityScalingFactor(vel_scale_);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);

        // Plan the motion to the Cartesian pose target
        moveit::planning_interface::MoveGroupInterface::Plan plan;
        auto start_time = std::chrono::high_resolution_clock::now();
        auto code = move_group_->plan(plan);
        auto end_time = std::chrono::high_resolution_clock::now();
        double planning_duration = std::chrono::duration<double>(end_time - start_time).count();

        if (code != moveit::core::MoveItErrorCode::SUCCESS) {
            out_msg = "Planning failed: " + moveitErrorCodeToString(code) + " (took " + std::to_string(planning_duration) + " seconds)";
            return false;
        }

        // Always clear pose targets to avoid accidental reuse
        move_group_->clearPoseTargets();

        // If execute flag is true, execute the planned trajectory
        if (execute) {
            auto exec_code = move_group_->execute(plan);
            if (exec_code != moveit::core::MoveItErrorCode::SUCCESS) {
            out_msg = "Execution failed for pose target" + moveitErrorCodeToString(exec_code) + " (took " + std::to_string(planning_duration) + " seconds)";
            return false;
            }
            out_msg = "Planned and executed pose target successfully (took " + std::to_string(planning_duration) + " seconds)";
            return true;
        }

        out_msg = "Planned pose target successfully (execute=false) (took " + std::to_string(planning_duration) + " seconds)";
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

    geometry_msgs::msg::PoseStamped MotionServer::computeAbsoluteTarget(
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
        geometry_msgs::msg::PoseStamped current_pose_msg = move_group_->getCurrentPose();
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
            return final_pose;
        }

        tf2::toMsg(result_transform, final_pose.pose);
        return final_pose;
    }

    void MotionServer::onMoveToPose(
        const std::shared_ptr<denso_motion_control::srv::MoveToPose::Request> req,
        std::shared_ptr<denso_motion_control::srv::MoveToPose::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string error_msg;
        if (!ensureInitialized(error_msg)) { res->success = false; res->message = error_msg; return; }

        // Calculating the absolute target using our mathematical engine
        geometry_msgs::msg::PoseStamped target_pose = computeAbsoluteTarget(
            req->x, req->y, req->z, req->r1, req->r2, req->r3, req->r4,
            req->rotation_format, req->reference_frame, req->is_relative, error_msg
        );

        if (!error_msg.empty()) { res->success = false; res->message = error_msg; return; }

        // Speed ​​application
        move_group_->setMaxVelocityScalingFactor(vel_scale_);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);

        // Choice of planning method: Straight line (Cartesian) VS Curve (Joint Space)
        if (req->cartesian_path) 
        {
            std::vector<geometry_msgs::msg::Pose> waypoints;
            waypoints.push_back(target_pose.pose);

            moveit_msgs::msg::RobotTrajectory trajectory;
            const double jump_threshold = 1.5; // 1.5 radian jump threshold (prevents joint "jumps")
            const double eef_step = 0.01; // 1 cm resolution

            double fraction = move_group_->computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);

            if (fraction < 0.95) { // If MoveIt was unable to draw at least 95% of the straight line
                res->success = false;
                res->message = "Impossible Cartesian path (collision or singularity) Fraction: " + std::to_string(fraction);
                return;
            }

            if (req->execute) {
                auto exec_code = move_group_->execute(trajectory);
                res->success = (exec_code == moveit::core::MoveItErrorCode::SUCCESS);
                res->message = res->success ? "Cartesian path executed." : "Failed to execute cartesian path";
            } else {
                res->success = true;
                res->message = "Cartesian path planned at " + std::to_string(fraction * 100.0) + "%";
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
        const std::shared_ptr<denso_motion_control::srv::MoveWaypoints::Request> req,
        std::shared_ptr<denso_motion_control::srv::MoveWaypoints::Response> res)
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
        geometry_msgs::msg::PoseStamped current_pose_msg = move_group_->getCurrentPose();
        tf2::Transform current_base_tf;
        tf2::fromMsg(current_pose_msg.pose, current_base_tf);

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

            // THE SECRET LIES HERE: The point we just calculated becomes the 
            // new reference base for the next point!
            current_base_tf = target_tf;

            geometry_msgs::msg::Pose abs_pose;
            tf2::toMsg(target_tf, abs_pose);
            absolute_waypoints.push_back(abs_pose);
        }

        // Apply velocity and acceleration scaling factors
        move_group_->setMaxVelocityScalingFactor(vel_scale_);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);

        // Cartesian path planning
        if (req->cartesian_path) {
            moveit_msgs::msg::RobotTrajectory trajectory;
            const double jump_threshold = 1.5; 
            const double eef_step = 0.01;      

            auto start_time = std::chrono::high_resolution_clock::now();
            double fraction = move_group_->computeCartesianPath(absolute_waypoints, eef_step, jump_threshold, trajectory);
            auto end_time = std::chrono::high_resolution_clock::now();
            double planning_duration = std::chrono::duration<double>(end_time - start_time).count();

            if (fraction < 0.95) { 
                res->success = false;
                res->message = "Cartesian path impossible or incomplete. Calculated fraction: " + std::to_string(fraction) + " (took " + std::to_string(planning_duration) + " seconds)";
                return;
            }

            if (req->execute) {
                auto exec_code = move_group_->execute(trajectory);
                res->success = (exec_code == moveit::core::MoveItErrorCode::SUCCESS);
                res->message = res->success ? "Trajectory waypoints executed successfully. (took " + std::to_string(planning_duration) + " seconds)" : "Failed to execute trajectory: " + moveitErrorCodeToString(exec_code) + " (took " + std::to_string(planning_duration) + " seconds)";
            } else {
                res->success = true;
                res->message = "Trajectory waypoints planned at " + std::to_string(fraction * 100.0) + "%" + " (execute=false) (took " + std::to_string(planning_duration) + " seconds)";
            }
        } else {
            res->success = false;
            res->message = "Joint space tracking (cartesian_path=false) is not supported for waypoints. Please use cartesian_path=true.";
        }
    }

    void MotionServer::onMoveJoints(
        const std::shared_ptr<denso_motion_control::srv::MoveJoints::Request> req,
        std::shared_ptr<denso_motion_control::srv::MoveJoints::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string why;
        if (!ensureInitialized(why)) { res->success = false; res->message = why; return; }

        const auto* jmg = move_group_->getRobotModel()->getJointModelGroup(planning_group_);
        const auto& names = jmg->getVariableNames();

        if (req->joints.size() != names.size()) {
            res->success = false;
            res->message = "Incorrect joint size. Expected: " + std::to_string(names.size());
            return;
        }

        std::map<std::string, double> target;
        std::vector<double> current_joints = move_group_->getCurrentJointValues();

        for (size_t i = 0; i < names.size(); ++i) {
            if (req->is_relative) {
                target[names[i]] = current_joints[i] + req->joints[i]; // Relative addition
            } else {
                target[names[i]] = req->joints[i]; // Absolute pose
            }
        }

        move_group_->setJointValueTarget(target);
        move_group_->setMaxVelocityScalingFactor(vel_scale_);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);

        moveit::planning_interface::MoveGroupInterface::Plan plan;

        auto start_time = std::chrono::high_resolution_clock::now();
        moveit::core::MoveItErrorCode plan_code = move_group_->plan(plan);

        auto end_time = std::chrono::high_resolution_clock::now();
        double planning_duration = std::chrono::duration<double>(end_time - start_time).count();
        
        if (plan_code != moveit::core::MoveItErrorCode::SUCCESS) {
            res->success = false; 
            res->message = "Failed to plan joint trajectory: " + moveitErrorCodeToString(plan_code) + " (took " + std::to_string(planning_duration) + " seconds)"; 
            return;
        }

        if (req->execute) {
            moveit::core::MoveItErrorCode exec_code = move_group_->execute(plan);
            
            if (exec_code == moveit::core::MoveItErrorCode::SUCCESS) {
                res->success = true;
                res->message = "Joint trajectory executed successfully (took " + std::to_string(planning_duration) + " seconds).";
            } else {
                res->success = false;
                res->message = "Failed to execute joint trajectory: " + moveitErrorCodeToString(exec_code) + " (took " + std::to_string(planning_duration) + " seconds)";
            }
        } else {
            res->success = true; 
            res->message = "Joint trajectory planned successfully (execute=false) (took " + std::to_string(planning_duration) + " seconds).";
        }
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
        const std::shared_ptr<denso_motion_control::srv::GetCurrentPose::Request> req,
        std::shared_ptr<denso_motion_control::srv::GetCurrentPose::Response> res)
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
                tf2::TimePointZero // Get the latest available transform
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

        moveit_msgs::msg::CollisionObject obj;
        obj.header.frame_id = "world";
        obj.id = req->box_id;

        if (req->action == "REMOVE") {
            obj.operation = obj.REMOVE;
        } else {
            obj.operation = obj.ADD;

            // Convert to Quaternion
            tf2::Quaternion q;
            if (req->rotation_format == "RPY") {
                q.setRPY(req->r1, req->r2, req->r3);
            } else {
                q = tf2::Quaternion(req->r1, req->r2, req->r3, req->r4);
                q.normalize();
            }

            // Extract Z vector easily with tf2
            tf2::Matrix3x3 m(q);
            tf2::Vector3 z_vec = m.getColumn(2);

            // Calculate Center (Move FORWARD into the object by half its Z-size)
            double offset = req->size_z / 2.0;
            double cx = req->x + (offset * z_vec.x());
            double cy = req->y + (offset * z_vec.y());
            double cz = req->z + (offset * z_vec.z());

            shape_msgs::msg::SolidPrimitive primitive;
            primitive.type = primitive.BOX;
            primitive.dimensions = {req->size_x, req->size_y, req->size_z};

            geometry_msgs::msg::Pose pose;
            pose.position.x = cx;
            pose.position.y = cy;
            pose.position.z = cz;
            pose.orientation.x = q.x();
            pose.orientation.y = q.y();
            pose.orientation.z = q.z();
            pose.orientation.w = q.w();

            obj.primitives.push_back(primitive);
            obj.primitive_poses.push_back(pose);
        }

        // Apply to the planning scene
        std::vector<moveit_msgs::msg::CollisionObject> collision_objects;
        collision_objects.push_back(obj);
        planning_scene_->applyCollisionObjects(collision_objects);

        res->success = true;
        res->message = "Box '" + req->box_id + "' action '" + req->action + "' applied.";
        RCLCPP_INFO(this->get_logger(), "%s", res->message.c_str());
    }



}  // namespace denso_motion_control



