#pragma once

#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <set>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/kinematic_constraints/utils.h>
#include <moveit_msgs/action/move_group_sequence.hpp>

#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Transform.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <moveit/robot_trajectory/robot_trajectory.h>
#include <moveit/trajectory_processing/iterative_time_parameterization.h>
#include <geometric_shapes/mesh_operations.h>
#include <shape_msgs/msg/mesh.hpp>
#include <geometric_shapes/shape_operations.h>
#include <visualization_msgs/msg/marker.hpp>
#include <unordered_map>
#include <moveit/trajectory_processing/time_optimal_trajectory_generation.h>


#include "motion_control/motion_diagnostics.hpp"
#include <moveit/planning_scene_monitor/planning_scene_monitor.h>

#include "motion_control/robot_health_monitor.hpp"


#include "motion_control/srv/init_robot.hpp"
#include "motion_control/srv/set_scaling.hpp"
#include "motion_control/srv/get_scaling.hpp"
#include "motion_control/srv/get_joint_state.hpp"
#include "motion_control/srv/get_current_pose.hpp"
#include "motion_control/srv/move_to_pose.hpp"
#include "motion_control/srv/move_joints.hpp"
#include "motion_control/srv/move_waypoints.hpp"
#include "motion_control/srv/set_virtual_cage.hpp"
#include "motion_control/srv/manage_box.hpp"
#include "motion_control/srv/manage_mesh.hpp"
#include <std_srvs/srv/trigger.hpp>
#include <std_srvs/srv/set_bool.hpp>
#include <geometry_msgs/msg/point.hpp>



namespace motion_control
{
    /**
     * @brief Main motion server for the Denso and Staubli robots.
     * * This ROS 2 node exposes services to initialize the robot,
     * command movements (joint space or Cartesian space), and retrieve the current state
     * using the MoveIt 2 planning interface.
     */
    class MotionServer : public rclcpp::Node
    {
        public:

        static constexpr double kCartesianAcceptThreshold = 0.99;

        // --- Pilz LIN trajectory densification (see densifyCartesianTrajectory) ---
        static constexpr double kDensifyMaxCartStep   = 0.005;  // 30 mm between sampled points
        static constexpr double kDensifyMaxAngStep    = 0.02;   // ~1.1 deg between sampled points
        static constexpr double kDensifyIkTimeout     = 0.01;   // s, per seeded IK solve (close seed)
        static constexpr double kDensifyMaxJointJump  = 0.25;   // rad; above this = IK branch jump
        static constexpr std::size_t kDensifyMaxSubSteps = 50;  // cap per original segment

        // Default TOTG path tolerance (rad) for joint-space waypoint re-timing — how much TOTG
        // may round segment-junction corners. Overridable per-request via MoveWaypoints.path_tolerance.
        static constexpr double kDefaultTotgPathTolerance = 0.05;

        /**
         * @brief Constructs the MotionServer.
         * * Initializes the node, declares parameters, and creates the service servers.
         * @param options ROS 2 node options.
         */
        explicit MotionServer(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());

        private:
            std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
            std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

            std::unique_ptr<RobotHealthMonitor> health_monitor_;
            std::string planning_frame_ = "world";
            // End-effector link, cached at init so the TCP-trace timer never has to
            // call into the (non thread-safe) MoveGroupInterface.
            std::string ee_link_;

            rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr visual_marker_pub_;


            planning_scene_monitor::PlanningSceneMonitorPtr psm_;
            planning_scene::PlanningSceneConstPtr getLockedPlanningScene() const;

            // RViz requires a numeric ID (int32), but MoveIt uses names (string).
            // This dictionary maps string IDs to integer IDs.
            std::unordered_map<std::string, int32_t> marker_ids_;
            int32_t next_marker_id_ = 0;
            std::set<std::string> visual_only_boxes_;

