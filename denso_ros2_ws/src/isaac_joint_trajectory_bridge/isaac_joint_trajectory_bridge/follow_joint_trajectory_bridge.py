import math
import threading
import time
from typing import Dict, List, Sequence

import rclpy
from control_msgs.action import FollowJointTrajectory
from control_msgs.msg import JointTrajectoryControllerState
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from sensor_msgs.msg import JointState
from trajectory_msgs.msg import JointTrajectoryPoint


class IsaacFollowJointTrajectoryBridge(Node):
    def __init__(self) -> None:
        super().__init__('follow_joint_trajectory_bridge')

        self.declare_parameter('action_name', 'follow_joint_trajectory')
        self.declare_parameter('joint_command_topic', '/joint_command')
        self.declare_parameter('joint_states_topic', '/joint_states')
        self.declare_parameter('joint_names', [])
        self.declare_parameter('goal_tolerance', 0.02)
        self.declare_parameter('goal_time_tolerance', 1.0)
        self.declare_parameter('state_publish_rate_hz', 20.0)

        self._action_name = self.get_parameter('action_name').get_parameter_value().string_value
        self._joint_command_topic = self.get_parameter('joint_command_topic').get_parameter_value().string_value
        self._joint_states_topic = self.get_parameter('joint_states_topic').get_parameter_value().string_value
        self._configured_joint_names = list(
            self.get_parameter('joint_names').get_parameter_value().string_array_value
        )
        self._goal_tolerance = self.get_parameter('goal_tolerance').get_parameter_value().double_value
        self._goal_time_tolerance = self.get_parameter('goal_time_tolerance').get_parameter_value().double_value
        self._state_publish_rate_hz = max(
            self.get_parameter('state_publish_rate_hz').get_parameter_value().double_value, 1.0
        )

        self._joint_command_pub = self.create_publisher(JointState, self._joint_command_topic, 10)
        self._joint_states_sub = self.create_subscription(
            JointState,
            self._joint_states_topic,
            self._on_joint_state,
            50,
        )
        self._state_pub = self.create_publisher(
            JointTrajectoryControllerState,
            '~/controller_state',
            10,
        )

        self._cb_group = ReentrantCallbackGroup()
        self._action_server = ActionServer(
            self,
            FollowJointTrajectory,
            self._action_name,
            execute_callback=self._execute_callback,
            goal_callback=self._goal_callback,
            cancel_callback=self._cancel_callback,
            callback_group=self._cb_group,
        )

        self._state_lock = threading.Lock()
        self._latest_positions: Dict[str, float] = {}
        self._latest_velocities: Dict[str, float] = {}
        self._active_goal_lock = threading.Lock()
        self._goal_active = False

        self.get_logger().info(
            f'Isaac trajectory bridge ready: action={self._action_name}, '
            f'joint_command={self._joint_command_topic}, joint_states={self._joint_states_topic}'
        )

    def destroy_node(self):
        self._action_server.destroy()
        super().destroy_node()

    def _goal_callback(self, goal_request: FollowJointTrajectory.Goal):
        if self._goal_active:
            self.get_logger().warn('Rejected trajectory goal because another goal is already active.')
            return GoalResponse.REJECT

        if not goal_request.trajectory.points:
            self.get_logger().error('Rejected empty trajectory goal.')
            return GoalResponse.REJECT

        if not goal_request.trajectory.joint_names:
            self.get_logger().error('Rejected trajectory goal without joint names.')
            return GoalResponse.REJECT

        if self._configured_joint_names:
            expected = set(self._configured_joint_names)
            actual = set(goal_request.trajectory.joint_names)
            if actual != expected:
                self.get_logger().error(
                    f'Rejected goal with unexpected joint names. '
                    f'expected={self._configured_joint_names} actual={goal_request.trajectory.joint_names}'
                )
                return GoalResponse.REJECT

        return GoalResponse.ACCEPT

    def _cancel_callback(self, _goal_handle):
        self.get_logger().warn('Cancellation requested for active Isaac trajectory.')
        return CancelResponse.ACCEPT

    def _on_joint_state(self, msg: JointState) -> None:
        with self._state_lock:
            for index, name in enumerate(msg.name):
                if index < len(msg.position):
                    self._latest_positions[name] = msg.position[index]
                if index < len(msg.velocity):
                    self._latest_velocities[name] = msg.velocity[index]

    def _execute_callback(self, goal_handle):
        with self._active_goal_lock:
            self._goal_active = True
            trajectory = goal_handle.request.trajectory
            joint_names = list(trajectory.joint_names)
            result = FollowJointTrajectory.Result()

            try:
                self.get_logger().info(f'Executing Isaac trajectory with {len(trajectory.points)} points.')

                if not self._wait_for_initial_state(joint_names):
                    result.error_code = FollowJointTrajectory.Result.INVALID_GOAL
                    result.error_string = 'No /joint_states received from Isaac Sim.'
                    goal_handle.abort()
                    return result

                start_time = time.monotonic()
                previous_time_from_start = 0.0

                for point in trajectory.points:
                    if goal_handle.is_cancel_requested:
                        result.error_code = FollowJointTrajectory.Result.SUCCESSFUL
                        result.error_string = 'Goal cancelled.'
                        goal_handle.canceled()
                        return result

                    if len(point.positions) != len(joint_names):
                        result.error_code = FollowJointTrajectory.Result.INVALID_GOAL
                        result.error_string = 'Each trajectory point must provide one position per joint.'
                        goal_handle.abort()
                        return result

                    time_from_start = self._duration_to_sec(point.time_from_start)
                    if time_from_start + 1e-6 < previous_time_from_start:
                        result.error_code = FollowJointTrajectory.Result.INVALID_GOAL
                        result.error_string = 'Trajectory time_from_start must be monotonic.'
                        goal_handle.abort()
                        return result

                    self._sleep_until(start_time + time_from_start, goal_handle)
                    if goal_handle.is_cancel_requested:
                        result.error_code = FollowJointTrajectory.Result.SUCCESSFUL
                        result.error_string = 'Goal cancelled.'
                        goal_handle.canceled()
                        return result

                    self._publish_joint_command(joint_names, point)
                    self._publish_feedback(goal_handle, joint_names, point)
                    previous_time_from_start = time_from_start

                final_point = trajectory.points[-1]
                if not self._wait_until_goal_reached(goal_handle, joint_names, final_point):
                    result.error_code = FollowJointTrajectory.Result.GOAL_TOLERANCE_VIOLATED
                    result.error_string = 'Isaac Sim did not reach the requested goal tolerance in time.'
                    goal_handle.abort()
                    return result

                self._publish_feedback(goal_handle, joint_names, final_point)
                result.error_code = FollowJointTrajectory.Result.SUCCESSFUL
                goal_handle.succeed()
                return result
            finally:
                self._goal_active = False

    def _wait_for_initial_state(self, joint_names: Sequence[str]) -> bool:
        deadline = time.monotonic() + 5.0
        while time.monotonic() < deadline:
            with self._state_lock:
                if all(name in self._latest_positions for name in joint_names):
                    return True
            time.sleep(0.05)
        return False

    def _wait_until_goal_reached(self, goal_handle, joint_names: Sequence[str], final_point: JointTrajectoryPoint) -> bool:
        deadline = time.monotonic() + max(self._goal_time_tolerance, 0.1)
        while time.monotonic() < deadline:
            if goal_handle.is_cancel_requested:
                return False

            actual = self._get_positions(joint_names)
            if len(actual) == len(final_point.positions):
                errors = [
                    abs(actual[index] - final_point.positions[index])
                    for index in range(len(final_point.positions))
                    if not math.isnan(actual[index])
                ]
                if errors and max(errors) <= self._goal_tolerance:
                    return True

            self._publish_feedback(goal_handle, joint_names, final_point)
            time.sleep(1.0 / self._state_publish_rate_hz)

        return False

    def _sleep_until(self, deadline: float, goal_handle) -> None:
        while not goal_handle.is_cancel_requested:
            remaining = deadline - time.monotonic()
            if remaining <= 0.0:
                return
            time.sleep(min(remaining, 0.02))

    def _publish_joint_command(self, joint_names: Sequence[str], point: JointTrajectoryPoint) -> None:
        msg = JointState()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.name = list(joint_names)
        msg.position = list(point.positions)
        if len(point.velocities) == len(joint_names):
            msg.velocity = list(point.velocities)
        if len(point.effort) == len(joint_names):
            msg.effort = list(point.effort)
        self._joint_command_pub.publish(msg)

    def _publish_feedback(self, goal_handle, joint_names: Sequence[str], desired: JointTrajectoryPoint) -> None:
        actual_positions = self._get_positions(joint_names)
        actual_velocities = self._get_velocities(joint_names)

        feedback = FollowJointTrajectory.Feedback()
        feedback.joint_names = list(joint_names)
        feedback.desired = self._copy_point(desired)
        feedback.actual = JointTrajectoryPoint()
        feedback.actual.positions = actual_positions
        feedback.actual.velocities = actual_velocities
        feedback.error = JointTrajectoryPoint()

        if len(desired.positions) == len(actual_positions):
            feedback.error.positions = [
                desired.positions[index] - actual_positions[index]
                if not math.isnan(actual_positions[index]) else float('nan')
                for index in range(len(desired.positions))
            ]

        goal_handle.publish_feedback(feedback)

        state_msg = JointTrajectoryControllerState()
        state_msg.header.stamp = self.get_clock().now().to_msg()
        state_msg.joint_names = list(joint_names)
        state_msg.reference = feedback.desired
        state_msg.actual = feedback.actual
        state_msg.error = feedback.error
        self._state_pub.publish(state_msg)

    def _get_positions(self, joint_names: Sequence[str]) -> List[float]:
        with self._state_lock:
            return [self._latest_positions.get(name, float('nan')) for name in joint_names]

    def _get_velocities(self, joint_names: Sequence[str]) -> List[float]:
        with self._state_lock:
            return [self._latest_velocities.get(name, float('nan')) for name in joint_names]

    @staticmethod
    def _copy_point(point: JointTrajectoryPoint) -> JointTrajectoryPoint:
        clone = JointTrajectoryPoint()
        clone.positions = list(point.positions)
        clone.velocities = list(point.velocities)
        clone.accelerations = list(point.accelerations)
        clone.effort = list(point.effort)
        clone.time_from_start = point.time_from_start
        return clone

    @staticmethod
    def _duration_to_sec(duration_msg) -> float:
        return float(duration_msg.sec) + float(duration_msg.nanosec) / 1_000_000_000.0


def main(args=None) -> None:
    rclpy.init(args=args)
    node = IsaacFollowJointTrajectoryBridge()
    executor = MultiThreadedExecutor()
    executor.add_node(node)

    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        executor.shutdown()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
