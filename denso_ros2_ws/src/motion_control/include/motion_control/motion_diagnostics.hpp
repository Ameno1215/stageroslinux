#pragma once

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
#include <moveit/robot_model/joint_model_group.h>
#include <moveit/collision_detection/collision_common.h>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <cmath>
#include <set>
#include <sstream>
#include <algorithm>
#include <iomanip>

namespace motion_control
{

    
    std::string moveitErrorCodeToString(const moveit::core::MoveItErrorCode& code);

    /**
     * @brief Structured report collecting all findings from a planning or execution failure diagnostic.
     * 
     * Aggregates collision details (start, goal, path), IK reachability, singularity metrics
     * (Yoshikawa manipulability and Jacobian condition number), joint limit violations,
     * Cartesian path completion fraction, and timing information into a single object.
     * 
     * When multiple issues are detected simultaneously, all are stored in `all_causes`
     * and the most actionable one is promoted to `primary_cause` using a priority order:
     * collision > IK > singularity > joint limits > timeout.
     * 
     * Call `buildSummary()` after populating the fields to generate a human-readable
     * diagnostic string suitable for logging.
     */
    struct DiagnosticReport
    {
        /**
         * @brief Enumeration of root cause categories for planning/execution failures.
         */
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
            MULTIPLE_CAUSES
        };

        Cause primary_cause = Cause::UNKNOWN;
        std::vector<Cause> all_causes;

        // Start collision details
        bool start_in_collision = false;
        std::vector<std::string> start_collision_pairs;
        std::vector<std::string> start_self_collision_pairs;
        std::vector<std::string> start_env_collision_pairs;

        // Goal collision details
        bool goal_in_collision = false;
        std::vector<std::string> goal_collision_pairs;
        std::vector<std::string> goal_self_collision_pairs;
        std::vector<std::string> goal_env_collision_pairs;

        // IK details 
        bool ik_failed = false;
        std::string ik_detail;

        // Singularity details
        bool near_singularity = false;
        double manipulability = -1.0;
        double condition_number = -1.0;
        double singularity_threshold = 1e-3;

        // Joint limits 
        bool joints_out_of_bounds = false;
        std::vector<std::string> violating_joints;

        // Cartesian path
        double cartesian_fraction = -1.0;
        int    cartesian_fail_waypoint_index = -1;
        geometry_msgs::msg::Pose cartesian_fail_pose;

        // Timing 
        double planning_duration_s = 0.0;

        // Human-readable summary 
        std::string summary;

        /**
         * @brief Builds the human-readable summary string from all populated fields.
         * 
         * Assembles a multi-line diagnostic message including the primary cause,
         * collision pair details (separated into self-collision and environment),
         * IK failure reason, singularity metrics, joint limit violations, Cartesian
         * fraction achieved, and planning duration. Limits output to avoid flooding
         * logs (e.g., max 3 collision pairs shown, with a count of additional ones).
         * 
         * Must be called after all diagnostic checks have populated the report fields.
         */
        void buildSummary();

