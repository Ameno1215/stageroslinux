import threading
import time
import math
from typing import List, Optional, Dict, Any

import rclpy
from rclpy.node import Node

from fastapi import FastAPI, HTTPException
from pydantic import BaseModel, Field

# NOUVEAUX IMPORTS DES SRV
from denso_motion_control.srv import InitRobot, MoveJoints, MoveToPose, MoveWaypoints, SetScaling, GetJointState, GetCurrentPose, SetVirtualCage
from geometry_msgs.msg import PoseStamped, Pose


# ----------------------------
# Utility functions
# ----------------------------
def euler_to_quaternion(roll, pitch, yaw):
    """Converts RPY to Quaternion to populate geometry_msgs/Pose"""
    cy = math.cos(yaw * 0.5)
    sy = math.sin(yaw * 0.5)
    cp = math.cos(pitch * 0.5)
    sp = math.sin(pitch * 0.5)
    cr = math.cos(roll * 0.5)
    sr = math.sin(roll * 0.5)

    qw = cr * cp * cy + sr * sp * sy
    qx = sr * cp * cy - cr * sp * sy
    qy = cr * sp * cy + sr * cp * sy
    qz = cr * cp * sy - sr * sp * cy
    return qx, qy, qz, qw


# ----------------------------
# Pydantic models (HTTP I/O)
# ----------------------------

class InitReq(BaseModel):
    model: str = "vs060"
    planning_group: str = "arm"
    velocity_scale: float = 0.1
    accel_scale: float = 0.1

class ScalingReq(BaseModel):
    velocity_scale: float = Field(ge=0.0, le=1.0)
    accel_scale: float = Field(ge=0.0, le=1.0)

class JointReq(BaseModel):
    joints: List[float]
    is_relative: bool = False
    execute: bool = True

class MoveToPoseReq(BaseModel):
    x: float
    y: float
    z: float
    r1: float
    r2: float
    r3: float
    r4: float = 0.0
    rotation_format: str = "RPY"
    reference_frame: str = "WORLD"
    is_relative: bool = False
    cartesian_path: bool = False
    execute: bool = True

class WaypointItem(BaseModel):
    x: float
    y: float
    z: float
    r1: float
    r2: float
    r3: float
    r4: float = 0.0

class MoveWaypointsReq(BaseModel):
    waypoints: List[WaypointItem]
    rotation_format: str = "RPY"
    reference_frame: str = "WORLD"
    is_relative: bool = False
    cartesian_path: bool = True
    execute: bool = True

class VirtualCageReq(BaseModel):
    enable: bool
    front: float = 1.0
    back: float = 1.0
    left: float = 1.0
    right: float = 1.0
    top: float = 1.5
    bottom: float = 0.0

    r: float = 0.0
    g: float = 0.6
    b: float = 1.0
    a: float = 0.15


# ----------------------------
# ROS2 client node
# ----------------------------

