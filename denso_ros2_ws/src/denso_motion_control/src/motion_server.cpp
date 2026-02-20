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

            move_group_->setMaxVelocityScalingFactor(vel_scale_);
            move_group_->setMaxAccelerationScalingFactor(accel_scale_);

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
        auto code = move_group_->plan(plan);

        // Always clear pose targets to avoid accidental reuse
        move_group_->clearPoseTargets();

        if (code != moveit::core::MoveItErrorCode::SUCCESS) {
            out_msg = "Planning failed for pose target";
            return false;
        }

        // If execute flag is true, execute the planned trajectory
        if (execute) {
            auto exec_code = move_group_->execute(plan);
            if (exec_code != moveit::core::MoveItErrorCode::SUCCESS) {
            out_msg = "Execution failed for pose target";
            return false;
            }
            out_msg = "Planned and executed pose target successfully";
            return true;
        }

        out_msg = "Planned pose target successfully (execute=false)";
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
            return final_pose; // Retournera 0, à gérer dans l'appelant
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
            const double jump_threshold = 0.0;
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

        // Retrieve the current pose. It will serve as the basis for calculation (Point 0)
        geometry_msgs::msg::PoseStamped current_pose_msg = move_group_->getCurrentPose();
        tf2::Transform current_base_tf;
        tf2::fromMsg(current_pose_msg.pose, current_base_tf);

        // Vector that will store absolute targets understandable by MoveIt
        std::vector<geometry_msgs::msg::Pose> absolute_waypoints;

        // Conversion loop: Transform each waypoint into an absolute WORLD pose
        for (const auto& wp : req->waypoints) {
            tf2::Transform wp_tf;
            tf2::fromMsg(wp, wp_tf); // Converts the ROS point into a mathematical object
            tf2::Transform target_tf;

            if (req->is_relative) {
                if (req->reference_frame == "TOOL") {
                    // Post-multiplication: the delta is applied along the current axes of the tool
                    target_tf = current_base_tf * wp_tf;
                } else { // WORLD
                    // Pre-multiplication: the delta is applied along the fixed axes of the part
                    target_tf.setOrigin(current_base_tf.getOrigin() + wp_tf.getOrigin());
                    target_tf.setRotation(wp_tf.getRotation() * current_base_tf.getRotation());
                    target_tf.getRotation().normalize();
                }
            } else {
                // If the coordinates are already absolute, we take them as they are
                target_tf = wp_tf;
            }

            // The point we just calculated becomes the new starting point
            // for the next point (only useful if is_relative is True)
            current_base_tf = target_tf;

            // Convert it back to ROS format and store it
            geometry_msgs::msg::Pose abs_pose;
            tf2::toMsg(target_tf, abs_pose);
            absolute_waypoints.push_back(abs_pose);
        }

        // Speed ​​application
        move_group_->setMaxVelocityScalingFactor(vel_scale_);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);

        // Route planning
        if (req->cartesian_path) {
            // Cartesian mode: Drawing in pure straight lines between each point
            moveit_msgs::msg::RobotTrajectory trajectory;
            const double jump_threshold = 0.0; // Disables joint "jumps"
            const double eef_step = 0.01;      // A point calculated every 1 cm

            double fraction = move_group_->computeCartesianPath(absolute_waypoints, eef_step, jump_threshold, trajectory);

            if (fraction < 0.95) { // If MoveIt gets stuck along the way (zone boundary, etc.)
                res->success = false;
                res->message = "Cartesian path impossible or incomplete. Calculated fraction:" + std::to_string(fraction);
                return;
            }

            if (req->execute) {
                auto exec_code = move_group_->execute(trajectory);
                res->success = (exec_code == moveit::core::MoveItErrorCode::SUCCESS);
                res->message = res->success ? "Trajectory waypoints executed successfully." : "Failed to execute trajectory.";
            } else {
                res->success = true;
                res->message = "Trajectory waypoints planned at " + std::to_string(fraction * 100.0) + "%";
            }
        } else {
            // Non-Cartesian mode (Fluid Joint Space):
            //  MoveIt (with the standard OMPL planner) does not easily handle uninterrupted transitions
            // through a series of strict poses without creating straight lines.
            // To maintain a robust system, an alert is sent.
            res->success = false;
            res->message = "Joint space tracking (cartesian_path=false) is not natively supported. Please use cartesian_path=true.";
            return;
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
        if (move_group_->plan(plan) != moveit::core::MoveItErrorCode::SUCCESS) {
            res->success = false; res->message = "Failed to plan joint trajectory."; return;
        }

        if (req->execute) {
            res->success = (move_group_->execute(plan) == moveit::core::MoveItErrorCode::SUCCESS);
            res->message = res->success ? "Joint trajectory executed successfully." : "Failed to execute joint trajectory.";
        } else {
            res->success = true; res->message = "Joint trajectory planned.";
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





}  // namespace denso_motion_control