            int32_t getMarkerId(const std::string& name) {
                if (marker_ids_.find(name) == marker_ids_.end()) {
                    marker_ids_[name] = next_marker_id_++;
                }
                return marker_ids_[name];
            }

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
            /**
             * @brief Computes the absolute target pose in the "world" frame.
             *
             * callers cannot accidentally use an uninitialized pose on error.
             * Returns std::nullopt on failure
             * and populates out_error_msg with the reason.
             */
            std::optional<geometry_msgs::msg::PoseStamped> computeAbsoluteTarget(
                double x, double y, double z,
                double r1, double r2, double r3, double r4,
                const std::string& rot_format,
                const std::string& ref_frame,
                bool is_relative,
                std::string& out_error_msg);

            /**
             * @brief Universal service callback to move the robot to a target Cartesian pose.
             * Replaces multiple legacy services. Handles absolute positions, relative offsets
             * (fly-by-wire), and both fluid joint-space planning or strict linear Cartesian paths.
             * * @param req Contains target coordinates, formats, reference frames, and motion flags.
             * @param res Returns the success status and informational messages.
             */
            void onMoveToPose(
                const std::shared_ptr<motion_control::srv::MoveToPose::Request> req,
                std::shared_ptr<motion_control::srv::MoveToPose::Response> res);

            /**
             * @brief Service callback to command a movement in the joint space.
             * Moves the robot's axes to specific angles. Supports both absolute joint configurations
             * and relative angular offsets from the current motor states.
             * * @param req Contains the target joint values and the is_relative behavior flag.
             * @param res Returns the success status of the planning and execution.
             */
            void onMoveJoints(
                const std::shared_ptr<motion_control::srv::MoveJoints::Request> req,
                std::shared_ptr<motion_control::srv::MoveJoints::Response> res);

            /**
             * @brief Service callback to follow a continuous multi-point trajectory (Waypoints).
             * Computes and executes a path passing through a provided list of poses.
             * Highly useful for welding, gluing, or complex collision avoidance.
             * Supports relative waypoint chaining (where point N is relative to point N-1).
             * * @param req Contains the list of waypoints and trajectory configuration flags.
             * @param res Returns the success status and the completion percentage of the path.
             */
            void onMoveWaypoints(
                const std::shared_ptr<motion_control::srv::MoveWaypoints::Request> req,
                std::shared_ptr<motion_control::srv::MoveWaypoints::Response> res);

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
             * @brief Get the velocity and acceleration scaling factors.
             * * These factors (clamped between 0.0 and 1.0)
             * * @param req empty request
             * @param res Confirmation message and values.
             */
            void onGetScaling(
                const std::shared_ptr<srv::GetScaling::Request> /*req*/,
                std::shared_ptr<srv::GetScaling::Response> res);

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
                const std::shared_ptr<motion_control::srv::GetCurrentPose::Request> req,
                std::shared_ptr<motion_control::srv::GetCurrentPose::Response> res);

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

            /**
             * @brief Service callback to add, update, or remove a box in the planning scene.
             *
             * Supports two display modes:
             * 1. Collision enabled: the box is added as a MoveIt CollisionObject, making the
             *    planner treat it as a physical obstacle.
             * 2. Collision disabled: the box is rendered as a purely visual RViz Marker
             *    (no effect on planning).
             *
             * The box position (x, y, z) represents the center of its bottom face.
             * An internal offset along the box's local Z-axis is applied so that the
             * geometric center is correctly placed for MoveIt and RViz.
             * Rotation can be specified in either RPY or Quaternion format.
             *
             * @param req Contains the box ID, action (ADD/REMOVE), dimensions, pose,
             *            rotation format, color (RGBA), and collision toggle.
             * @param res Returns the success status and a descriptive message.
             */
            void onManageBox(
                const std::shared_ptr<srv::ManageBox::Request> req,
                std::shared_ptr<srv::ManageBox::Response> res);

            /**
             * @brief Service callback to add or remove a 3D mesh in the MoveIt planning scene.
             *
             * Loads a mesh file (STL, DAE, OBJ, etc.) from a URI (file:// or package://)
             * and inserts it as a CollisionObject. The mesh can be independently scaled
             * along each axis (X, Y, Z) and positioned with a full 6-DOF pose.
             * Rotation can be specified in either RPY or Quaternion format.
             * An RGBA color is applied via the PlanningScene diff for RViz rendering.
             *
             * @param req Contains the mesh ID, action (ADD/REMOVE), file path, scale factors,
             *            pose, rotation format, and color (RGBA).
             * @param res Returns the success status and a descriptive message.
             */
            void onManageMesh(
                const std::shared_ptr<motion_control::srv::ManageMesh::Request> req,
                std::shared_ptr<motion_control::srv::ManageMesh::Response> res);

