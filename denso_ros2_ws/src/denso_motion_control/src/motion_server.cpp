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

        srv_joint_ = this->create_service<srv::GoToJoint>(
            "goto_joint",
            std::bind(&MotionServer::onGoToJoint, this, std::placeholders::_1, std::placeholders::_2));

        srv_pose_ = this->create_service<srv::GoToPose>(
            "goto_cartesian",
            std::bind(&MotionServer::onGoToPose, this, std::placeholders::_1, std::placeholders::_2));

        srv_scaling_ = this->create_service<srv::SetScaling>(
            "set_scaling",
            std::bind(&MotionServer::onSetScaling, this, std::placeholders::_1, std::placeholders::_2));

            srv_get_joints_ = this->create_service<srv::GetJointState>(
            "get_joint_state",
            std::bind(&MotionServer::onGetJointState, this, std::placeholders::_1, std::placeholders::_2));

        srv_get_pose_ = this->create_service<srv::GetCurrentPose>(
            "get_current_pose",
            std::bind(&MotionServer::onGetCurrentPose, this, std::placeholders::_1, std::placeholders::_2));



        RCLCPP_INFO(this->get_logger(), "MotionServer ready. Call /init_robot first.");
    }

    bool MotionServer::ensureInitialized(std::string& why) const
        {
        if (!initialized_ || !move_group_) {
            why = "Robot not initialized. Call service /init_robot first.";
            return false;
        }
        return true;
    }

    void MotionServer::onInitRobot(
        const std::shared_ptr<srv::InitRobot::Request> req,
        std::shared_ptr<srv::InitRobot::Response> res)
        {
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

    void MotionServer::onGoToJoint(
        const std::shared_ptr<srv::GoToJoint::Request> req,
        std::shared_ptr<srv::GoToJoint::Response> res)
        {
        // Thread-safety: MoveGroupInterface is not designed to be called concurrently
        std::lock_guard<std::mutex> lock(mtx_);

        std::string why;
        // Check if MoveGroupInterface is initialized
        if (!ensureInitialized(why)) {
            res->success = false;
            res->message = why;
            return;
        }

        // Validate joint target
        if (req->joints.empty()) {
            res->success = false;
            res->message = "Empty joint target.";
            return;
        }

        // Get joint names from MoveIt to ensure correct mapping
        const auto* jmg = move_group_->getRobotModel()->getJointModelGroup(planning_group_);
        const auto& names = jmg->getVariableNames();

        // Check if the provided joint values match the expected size
        if (req->joints.size() != names.size()) {
        res->success = false;
        res->message = "Joint target size mismatch. Expected " + std::to_string(names.size());
        return;
        }

        // Create a map of joint names to target values
        std::map<std::string, double> target;
        for (size_t i = 0; i < names.size(); ++i) {
        target[names[i]] = req->joints[i];
        }
        move_group_->setJointValueTarget(target);


        move_group_->setMaxVelocityScalingFactor(vel_scale_);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);

        // Plan the motion to the joint target
        moveit::planning_interface::MoveGroupInterface::Plan plan;
        auto code = move_group_->plan(plan);

        if (code != moveit::core::MoveItErrorCode::SUCCESS) {
            res->success = false;
            res->message = "Planning failed for joint target.";
            return;
        }

        // If execute flag is true, execute the planned trajectory
        if (req->execute) {
            auto exec_code = move_group_->execute(plan);
            if (exec_code != moveit::core::MoveItErrorCode::SUCCESS) {
            res->success = false;
            res->message = "Execution failed for joint target.";
            return;
            }
            res->success = true;
            res->message = "Planned and executed joint target successfully.";
        } else {
            res->success = true;
            res->message = "Planned joint target successfully (execute=false).";
        }
    }

    void MotionServer::onGoToPose(
        const std::shared_ptr<srv::GoToPose::Request> req,
        std::shared_ptr<srv::GoToPose::Response> res)
        {
        // Thread-safety: MoveGroupInterface is not designed to be called concurrently
        std::lock_guard<std::mutex> lock(mtx_);

        std::string why;
        if (!ensureInitialized(why)) {
            res->success = false;
            res->message = why;
            return;
        }

        move_group_->setPoseTarget(req->target);

        move_group_->setMaxVelocityScalingFactor(vel_scale_);
        move_group_->setMaxAccelerationScalingFactor(accel_scale_);

        // Plan the motion to the Cartesian pose target
        moveit::planning_interface::MoveGroupInterface::Plan plan;
        auto code = move_group_->plan(plan);

        // Always clear pose targets to avoid accidental reuse
        move_group_->clearPoseTargets();

        if (code != moveit::core::MoveItErrorCode::SUCCESS) {
            res->success = false;
            res->message = "Planning failed for pose target.";
            return;
        }

        // If execute flag is true, execute the planned trajectory
        if (req->execute) {
            auto exec_code = move_group_->execute(plan);
            if (exec_code != moveit::core::MoveItErrorCode::SUCCESS) {
            res->success = false;
            res->message = "Execution failed for pose target.";
            return;
            }
            res->success = true;
            res->message = "Planned and executed pose target successfully.";
        } else {
            res->success = true;
            res->message = "Planned pose target successfully (execute=false).";
        }
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
            << ". This will be used for all subsequent motions.";

        res->success = true;
        res->message = oss.str();

        RCLCPP_INFO(this->get_logger(), "%s", res->message.c_str());
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
        const std::shared_ptr<srv::GetCurrentPose::Request> req,
        std::shared_ptr<srv::GetCurrentPose::Response> res)
    {
        std::lock_guard<std::mutex> lock(mtx_);

        // Determine the target frame
        std::string target_frame = req->child_frame_id;
        
        // If no child_frame_id provided, default to end-effector link
        if (target_frame.empty()) {
            if (move_group_) {
                target_frame = move_group_->getEndEffectorLink();
            } else {
                res->success = false;
                res->message = "MoveGroup not ready and no child_frame_id provided.";
                return;
            }
        }

        // Determine the reference frame (default to "world" if not provided)
        std::string reference_frame = req->frame_id;
        if (reference_frame.empty()) {
            reference_frame = "world"; // Ou "base_link" selon ta préférence
        }

        // Calculate the transform from reference_frame to target_frame using TF2
        try {
            geometry_msgs::msg::TransformStamped t;

            t = tf_buffer_->lookupTransform(
                reference_frame, 
                target_frame, 
                tf2::TimePointZero
            );

            // Fill the response pose  
            res->pose.header = t.header;
            res->pose.pose.position.x = t.transform.translation.x;
            res->pose.pose.position.y = t.transform.translation.y;
            res->pose.pose.position.z = t.transform.translation.z;
            res->pose.pose.orientation = t.transform.rotation;

            res->success = true;
            res->message = "Pose retrieved via TF2 for link: " + target_frame;
        } 
        catch (const tf2::TransformException & ex) {
            // If TF2 lookup fails, return an error message
            res->success = false;
            res->message = std::string("TF2 Error: ") + ex.what();
            RCLCPP_ERROR(this->get_logger(), "%s", res->message.c_str());
        }
    }


}  // namespace denso_motion_control