        /**
         * @brief Converts a Cause enum value to a human-readable string.
         * 
         * @param c The cause enum value to convert.
         * @return std::string Uppercase string representation (e.g., "START_STATE_IN_COLLISION").
         */
        static std::string causeToString(Cause c);
    };


    /**
     * @brief Singularity metrics computed from Jacobian SVD decomposition.
     * 
     * Provides two complementary measures of proximity to a kinematic singularity:
     * - Yoshikawa manipulability (product of singular values — low = singular).
     * - Jacobian condition number (sigma_max / sigma_min — high = singular).
     */
    struct SingularityMetrics {
        double manipulability;    ///< sqrt(det(J * J^T)) — Yoshikawa measure
        double condition_number;  ///< sigma_max / sigma_min of J
        bool   is_singular;       ///< true if manipulability < threshold
    };


    /**
     * @brief Checks whether a given robot state is in collision within the planning scene.
     * 
     * Queries the planning scene for contacts at the given state and classifies
     * each colliding pair as either self-collision (both bodies are robot links)
     * or environment collision (at least one body is an external object).
     * Limited to 10 contact pairs to avoid flooding on complex scenes.
     * 
     * @param scene Const snapshot of the planning scene (typically from getLockedPlanningScene).
     * @param state The robot state to check.
     * @param group_name The planning group to restrict the collision check to.
     * @param collision_pairs Output: all colliding pairs as "bodyA <-> bodyB" strings.
     * @param self_collision_pairs Output: subset of pairs where both bodies are robot links.
     * @param env_collision_pairs Output: subset of pairs involving at least one external object.
     * @return true If the state is in collision (at least one contact pair found).
     * @return false If the state is collision-free.
     */
    bool checkStateCollision(
        const planning_scene::PlanningSceneConstPtr& scene,
        const moveit::core::RobotState& state,
        const std::string& group_name,
        std::vector<std::string>& collision_pairs,
        std::vector<std::string>& self_collision_pairs,
        std::vector<std::string>& env_collision_pairs);

    /**
     * @brief Checks whether joint values in the given state respect model bounds.
     * 
     * Iterates over all active joints in the planning group and compares each
     * variable's position against its declared min/max limits.
     * 
     * @param state The robot state to check.
     * @param group_name The planning group whose joints to verify.
     * @param logger ROS logger used to report offending values.
     * @return std::vector<std::string> Names of joints that exceed their bounds,
     *         formatted as "joint_name=value [min, max]". Empty if all within limits.
     */
    std::vector<std::string> checkJointLimits(
        const moveit::core::RobotState& state,
        const std::string& group_name);

    /**
     * @brief Computes singularity metrics via Jacobian SVD decomposition.
     * 
     * Retrieves the geometric Jacobian (6 x n_joints) at the tip link of the
     * planning group and performs Singular Value Decomposition. Computes the
     * Yoshikawa manipulability measure (product of all singular values) and
     * the condition number (sigma_max / sigma_min). A manipulability below
     * the threshold indicates proximity to a kinematic singularity.
     * 
     * @param state The robot state at which to evaluate the Jacobian.
     * @param jmg Pointer to the joint model group (must not be null).
     * @param threshold Manipulability below this value flags the state as singular (default: 1e-3).
     * @return SingularityMetrics Containing manipulability, condition number, and singular flag.
     *         Returns manipulability=0, condition=inf, is_singular=true if Jacobian computation fails.
     */
    SingularityMetrics computeSingularityMetrics(
        const moveit::core::RobotState& state,
        const moveit::core::JointModelGroup* jmg,
        double threshold = 1e-3);

    /**
     * @brief Runs a full diagnostic analysis after a MoveIt planning failure.
     * 
     * This is the main diagnostic entry point called from service handlers when
     * MoveGroupInterface::plan() returns a non-SUCCESS error code. Performs the
     * following checks in order:
     * 
     * 1. Collision check on the current (start) state.
     * 2. Goal state construction (via IK for pose targets or direct assignment for
     *    joint targets), then collision check, joint limit check, and singularity
     *    analysis on the goal state.
     * 3. Timeout detection from the error code.
     * 4. Primary cause determination using priority: collision > IK > singularity
     *    > joint limits > timeout.
     * 
     * Accepts either a goal pose (for Cartesian targets) or goal joint values
     * (for joint-space targets). Pass nullptr for the unused one.
     * 
     * @param error_code The MoveIt error code returned by plan().
     * @param move_group Reference to the MoveGroupInterface (used to get current state and robot model).
     * @param scene Const snapshot of the planning scene for collision checking.
     * @param group_name The planning group name.
     * @param goal_pose Target Cartesian pose (nullable — pass nullptr for joint-space targets).
     * @param goal_joints Target joint values (nullable — pass nullptr for pose targets).
     * @param planning_duration_s Wall-clock time the planner spent (for the report).
     * @param logger ROS logger for WARN/DEBUG output during analysis.
     * @return DiagnosticReport Fully populated report with summary already built.
     */
    DiagnosticReport diagnosePlanningFailure(
        const moveit::core::MoveItErrorCode& error_code,
        const moveit::planning_interface::MoveGroupInterface& move_group,
        const planning_scene::PlanningSceneConstPtr& scene,
        const std::string& group_name,
        const geometry_msgs::msg::Pose* goal_pose,
        const std::vector<double>* goal_joints,
        double planning_duration_s,
        const rclcpp::Logger& logger);

    /**
     * @brief Runs a diagnostic specifically for Cartesian path failures.
     * 
     * Called when computeCartesianPath returns a fraction below the acceptable
     * threshold. Walks through each waypoint sequentially to pinpoint WHERE
     * and WHY the interpolated path breaks:
     * 
     * 1. Checks the start state for collision.
     * 2. For each waypoint: attempts IK, checks collision, and evaluates
     *    singularity at the resulting joint state. Stops at the first failure
     *    for IK and collision (singularity analysis continues to gather all data).
     * 3. If all individual waypoints are reachable and collision-free, the failure
     *    is attributed to the interpolated path between waypoints (collision zone,
     *    singularity, or joint-limit boundary crossed during interpolation).
     * 
     * The `cartesian_fail_waypoint_index` and `cartesian_fail_pose` fields in the
     * returned report identify the approximate location of the break.
     * 
     * @param move_group Reference to the MoveGroupInterface (used for current state and robot model).
     * @param scene Const snapshot of the planning scene for collision checking.
     * @param group_name The planning group name.
     * @param waypoints Ordered list of Cartesian poses the end-effector must pass through.
     * @param achieved_fraction Fraction of the path successfully computed (0.0 to 1.0).
     * @param planning_duration_s Wall-clock time the Cartesian planner spent.
     * @param logger ROS logger for WARN/DEBUG output during analysis.
     * @return DiagnosticReport Fully populated report with spatial failure localization.
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