            /**
             * @brief Re-times a trajectory with TOTG, enforcing vel_scale_/accel_scale_.
             *
             * Re-times the trajectory using Time-Optimal Trajectory Generation (TOTG),
             * applying the current vel_scale_ and accel_scale_ while respecting the robot's
             * joint velocity/acceleration limits. On TOTG failure the trajectory points are
             * cleared (safety: never execute with raw timestamps).
             *
             * Used by the joint-space waypoint path (onMoveWaypoints, non-Cartesian) to
             * smooth velocity discontinuities at the junctions of concatenated segments.
             * NOTE: Cartesian moves no longer use this — Pilz LIN/Sequence produce trajectories
             * that are already time-parameterized and honor the scaling factors directly.
             *
             * @param trajectory     The robot trajectory to retime (modified in place).
             * @param path_tolerance TOTG path tolerance (rad): how much TOTG may round the
             *                       segment-junction corners to smooth the path. <= 0 falls
             *                       back to kDefaultTotgPathTolerance. The joint-space analogue
             *                       of the Cartesian blend_radius.
             */
            void applyVelocityScaling(
                moveit_msgs::msg::RobotTrajectory& trajectory,
                double path_tolerance = kDefaultTotgPathTolerance);

            /**
             * @brief Plans a straight-line Cartesian motion to a single pose using Pilz LIN.
             *
             * Replaces the old computeCartesianPath pipeline (whose adaptive interpolator
             * returned too few points, producing a joint-interpolated zigzag). Pilz LIN
             * natively yields a dense, already time-parameterized straight-line trajectory.
             *
             * Selects the "pilz_industrial_motion_planner" pipeline + "LIN" planner, applies
             * the given velocity scaling (and the current accel scaling), plans from the
             * current state, then ALWAYS restores the default OMPL pipeline so subsequent
             * joint-space moves are unaffected.
             *
             * @param target       Target end-effector pose (PoseStamped, planning frame).
             * @param vel_scaling  Velocity scaling factor [0..1] to apply for this motion.
             * @param trajectory   Output: the planned LIN trajectory (filled on success).
             * @param out_msg       Status or failure reason.
             * @return true if Pilz LIN planning succeeded, false otherwise.
             */
            bool planCartesianLin(
                const geometry_msgs::msg::PoseStamped& target,
                double vel_scaling,
                moveit_msgs::msg::RobotTrajectory& trajectory,
                std::string& out_msg);

            /**
             * @brief Densifies a Pilz LIN trajectory along its (validated) Cartesian line.
             *
             * Pilz outputs one joint waypoint every sampling_time (0.1s, hardcoded in MoveIt
             * Humble). Between them the controller interpolates in joint space, which deviates
             * from the true straight line — the deviation grows ~quadratically with speed. This
             * re-samples the line finely (linear position + SLERP orientation), solves seeded
             * IK on each sub-point (anchoring every original node to Pilz's own on-line
             * solution), and inherits Pilz's timestamps so the requested Cartesian speed is
             * preserved. Velocities are recomputed by finite difference; endpoints stay at rest.
             *
             * Returns false (leaving @p trajectory untouched) if IK fails or an IK branch jump
             * is detected. The caller treats this as fatal and refuses the move — there is no
             * fallback to the raw (coarse, not finely collision-checked) Pilz trajectory.
             *
             * @param trajectory   In/out: Pilz LIN trajectory, replaced by the dense one on success.
             * @param max_cart_step Max TCP translation (m) between two sampled points.
             * @param max_ang_step  Max TCP rotation (rad) between two sampled points.
             * @param out_msg       Status or failure reason.
             * @return true if densification succeeded, false to keep the original trajectory.
             */
            bool densifyCartesianTrajectory(
                moveit_msgs::msg::RobotTrajectory& trajectory,
                double max_cart_step,
                double max_ang_step,
                std::string& out_msg);

