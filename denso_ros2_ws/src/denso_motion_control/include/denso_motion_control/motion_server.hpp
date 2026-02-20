#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Transform.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <moveit/robot_trajectory/robot_trajectory.h>
#include <moveit/trajectory_processing/iterative_time_parameterization.h>

#include "denso_motion_control/srv/init_robot.hpp"
#include "denso_motion_control/srv/set_scaling.hpp"
#include "denso_motion_control/srv/get_joint_state.hpp"
#include "denso_motion_control/srv/get_current_pose.hpp"
#include "denso_motion_control/srv/move_to_pose.hpp"
#include "denso_motion_control/srv/move_joints.hpp"
#include "denso_motion_control/srv/move_waypoints.hpp"
#include "denso_motion_control/srv/set_virtual_cage.hpp"


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
            std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
            std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

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
             * @brief Mathematical engine to compute the absolute target pose in the "world" frame.
             * Resolves complex coordinate transformations including relative movements, 
             * Tool Center Point (TCP) offsets, and Euler/Quaternion conversions.
             * @param x Translation along the X axis.
             * @param y Translation along the Y axis.
             * @param z Translation along the Z axis.
             * @param r1 Rotation 1 (Roll for RPY, or X for Quaternion).
             * @param r2 Rotation 2 (Pitch for RPY, or Y for Quaternion).
             * @param r3 Rotation 3 (Yaw for RPY, or Z for Quaternion).
             * @param r4 Rotation 4 (W for Quaternion. Ignored if rot_format is "RPY").
             * @param rot_format String indicating rotation format: "RPY" or "QUAT".
             * @param ref_frame String indicating the reference frame: "WORLD" or "TOOL".
             * @param is_relative If true, treats the inputs as a delta applied to the current pose.
             * @param out_error_msg Reference to a string to output any transformation errors.
             * @return geometry_msgs::msg::PoseStamped The computed absolute pose in the world frame.
             */
            geometry_msgs::msg::PoseStamped computeAbsoluteTarget(
                double x, double y, double z,
                double r1, double r2, double r3, double r4,
                const std::string& rot_format,
                const std::string& ref_frame,
                bool is_relative,
                std::string& out_error_msg);

            /**
             * @brief Universal service callback to move the robot to a target Cartesian pose.
             * Replaces multiple legacy services. Handles absolute positions, relative offsets 
             * (fly-by-wire or crane mode), and both fluid joint-space planning or strict linear Cartesian paths.
             * * @param req Contains target coordinates, formats, reference frames, and motion flags.
             * @param res Returns the success status and informational messages.
             */
            void onMoveToPose(
                const std::shared_ptr<denso_motion_control::srv::MoveToPose::Request> req,
                std::shared_ptr<denso_motion_control::srv::MoveToPose::Response> res);

            /**
             * @brief Service callback to command a movement in the joint space.
             * Moves the robot's axes to specific angles. Supports both absolute joint configurations 
             * and relative angular offsets from the current motor states.
             * * @param req Contains the target joint values and the is_relative behavior flag.
             * @param res Returns the success status of the planning and execution.
             */
            void onMoveJoints(
                const std::shared_ptr<denso_motion_control::srv::MoveJoints::Request> req,
                std::shared_ptr<denso_motion_control::srv::MoveJoints::Response> res);

            /**
             * @brief Service callback to follow a continuous multi-point trajectory (Waypoints).
             * Computes and executes a path passing through a provided list of poses. 
             * Highly useful for welding, gluing, or complex collision avoidance. 
             * Supports relative waypoint chaining (where point N is relative to point N-1).
             * * @param req Contains the list of waypoints and trajectory configuration flags.
             * @param res Returns the success status and the completion percentage of the path.
             */
            void onMoveWaypoints(
                const std::shared_ptr<denso_motion_control::srv::MoveWaypoints::Request> req,
                std::shared_ptr<denso_motion_control::srv::MoveWaypoints::Response> res);

            /**
             * @brief Helper function to interface with MoveIt logic.
             * Sets the target, applies scaling factors, plans the trajectory, and optionally executes it.
             * @param target The final Cartesian pose (geometry_msgs::msg::PoseStamped) the robot should reach.
             * @param execute If true, the robot will move. If false, it only checks if a path exists (Plan only).
             * @param out_msg Reference to a string where status or error messages will be written.
             * @return true If the planning (and execution if requested) was successful.
             * @return false If MoveIt failed to find a plan or failed to execute the trajectory.
             */
            bool planAndMaybeExecutePose(
                const geometry_msgs::msg::PoseStamped& target,
                bool execute,
                std::string& out_msg);

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
             * @brief Retrieves the current Cartesian pose of a specific link relative to a reference frame.
             * Computes the transform using TF2 and returns it in two formats:
             * 1. Standard Pose (Position + Quaternion).
             * 2. Euler Angles (Roll-Pitch-Yaw) in fixed XYZ convention.
             *
             * - If `child_frame_id` is empty, it defaults to the robot's end-effector.
             * - If `frame_id` is empty, it defaults to "world".
             *
             * @param req Contains `child_frame_id` (target) and `frame_id` (reference).
             * @param res Returns the PoseStamped, the Euler angles array, and success status.
             */
            void onGetCurrentPose(
                const std::shared_ptr<denso_motion_control::srv::GetCurrentPose::Request> req,
                std::shared_ptr<denso_motion_control::srv::GetCurrentPose::Response> res);

            /**
             * @brief Service callback to dynamically generate a virtual collision cage around the robot.
             * * Creates 6 walls (CollisionObjects) in the MoveIt planning scene to strictly 
             * restrict the robot's workspace and prevent any part of the arm from exceeding the limits. 
             * The dimensions provided define the exact internal free space originating from the 
             * "world" frame (0, 0, 0). 
             * * IMPORTANT: The thickness of the collision walls is added exclusively to the OUTSIDE 
             * of the specified boundaries. Therefore, the given parameters exactly represent the 
             * permitted internal workspace without any loss of volume due to wall thickness.
             * * @param req Contains the enable flag and the 6 maximum distances (front, back, left, right, top, bottom).
             * @param res Returns the success status of the cage generation or removal.
             */
            void onSetVirtualCage(
                const std::shared_ptr<srv::SetVirtualCage::Request> req,
                std::shared_ptr<srv::SetVirtualCage::Response> res);


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
            rclcpp::Service<srv::SetScaling>::SharedPtr srv_scaling_;
            rclcpp::Service<srv::GetJointState>::SharedPtr srv_get_joints_;
            rclcpp::Service<srv::GetCurrentPose>::SharedPtr srv_get_pose_;
            rclcpp::Service<srv::MoveJoints>::SharedPtr srv_move_joints_;
            rclcpp::Service<srv::MoveToPose>::SharedPtr srv_move_pose_;
            rclcpp::Service<srv::MoveWaypoints>::SharedPtr srv_move_waypoints_;
            rclcpp::Service<srv::SetVirtualCage>::SharedPtr srv_virtual_cage_;
    };

}  // namespace denso_motion_control