class DensoMotionRosClient(Node):
    def __init__(self):
        super().__init__("denso_motion_http_bridge")

        self.init_cli = self.create_client(InitRobot, "/init_robot")
        self.scale_cli = self.create_client(SetScaling, "/set_scaling")
        self.get_joints_cli = self.create_client(GetJointState, "/get_joint_state")
        self.get_pose_cli = self.create_client(GetCurrentPose, "/get_current_pose")
        self.move_pose_cli = self.create_client(MoveToPose, "/move_to_pose")
        self.move_joints_cli = self.create_client(MoveJoints, "/move_joints")
        self.move_waypoints_cli = self.create_client(MoveWaypoints, "/move_waypoints")
        self.cage_cli = self.create_client(SetVirtualCage, "/set_virtual_cage")

        # Wait for services
        for cli, name in [
            (self.init_cli, "/init_robot"),
            (self.scale_cli, "/set_scaling"),
            (self.get_joints_cli, "/get_joint_state"),
            (self.get_pose_cli, "/get_current_pose"),
            (self.move_pose_cli, "/move_to_pose"),
            (self.move_joints_cli, "/move_joints"),
            (self.move_waypoints_cli, "/move_waypoints"),
            (self.cage_cli, "/set_virtual_cage"),
        ]:
            if not cli.wait_for_service(timeout_sec=30.0):
                self.get_logger().error(f"Service {name} not available. Is motion_server running?")

    def _wait_for_future(self, fut, timeout: Optional[float]):
        """
        Manual wait because rclpy.Future.result() does not take a timeout argument.
        """
        start_time = time.time()
        while not fut.done():
            # If a timeout is defined and it is exceeded
            if timeout is not None and (time.time() - start_time) > timeout:
                # We cancel the future so as not to leave it hanging.
                fut.cancel()
                raise RuntimeError("Timeout waiting for ROS service response")
            
            time.sleep(0.05)
        
        # Once finished, we retrieve the result
        return fut.result()

    def call_init(self, req: InitReq) -> Dict[str, Any]:
        print(f"DEBUG: Init requested ({req.model})")
        ros_req = InitRobot.Request()
        ros_req.model = str(req.model)
        ros_req.planning_group = str(req.planning_group)
        ros_req.velocity_scale = float(req.velocity_scale)
        ros_req.accel_scale = float(req.accel_scale)

        fut = self.init_cli.call_async(ros_req)
        
        try:
            # 60 seconds for initialization (loading robot model, setting up MoveIt, etc.)
            res = self._wait_for_future(fut, timeout=60.0)
        except Exception as e:
            print(f"ERROR Init: {e}")
            raise RuntimeError(f"InitRobot failed: {e}")
            
        return {"success": bool(res.success), "message": str(res.message)}

    def call_scaling(self, req: ScalingReq) -> Dict[str, Any]:
        ros_req = SetScaling.Request()
        ros_req.velocity_scale = float(req.velocity_scale)
        ros_req.accel_scale = float(req.accel_scale)

        fut = self.scale_cli.call_async(ros_req)
        
        try:
            res = self._wait_for_future(fut, timeout=5.0)
        except Exception as e:
            raise RuntimeError(f"SetScaling failed: {e}")

        return {"success": bool(res.success), "message": str(res.message)}

    def call_move_joints(self, req: JointReq) -> Dict[str, Any]:
        ros_req = MoveJoints.Request()
        ros_req.joints = [float(x) for x in req.joints]
        ros_req.is_relative = bool(req.is_relative)
        ros_req.execute = bool(req.execute)

        fut = self.move_joints_cli.call_async(ros_req)
        try:
            res = self._wait_for_future(fut, timeout=None)
        except Exception as e:
            raise RuntimeError(f"MoveJoints failed: {e}")
        return {"success": bool(res.success), "message": str(res.message)}

    def call_move_to_pose(self, req: MoveToPoseReq) -> Dict[str, Any]:
        ros_req = MoveToPose.Request()
        ros_req.x = float(req.x)
        ros_req.y = float(req.y)
        ros_req.z = float(req.z)
        ros_req.r1 = float(req.r1)
        ros_req.r2 = float(req.r2)
        ros_req.r3 = float(req.r3)
        ros_req.r4 = float(req.r4)
        ros_req.rotation_format = str(req.rotation_format)
        ros_req.reference_frame = str(req.reference_frame)
        ros_req.is_relative = bool(req.is_relative)
        ros_req.cartesian_path = bool(req.cartesian_path)
        ros_req.execute = bool(req.execute)

        fut = self.move_pose_cli.call_async(ros_req)
        try:
            res = self._wait_for_future(fut, timeout=None)
        except Exception as e:
            raise RuntimeError(f"MoveToPose failed: {e}")
        return {"success": bool(res.success), "message": str(res.message)}

    def call_move_waypoints(self, req: MoveWaypointsReq) -> Dict[str, Any]:
        ros_req = MoveWaypoints.Request()
        ros_req.reference_frame = str(req.reference_frame)
        ros_req.is_relative = bool(req.is_relative)
        ros_req.cartesian_path = bool(req.cartesian_path)
        ros_req.execute = bool(req.execute)

        # Construction of the geometry_msgs/Pose table
        for wp in req.waypoints:
            p = Pose()
            p.position.x = float(wp.x)
            p.position.y = float(wp.y)
            p.position.z = float(wp.z)
            
            if req.rotation_format == "RPY":
                qx, qy, qz, qw = euler_to_quaternion(wp.r1, wp.r2, wp.r3)
                p.orientation.x = qx
                p.orientation.y = qy
                p.orientation.z = qz
                p.orientation.w = qw
            else:
                p.orientation.x = float(wp.r1)
                p.orientation.y = float(wp.r2)
                p.orientation.z = float(wp.r3)
                p.orientation.w = float(wp.r4)
            
            ros_req.waypoints.append(p)

        fut = self.move_waypoints_cli.call_async(ros_req)
        try:
            res = self._wait_for_future(fut, timeout=None)
        except Exception as e:
            raise RuntimeError(f"MoveWaypoints failed: {e}")
        return {"success": bool(res.success), "message": str(res.message)}
    
    def call_get_joints(self):
        req = GetJointState.Request()
        fut = self.get_joints_cli.call_async(req)
        try:
            res = self._wait_for_future(fut, timeout=5.0)
        except Exception as e:
            raise RuntimeError(f"GetJointState failed: {e}")
        return {"success": res.success, "message": res.message, "joints": list(res.joints)}
    
    def call_get_pose(self, frame_id: str = "", child_frame_id: str = ""):
        req = GetCurrentPose.Request()
        req.frame_id = frame_id # Reference frame for the returned pose (e.g. "base_link"). If empty, the robot's default frame will be used.
        req.child_frame_id = child_frame_id # (Optional) If specified, the service will attempt to return the pose of this child frame. If empty, the end-effector frame will be used.
        
        fut = self.get_pose_cli.call_async(req)
        try:
            res = self._wait_for_future(fut, timeout=5.0)
        except Exception as e:
            raise RuntimeError(f"GetCurrentPose failed: {e}")

        p = res.pose.pose
        
        # Safe extraction of Euler angles (default to 0.0 if empty for any reason)
        rx, ry, rz = 0.0, 0.0, 0.0
        if len(res.euler_rpy) >= 3:
            rx = res.euler_rpy[0]
            ry = res.euler_rpy[1]
            rz = res.euler_rpy[2]

        return {
            "success": res.success,
            "message": res.message,
            "frame_id": res.pose.header.frame_id,
            "child_frame_id": child_frame_id,
            "position": {"x": p.position.x, "y": p.position.y, "z": p.position.z},
            
            # We return BOTH formats. The client (Windows side) will filter what it needs.
            "orientation_quat": {
                "x": p.orientation.x, 
                "y": p.orientation.y, 
                "z": p.orientation.z, 
                "w": p.orientation.w
            },
            "orientation_euler": {
                "rx": rx, 
                "ry": ry, 
                "rz": rz
            }
        }

    def call_set_virtual_cage(self, req: VirtualCageReq) -> Dict[str, Any]:
        ros_req = SetVirtualCage.Request()
        ros_req.enable = bool(req.enable)
        ros_req.front = float(req.front)
        ros_req.back = float(req.back)
        ros_req.left = float(req.left)
        ros_req.right = float(req.right)
        ros_req.top = float(req.top)
        ros_req.bottom = float(req.bottom)
        ros_req.r = float(req.r)
        ros_req.g = float(req.g)
        ros_req.b = float(req.b)
        ros_req.a = float(req.a)

        fut = self.cage_cli.call_async(ros_req)
        try:
            res = self._wait_for_future(fut, timeout=5.0)
        except Exception as e:
            raise RuntimeError(f"SetVirtualCage failed: {e}")
        return {"success": bool(res.success), "message": str(res.message)}