            /**
             * @brief Plans (and optionally executes) a Cartesian waypoint sequence as a
             * single blended Pilz LIN sequence via the /sequence_move_group action.
             *
             * Each waypoint becomes a LIN MotionSequenceItem; blend_radius rounds the
             * corner between consecutive segments (0 = stop at each corner). The last
             * item's blend is forced to 0 (Pilz requirement). When execute is true the
             * action plans and executes; otherwise it only plans.
             *
             * @param waypoints     Ordered absolute target poses (planning frame).
             * @param vel_scaling   Velocity scaling factor [0..1].
             * @param blend_radius  Corner blend radius in meters (0 = stop at corners).
             * @param execute       If true, plan and execute; if false, plan only.
             * @param out_msg        Status or failure reason.
             * @return true on success, false otherwise.
             */
            bool planAndExecuteSequence(
                const std::vector<geometry_msgs::msg::Pose>& waypoints,
                double vel_scaling,
                double blend_radius,
                bool execute,
                std::string& out_msg);

            /**
             * Logs the FK trace of a joint trajectory for Cartesian path diagnostics.
             *
             * The INFO log reports straight-line deviation and path length metrics.
             * Individual FK points are emitted at DEBUG level to avoid flooding normal logs.
             */
            void logCartesianFkTrace(
                const std::string& label,
                const moveit_msgs::msg::RobotTrajectory& trajectory) const;

            /**
             * Validates a trajectory before execution.
             * Checks for degenerate trajectories (too few points, near-zero duration,
             * suspiciously short segments). Returns false and fills out_msg if the
             * trajectory is unsafe to execute.
             */
            bool validateTrajectory(
                const moveit_msgs::msg::RobotTrajectory& trajectory,
                std::string& out_msg) const;

            /**
             * @brief Verifies that a re-timed trajectory is collision-free along its path.
             *
             * The joint-space waypoint path concatenates per-segment OMPL plans (each
             * individually collision-checked) and then re-times the result with TOTG. TOTG's
             * path_tolerance rounds the corners at segment junctions, so the executed path can
             * deviate from the validated one — that deviation is NOT re-checked anywhere else.
             * This method re-validates the FINAL trajectory against the planning scene
             * (self + environment), interpolating between consecutive points so a thin
             * obstacle cannot be "tunneled" through. Returns false (and fills out_msg with the
             * first colliding state) if any sampled state is in collision — caller must refuse
             * execution.
             *
             * @param trajectory The trajectory to validate (positions, in joint order).
             * @param out_msg     First colliding state / contact pairs, on failure.
             * @return true if every sampled state is collision-free, false otherwise.
             */
            bool validateTrajectoryCollisionFree(
                const moveit_msgs::msg::RobotTrajectory& trajectory,
                std::string& out_msg) const;

            /**
             * Runs post-execution diagnostics when a controller error occurs.
             * Logs the current joint state, checks collision and singularity at the
             * interrupted state, and returns a human-readable summary.
             */
            std::string diagnoseExecutionFailure(
                const moveit::core::MoveItErrorCode& exec_code);

            /**
             * @brief Plans and optionally executes a joint-space trajectory.
             *
             * Sets the target joint values (absolute or relative to current state),
             * applies velocity/acceleration scaling, plans via MoveIt, and optionally
             * executes the trajectory. Includes full diagnostic analysis on planning
             * failure and post-execution diagnostics on controller errors.
             *
             * @param joints Target joint values (one per active joint in the planning group).
             * @param is_relative If true, values are treated as deltas from the current joint state.
             * @param execute If true, the planned trajectory is sent to the controller.
             * @param out_msg Reference to a string where status or error messages will be written.
             * @return true If planning (and execution if requested) succeeded.
             * @return false If joint count mismatch, planning failed, trajectory validation
             *         failed, or execution was rejected by the controller.
             */
            // ik_seconds: time spent in the preceding IK search, for logging only.
            // Pass a value >= 0 to prepend "IK=...s, " to the result message; -1 (default)
            // means there was no IK step (e.g. direct joint-space move) and it is omitted.
            bool planAndExecuteJoints(const std::vector<double>& joints, bool is_relative, bool execute, std::string& out_msg, double ik_seconds = -1.0);

