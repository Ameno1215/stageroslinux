#pragma once

// =============================================================================
// motion_diagnostics.hpp
//
// Diagnostic utilities for MotionServer — provides structured failure analysis
// after MoveIt planning/execution errors. Distinguishes between:
//   - Collision (start, goal, or along trajectory)
//   - IK / Unreachable pose
//   - Singularity (via Jacobian condition number / manipulability)
//   - Joint limits violation
//   - Cartesian path partial failure (with spatial localization)
//   - Timeout / generic planning failure
//
// =============================================================================

#include <string>
#include <vector>
#include <optional>

#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_monitor/planning_scene_monitor.h>
#include <moveit/robot_state/robot_state.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit_msgs/msg/move_it_error_codes.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <Eigen/Dense>

namespace motion_control
{
    struct DiagnosticReport
    {
        // ---- High-level verdict ----
        enum class Cause {
            UNKNOWN,
            START_COLLISION,
            GOAL_COLLISION,
            PATH_COLLISION,
            IK_UNREACHABLE,
            SINGULARITY,
            JOINT_LIMITS,
            TIMEOUT,
            CONTROL_FAILED,
            CARTESIAN_INCOMPLETE,
            CONSTRAINT_VIOLATION,
            MULTIPLE_CAUSES       // When several issues are detected simultaneously
        };

        Cause primary_cause = Cause::UNKNOWN;
        std::vector<Cause> all_causes;          // May contain multiple findings

        // ---- Collision details ----
        bool start_in_collision = false;
        bool goal_in_collision  = false;
        std::vector<std::string> collision_pairs;  // e.g. "link3 <-> box_obstacle"

        // ---- IK details ----
        bool ik_failed = false;
        std::string ik_detail;                     // e.g. "KDL returned no solution after 5 attempts"

        // ---- Singularity details ----
        bool near_singularity = false;
        double manipulability = -1.0;              // Yoshikawa manipulability measure
        double condition_number = -1.0;            // Jacobian condition number (high = bad)
        double singularity_threshold = 1e-3;       // Below this manipulability → singular

        // ---- Joint limits ----
        bool joints_out_of_bounds = false;
        std::vector<std::string> violating_joints; // Names of joints exceeding limits

        // ---- Cartesian path ----
        double cartesian_fraction = -1.0;
        int    cartesian_fail_waypoint_index = -1; // Index of first waypoint that couldn't be reached
        geometry_msgs::msg::Pose cartesian_fail_pose; // Approximate pose where interpolation broke

        // ---- Timing ----
        double planning_duration_s = 0.0;

        // ---- Human-readable summary ----
        std::string summary;                       // Full diagnostic message

        /**
         * @brief Assembles the human-readable summary string from all populated fields.
         * 
         * Iterates over collision details, IK status, singularity metrics, joint-limit
         * violations, Cartesian fraction, and timing to produce a structured multi-line
         * diagnostic message stored in the `summary` member.
         */
        void buildSummary();

         /**
         * @brief Converts a Cause enum value to its string representation.
         * 
         * @param c The diagnostic cause to convert.
         * @return std::string Human-readable name of the cause (e.g. "GOAL_STATE_IN_COLLISION").
         */
        static std::string causeToString(Cause c);
    };


    // ---------------------------------------------------------------------------
    // Diagnostic functions (designed as static helpers or MotionServer methods)
    // ---------------------------------------------------------------------------

    /**
     * @brief Checks whether a given robot state is in collision within the planning scene.
     * 
     * Performs a collision query against the full planning scene (self-collisions
     * and environment obstacles). When a collision is detected, the colliding
     * pairs are returned as human-readable strings (e.g. "link3 <-> box_obstacle").
     * 
     * @param scene A const snapshot of the planning scene to check against.
     * @param state The robot state to evaluate for collisions.
     * @param group_name Name of the joint model group to restrict the check to.
     * @param collision_pairs Output vector filled with "bodyA <-> bodyB" strings for each contact (up to 10).
     * @return true If the state is in collision.
     * @return false If the state is collision-free.
     */
    bool checkStateCollision(
        const planning_scene::PlanningSceneConstPtr& scene,
        const moveit::core::RobotState& state,
        const std::string& group_name,
        std::vector<std::string>& collision_pairs);

    /**
     * @brief Checks whether any joint in the given state exceeds its model-defined position limits.
     * 
     * Iterates over all active joints of the specified group and compares their
     * current values against the URDF-defined bounds. Each violation is returned
     * as a formatted string containing the joint name, its current value, and
     * the allowed range (e.g. "joint_3=3.25 [-3.14, 3.14]").
     * 
     * @param state The robot state whose joint positions are checked.
     * @param group_name Name of the joint model group to inspect.
     * @return std::vector<std::string> List of violation descriptions (empty if all joints are within bounds).
     */
    std::vector<std::string> checkJointLimits(
        const moveit::core::RobotState& state,
        const std::string& group_name);

