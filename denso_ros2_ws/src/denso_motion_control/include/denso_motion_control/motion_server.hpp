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

namespace denso_motion_control
{

    class MotionServer : public rclcpp::Node
    {
        public:
        explicit MotionServer(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());

        private:
        // Service callbacks
            void onInitRobot(
                const std::shared_ptr<srv::InitRobot::Request> req,
                std::shared_ptr<srv::InitRobot::Response> res);

            void onGoToJoint(
                const std::shared_ptr<srv::GoToJoint::Request> req,
                std::shared_ptr<srv::GoToJoint::Response> res);

            void onGoToPose(
                const std::shared_ptr<srv::GoToPose::Request> req,
                std::shared_ptr<srv::GoToPose::Response> res);

            void onSetScaling(
                const std::shared_ptr<srv::SetScaling::Request> req,
                std::shared_ptr<srv::SetScaling::Response> res);


        // Internal helpers
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

    };

}  // namespace denso_motion_control
