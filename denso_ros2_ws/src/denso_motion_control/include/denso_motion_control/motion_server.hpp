#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include "denso_motion_control/srv/init_robot.hpp"
#include "denso_motion_control/srv/go_to_joint.hpp"
#include "denso_motion_control/srv/go_to_pose.hpp"
#include "denso_motion_control/srv/set_scaling.hpp"
#include "denso_motion_control/srv/get_joint_state.hpp"
#include "denso_motion_control/srv/get_current_pose.hpp"


namespace denso_motion_control
{
    /**
     * @brief Main motion server for the Denso robot.
     * * This ROS 2 node exposes services to initialize the robot, 
     * command movements (joint space or Cartesian space), and retrieve the current state
     * using the MoveIt 2 planning interface.
     */
    class MotionServer : public rclcpp::Node
    {
        public:
        /**
         * @brief Constructs the MotionServer.
         * * Initializes the node, declares parameters, and creates the service servers.
         * @param options ROS 2 node options.
         */
        explicit MotionServer(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());

        private:
        // Service callbacks
            /**
             * @brief Initializes the MoveIt MoveGroup interface.
             * * This function must be called (via the /init_robot service) before any motion command.
             * It configures the robot model, the planning group, and the velocity/acceleration scaling factors.
             * * @param req Contains the model name (e.g., "vs060") and planning group (e.g., "arm").
             * @param res Returns the success status and a status message.
             */
            void onInitRobot(
                const std::shared_ptr<srv::InitRobot::Request> req,
                std::shared_ptr<srv::InitRobot::Response> res);

            /**
             * @brief Commands a movement to a target joint configuration.
             * * Plans and (optionally) executes a movement to the specified joint angles.
             * * @param req List of target joint angles (must match the number of joints in the group).
             * @param res Returns the success of the planning/execution.
             */
            void onGoToJoint(
                const std::shared_ptr<srv::GoToJoint::Request> req,
                std::shared_ptr<srv::GoToJoint::Response> res);

            /**
             * @brief Commands a movement to a Cartesian pose (Position + Orientation).
             * * Uses inverse kinematics to reach the target position and orientation.
             * * @param req The target PoseStamped including the reference frame_id.
             * @param res Returns the success of the planning/execution.
             */
            void onGoToPose(
                const std::shared_ptr<srv::GoToPose::Request> req,
                std::shared_ptr<srv::GoToPose::Response> res);

            /**
             * @brief Updates the velocity and acceleration scaling factors.
             * * These factors (clamped between 0.0 and 1.0) apply to all subsequent motions.
             * * @param req New scaling factors (velocity_scale, accel_scale).
             * @param res Confirmation message.
             */
            void onSetScaling(
                const std::shared_ptr<srv::SetScaling::Request> req,
                std::shared_ptr<srv::SetScaling::Response> res);

            /**
             * @brief Retrieves the current joint state of the robot.
             * * Queries MoveIt to get the current motor angles.
             * * @param req (Empty request).
             * @param res List of current joint angles.
             */
            void onGetJointState(
                const std::shared_ptr<srv::GetJointState::Request> req,
                std::shared_ptr<srv::GetJointState::Response> res);

            /**
             * @brief Retrieves the current Cartesian pose of the end-effector.
             * * Calculates the position (X,Y,Z) and orientation of the tool tip relative to the base.
             * * @param req Can specify a specific reference frame_id (optional).
             * @param res The current PoseStamped.
             */
            void onGetCurrentPose(
                const std::shared_ptr<srv::GetCurrentPose::Request> req,
                std::shared_ptr<srv::GetCurrentPose::Response> res);



        // Internal helpers
        // Checks if the MoveGroup interface is initialized before processing motion commands
        bool ensureInitialized(std::string& why) const;

        // Thread-safety: MoveGroupInterface is not designed to be called concurrently
        mutable std::mutex mtx_;

        bool initialized_{false};
        std::string model_;
        std::string planning_group_{"arm"};
        double vel_scale_{0.1};
        double accel_scale_{0.1};

        std::shared_ptr<moveit::planning_interface::MoveGroupInterface> move_group_;
        std::shared_ptr<moveit::planning_interface::PlanningSceneInterface> planning_scene_;

        // Services
        rclcpp::Service<srv::InitRobot>::SharedPtr srv_init_;
        rclcpp::Service<srv::GoToJoint>::SharedPtr srv_joint_;
        rclcpp::Service<srv::GoToPose>::SharedPtr srv_pose_;
        rclcpp::Service<srv::SetScaling>::SharedPtr srv_scaling_;
        rclcpp::Service<srv::GetJointState>::SharedPtr srv_get_joints_;
        rclcpp::Service<srv::GetCurrentPose>::SharedPtr srv_get_pose_;


    };

}  // namespace denso_motion_control