# ----------------------------
# FastAPI app
# ----------------------------

app = FastAPI(title="Denso Motion HTTP Bridge", version="1.0")

_ros_client: Optional[DensoMotionRosClient] = None

@app.on_event("startup")
def on_startup():
    global _ros_client
    rclpy.init(args=None)
    _ros_client = DensoMotionRosClient()

    # Thread for running ROS
    def _spin():
        while rclpy.ok():
            rclpy.spin_once(_ros_client, timeout_sec=0.1)

    t = threading.Thread(target=_spin, daemon=True)
    t.start()

@app.on_event("shutdown")
def on_shutdown():
    global _ros_client
    if _ros_client is not None:
        _ros_client.destroy_node()
    rclpy.shutdown()

@app.get("/health")
def health():
    return {"ok": True}

@app.post("/init")
def init_robot(req: InitReq):
    try:
        return _ros_client.call_init(req)
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

@app.post("/scaling")
def set_scaling(req: ScalingReq):
    try:
        return _ros_client.call_scaling(req)
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

@app.post("/move_joints")
def move_joints(req: JointReq):
    try:
        return _ros_client.call_move_joints(req)
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

@app.post("/move_to_pose")
def move_to_pose(req: MoveToPoseReq):
    try:
        return _ros_client.call_move_to_pose(req)
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

@app.post("/move_waypoints")
def move_waypoints(req: MoveWaypointsReq):
    try:
        return _ros_client.call_move_waypoints(req)
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

@app.get("/state/joints")
def state_joints():
    return _ros_client.call_get_joints()

@app.get("/state/pose")
def state_pose(frame_id: str = "", child_frame_id: str = ""):
    return _ros_client.call_get_pose(frame_id, child_frame_id)

@app.post("/set_virtual_cage")
def set_virtual_cage(req: VirtualCageReq):
    try:
        return _ros_client.call_set_virtual_cage(req)
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))