            /**
             * @brief Service callback to move the robot to a Cartesian pose via joint-space planning.
             *
             * Resolves the target pose using computeAbsoluteTarget (supporting relative offsets,
             * TOOL/WORLD frames, RPY/Quaternion formats), then solves Inverse Kinematics to obtain
             * a joint configuration and plans entirely in joint space. This avoids the constraints
             * of Cartesian-space planners (singularities, straight-line requirements) at the cost
             * of a non-linear end-effector path.
             *
             * Delegates to solveIKAndPlanJoints after pose resolution and quaternion validation.
             *
             * @param req Contains target coordinates, rotation format, reference frame, and flags.
             * @param res Returns the success status and informational messages prefixed with "[IK OK]".
             */
            void onMoveToPoseViaJoint(const std::shared_ptr<motion_control::srv::MoveToPose::Request> req, std::shared_ptr<motion_control::srv::MoveToPose::Response> res);

            /**
             * @brief Multi-seed IK search returning the best joint configuration (no planning, no execution).
             *
             * Extracts the IK selection logic shared by solveIKAndPlanJoints and onMoveWaypoints.
             * Runs NUM_ATTEMPTS IK queries (the first seeded from seed_state, the rest from random
             * configurations) and filters every candidate against, in order:
             *   1. URDF joint position limits.
             *   2. User-defined joint path constraints (via setPathConstraints).
             *   3. Collision (self + environment) using the current locked planning scene.
             * Surviving solutions are scored by a weighted squared-distance cost relative to
             * seed_state (the weights penalize wrist joints to discourage flips), deduplicated
             * into distinct branches, and the lowest-cost branch is returned.
             *
             * The seed_state serves a double role: it is both the IK seed for the first attempt
             * AND the reference for the "minimize movement" cost. Pass the chained start state
             * (end of the previous segment) when sequencing waypoints so the chosen configuration
             * stays close to the previous one; pass the current robot state for single-target moves.
             *
             *
             * @param target_pose The desired end-effector pose in the planning frame.
             * @param seed_state  IK seed and cost reference (NOT necessarily the current robot state).
             * @param best_joints Output: joint values of the lowest-cost valid branch (one per active joint).
             * @param out_msg     Status message (cost and counts) on success, or failure reason
             *                    with per-filter rejection breakdown.
             * @param all_branches Optional output: all distinct valid branches sorted by ascending
             * cost (best first). Pass nullptr if not needed (e.g. waypoint sequencing);
             * used by the demo mode in solveIKAndPlanJoints to replay every branch.
             * @return true  If at least one valid, collision-free solution was found.
             * @return false If the planning group is unknown, the planning scene is unavailable,
             *         or no candidate survived the filters after NUM_ATTEMPTS.
             */
            bool solveBestIK(
                const geometry_msgs::msg::Pose& target_pose,
                const moveit::core::RobotState& seed_state,
                std::vector<double>& best_joints,
                std::string& out_msg,
                std::vector<std::vector<double>>* all_branches = nullptr);

            /**
             * @brief Solves IK for a target pose and plans/executes the resulting joint trajectory.
             *
             * Primary joint-space entry point for move_to_pose and move_to_pose_via_joint.
             * Thin wrapper that delegates the IK search to solveBestIK (multi-seed search,
             * joint-limit / user-constraint / collision filtering, weighted cost selection),
             * then hands the chosen configuration to planAndExecuteJoints for planning and
             * optional execution.
             *
             * Seeds the IK search from the current robot state, so the selected configuration
             * is biased toward the nearest joint solution and the cost function minimizes motion
             * relative to where the robot is now. Note that this configuration may differ from
             * what a pose-target planner would pick (e.g., elbow-up vs elbow-down).
             *
             * @param target_pose The desired end-effector pose in the planning frame.
             * @param execute If true, the planned trajectory is sent to the controller.
             * @param out_msg Reference to a string where status or error messages will be written.
             * @return true If IK succeeded and planAndExecuteJoints returned success.
             * @return false If the current state is unavailable, solveBestIK found no valid
             *         solution, or joint-space planning/execution failed.
             */
            bool solveIKAndPlanJoints(const geometry_msgs::msg::Pose& target_pose, bool execute, std::string& out_msg);

