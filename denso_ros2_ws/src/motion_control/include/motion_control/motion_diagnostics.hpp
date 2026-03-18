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
// Usage: Add these methods to your MotionServer class, or keep them as
//        free functions accepting the relevant MoveIt interfaces.
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

// ---------------------------------------------------------------------------
// Diagnostic report: one struct that collects all findings
// ---------------------------------------------------------------------------
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

    // Helper: build the summary string from all fields
    void buildSummary();

    // Helper: cause enum to string
    static std::string causeToString(Cause c);
};


// ---------------------------------------------------------------------------
// Diagnostic functions (designed as static helpers or MotionServer methods)
// ---------------------------------------------------------------------------

/// Check whether a given RobotState is in collision.
/// Populates collision_pairs with "linkA <-> linkB/objectX" strings.
bool checkStateCollision(
    const planning_scene::PlanningSceneConstPtr& scene,
    const moveit::core::RobotState& state,
    const std::string& group_name,
    std::vector<std::string>& collision_pairs);

/// Check whether joint values are within model limits.
/// Returns names of joints that violate bounds.
std::vector<std::string> checkJointLimits(
    const moveit::core::RobotState& state,
    const std::string& group_name);

/// Compute the Jacobian condition number and Yoshikawa manipulability
/// for the given state. High condition number or low manipulability
/// indicates proximity to a kinematic singularity.
struct SingularityMetrics {
    double manipulability;    // det(J * J^T)^0.5  — Yoshikawa measure
    double condition_number;  // sigma_max / sigma_min of J
    bool   is_singular;       // true if manipulability < threshold
};

SingularityMetrics computeSingularityMetrics(
    const moveit::core::RobotState& state,
    const moveit::core::JointModelGroup* jmg,
    double threshold = 1e-3);

/// Run a full diagnostic after a planning failure.
/// This is the main entry point you call from your service handlers.
DiagnosticReport diagnosePlanningFailure(
    const moveit::core::MoveItErrorCode& error_code,
    const moveit::planning_interface::MoveGroupInterface& move_group,
    const planning_scene::PlanningSceneConstPtr& scene,
    const std::string& group_name,
    const geometry_msgs::msg::Pose* goal_pose,       // nullable if joint target
    const std::vector<double>* goal_joints,           // nullable if pose target
    double planning_duration_s,
    const rclcpp::Logger& logger);

/// Run a diagnostic specifically for Cartesian path failures.
/// Walks through the waypoints to find WHERE the path breaks.
DiagnosticReport diagnoseCartesianFailure(
    const moveit::planning_interface::MoveGroupInterface& move_group,
    const planning_scene::PlanningSceneConstPtr& scene,
    const std::string& group_name,
    const std::vector<geometry_msgs::msg::Pose>& waypoints,
    double achieved_fraction,
    double planning_duration_s,
    const rclcpp::Logger& logger);

}  // namespace motion_control