    struct SingularityMetrics {
        double manipulability;    // det(J * J^T)^0.5  — Yoshikawa measure
        double condition_number;  // sigma_max / sigma_min of J
        bool   is_singular;       // true if manipulability < threshold
    };

    /**
     * @brief Computes singularity metrics for a given robot state using the geometric Jacobian.
     * 
     * Evaluates proximity to kinematic singularities by performing an SVD
     * decomposition of the Jacobian matrix and deriving two complementary measures:
     * 1. Yoshikawa manipulability: product of singular values (low = singular).
     * 2. Jacobian condition number: ratio of largest to smallest singular value (high = singular).
     * 
     * @param state The robot state at which to evaluate the Jacobian.
     * @param jmg Pointer to the joint model group (determines which joints and tip link are used).
     * @param threshold Manipulability value below which the state is considered singular (default: 1e-3).
     * @return SingularityMetrics Struct containing manipulability, condition number, and a boolean singular flag.
     */
    SingularityMetrics computeSingularityMetrics(
        const moveit::core::RobotState& state,
        const moveit::core::JointModelGroup* jmg,
        double threshold = 1e-3);

    /**
     * @brief Runs a comprehensive diagnostic analysis after a MoveIt planning failure.
     * 
     * This is the main diagnostic entry point for joint-space and pose-target planning.
     * It systematically checks the start state for collisions, attempts IK on the goal
     * pose (if provided), verifies the goal state for collisions, joint-limit violations,
     * and singularity proximity. A prioritized primary cause is determined from all
     * detected issues, and a human-readable summary is generated.
     * 
     * @param error_code The MoveIt error code returned by the failed plan() call.
     * @param move_group Reference to the MoveGroupInterface (used to retrieve the current state and robot model).
     * @param scene A const snapshot of the planning scene for collision checking.
     * @param group_name Name of the joint model group being planned for.
     * @param goal_pose Pointer to the target Cartesian pose (nullable if planning in joint space).
     * @param goal_joints Pointer to the target joint values (nullable if planning to a pose target).
     * @param planning_duration_s Wall-clock time the planner spent before failing.
     * @param logger ROS logger used to emit warnings during the diagnostic process.
     * @return DiagnosticReport Structured report containing all findings, the primary cause, and a summary string.
     */
    DiagnosticReport diagnosePlanningFailure(
        const moveit::core::MoveItErrorCode& error_code,
        const moveit::planning_interface::MoveGroupInterface& move_group,
        const planning_scene::PlanningSceneConstPtr& scene,
        const std::string& group_name,
        const geometry_msgs::msg::Pose* goal_pose,       // nullable if joint target
        const std::vector<double>* goal_joints,           // nullable if pose target
        double planning_duration_s,
        const rclcpp::Logger& logger);

    /**
     * @brief Runs a diagnostic analysis specifically tailored to Cartesian path planning failures.
     * 
     * Walks through each waypoint sequentially, attempting IK and checking for
     * collisions and singularity at each step. This localizes the failure spatially
     * by identifying the first waypoint where IK fails, a collision occurs, or
     * the arm enters a singular configuration. If all individual waypoints are
     * reachable, the failure is attributed to the interpolated path between them
     * (e.g. passing through a collision zone or singularity during linear interpolation).
     * 
     * @param move_group Reference to the MoveGroupInterface (used to retrieve the current state and robot model).
     * @param scene A const snapshot of the planning scene for collision checking.
     * @param group_name Name of the joint model group being planned for.
     * @param waypoints Ordered list of Cartesian poses the end-effector was expected to follow.
     * @param achieved_fraction The fraction (0.0–1.0) of the path that was successfully computed before failure.
     * @param planning_duration_s Wall-clock time the Cartesian planner spent.
     * @param logger ROS logger used to emit warnings during the diagnostic process.
     * @return DiagnosticReport Structured report including the failure waypoint index, pose, cause, and summary.
     */
    DiagnosticReport diagnoseCartesianFailure(
        const moveit::planning_interface::MoveGroupInterface& move_group,
        const planning_scene::PlanningSceneConstPtr& scene,
        const std::string& group_name,
        const std::vector<geometry_msgs::msg::Pose>& waypoints,
        double achieved_fraction,
        double planning_duration_s,
        const rclcpp::Logger& logger);

}  // namespace motion_control