            /**
             * @brief Applies joint path constraints to restrict joint amplitude during planning.
             *
             * Builds moveit_msgs::msg::Constraints from parallel arrays of joint names
             * and [min, max] bounds, then sets them on the MoveGroupInterface.
             * The caller MUST call move_group_->clearPathConstraints() after planning.
             *
             * @param joint_names  Names of joints to constrain.
             * @param joint_min    Lower bounds in radians (parallel to joint_names).
             * @param joint_max    Upper bounds in radians (parallel to joint_names).
             * @param out_msg      Error message if validation fails.
             * @return true if constraints were applied successfully, false on validation error.
             */
            bool applyJointConstraints(
                const std::vector<std::string>& joint_names,
                const std::vector<double>& joint_min,
                const std::vector<double>& joint_max,
                std::string& out_msg);

            void onClearEnvironment(
                const std::shared_ptr<std_srvs::srv::Trigger::Request> req,
                std::shared_ptr<std_srvs::srv::Trigger::Response> res);

            /**
             * @brief Enables/disables continuous tracing of the tool tip (TCP) path.
             *
             * When enabled, a periodic timer samples the REAL TCP pose via TF
             * (planning_frame -> end-effector link) and appends it to a SPHERE_LIST
             * marker, so the actual travelled path is shown live in RViz regardless of
             * the motion type (joint, Pilz LIN, waypoints, manual jog, external control).
             * Disabling stops sampling but keeps the existing trace displayed.
             *
             * @param req data=true -> START tracing, data=false -> STOP tracing.
             * @param res Success status and message.
             */
            void onSetTcpTrace(
                const std::shared_ptr<std_srvs::srv::SetBool::Request> req,
                std::shared_ptr<std_srvs::srv::SetBool::Response> res);

            /**
             * @brief Clears the recorded TCP trace and erases the marker in RViz.
             */
            void onClearTcpTrace(
                const std::shared_ptr<std_srvs::srv::Trigger::Request> req,
                std::shared_ptr<std_srvs::srv::Trigger::Response> res);

            /**
             * @brief Tells the health monitor whether motors are intentionally powered.
             *
             * The Python bridge owns the operator's motor on/off intent (self.motors_on).
             * It calls this BEFORE an intentional power-off (data=false) so the monitor does
             * NOT flag the resulting drives_powered/motion_possible == FALSE as a hardware
             * fault, and again AFTER a confirmed power-on (data=true) to resume enforcement.
             * Genuine faults (E-stop, in_error, RC8 error) remain detected in all cases.
             *
             * @param req data=true -> motors expected ON (enforce drives-powered fault),
             *            data=false -> motors deliberately OFF (suppress drives-powered fault).
             * @param res Success status and message.
             */
            void onSetDrivesExpected(
                const std::shared_ptr<std_srvs::srv::SetBool::Request> req,
                std::shared_ptr<std_srvs::srv::SetBool::Response> res);

            /**
             * @brief Timer callback: samples the current TCP position via TF and, if it
             * moved more than kTraceMinDist since the last sample, appends it to the trace
             * and republishes the marker. Runs in a dedicated callback group so it keeps
             * sampling even while a (blocking) motion service callback is executing.
             */
            void sampleTcpTrace();

            /**
             * @brief Publishes the current TCP trace as a SPHERE_LIST marker (ADD), or an
             * empty/DELETE marker to clear it. Caller must hold trace_mtx_.
             */
            void publishTraceMarker(bool clear = false);

            /**
             * @brief Retrieves the joint position limits of the planning group.
             *
             * Queries MoveIt's RobotModel to extract the [min, max] bounds of every
             * active joint. Output vectors are resized to nb_joints. For continuous
             * (unbounded) joints, falls back to [-pi, pi] with a warning.
             *
             * @param joint_min   Output vector of lower position limits (rad or m).
             * @param joint_max   Output vector of upper position limits, parallel to joint_min.
             * @param joint_names Optional output vector of joint names. Pass nullptr if not needed.
             * @param out_msg     Status or error message.
             * @return true on success, false if not initialized or planning group unknown.
             */
            bool getJointLimits(
                std::vector<double>& joint_min,
                std::vector<double>& joint_max,
                std::vector<std::string>* joint_names,
                std::string& out_msg) const;



            // Internal helpers
            // Checks if the MoveGroup interface is initialized before processing motion commands
            bool ensureInitialized(std::string& why) const;
            bool ensureMoveGroupInitialized(std::string& why) const;
            bool getRobotFaultMessage(std::string& why) const;

            // Thread-safety: MoveGroupInterface is not designed to be called concurrently
            mutable std::mutex mtx_;

            bool initialized_{false};
            std::string model_;
            std::string planning_group_{"arm"};
            double vel_scale_{0.1};
            double accel_scale_{0.1};
            // Relative velocity scaling [0..1] applied to Cartesian (Pilz LIN/Sequence)
            // moves only. 0 = fall back to vel_scale_ (joint-space scaling).
            double cartesian_vel_scale_{0.0};

            std::shared_ptr<moveit::planning_interface::MoveGroupInterface> move_group_;
            std::shared_ptr<moveit::planning_interface::PlanningSceneInterface> planning_scene_;

            // Dedicated node + action client for the Pilz MoveGroupSequence action.
            // Kept on a separate node so we can spin it to completion inside a service
            // callback without deadlocking the main node's executor.
            rclcpp::Node::SharedPtr seq_node_;
            rclcpp_action::Client<moveit_msgs::action::MoveGroupSequence>::SharedPtr seq_client_;

            // Services
            rclcpp::Service<srv::InitRobot>::SharedPtr srv_init_;
            rclcpp::Service<srv::SetScaling>::SharedPtr srv_scaling_;
            rclcpp::Service<srv::GetScaling>::SharedPtr srv_get_scaling_;
            rclcpp::Service<srv::GetJointState>::SharedPtr srv_get_joints_;
            rclcpp::Service<srv::GetCurrentPose>::SharedPtr srv_get_pose_;
            rclcpp::Service<srv::MoveJoints>::SharedPtr srv_move_joints_;
            rclcpp::Service<srv::MoveToPose>::SharedPtr srv_move_pose_;
            rclcpp::Service<srv::MoveToPose>::SharedPtr srv_move_pose_via_joint_;
            rclcpp::Service<srv::MoveWaypoints>::SharedPtr srv_move_waypoints_;
            rclcpp::Service<srv::SetVirtualCage>::SharedPtr srv_virtual_cage_;
            rclcpp::Service<srv::ManageBox>::SharedPtr srv_manage_box_;
            rclcpp::Service<motion_control::srv::ManageMesh>::SharedPtr srv_manage_mesh_;
            rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr srv_clear_env_;

            // --- Continuous TCP path tracing ---
            // The timer and the trace services live in a dedicated callback group so the
            // MultiThreadedExecutor can run them on a separate thread, i.e. keep sampling
            // the TCP while a (blocking) motion service callback holds the default group.
            rclcpp::CallbackGroup::SharedPtr trace_cb_group_;
            rclcpp::TimerBase::SharedPtr trace_timer_;
            rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr srv_set_trace_;
            rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr srv_clear_trace_;
            rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr srv_set_drives_expected_;

            std::mutex trace_mtx_;                              // guards the fields below
            bool trace_enabled_{false};
            std::vector<geometry_msgs::msg::Point> trace_points_;

            // Minimum TCP displacement (m) between two recorded points (anti-spam at rest).
            static constexpr double kTraceMinDist = 0.002;      // 2 mm (< sphere diameter so spheres overlap)
            // Beyond this single-step displacement (m) we assume a discontinuity/teleport
            // and start a fresh trace rather than drawing a straight line across space.
            static constexpr double kTraceMaxJump = 0.25;       // 25 cm
            // Hard cap on stored points; oldest are dropped (moving window).
            static constexpr size_t kTraceMaxPoints = 20000;
    };

}  // namespace motion_control
