import threading
import time
from typing import List, Optional, Dict, Any

import rclpy
from rclpy.node import Node

from fastapi import FastAPI, HTTPException
from pydantic import BaseModel, Field

from denso_motion_control.srv import InitRobot, GoToJoint, GoToPose, SetScaling, GetJointState, GetCurrentPose, GoToEuler
from geometry_msgs.msg import PoseStamped


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
    execute: bool = True


class PoseReq(BaseModel):
    frame_id: str = "base_link"
    position: Dict[str, float]
    orientation: Dict[str, float]
    execute: bool = True

class EulerReq(BaseModel):
    frame_id: str = "base_link"
    x: float
    y: float
    z: float
    rx: float
    ry: float
    rz: float
    execute: bool = True


# ----------------------------
# ROS2 client node
# ----------------------------

class DensoMotionRosClient(Node):
    def __init__(self):
        super().__init__("denso_motion_http_bridge")

        self.init_cli = self.create_client(InitRobot, "/init_robot")
        self.joint_cli = self.create_client(GoToJoint, "/goto_joint")
        self.pose_cli = self.create_client(GoToPose, "/goto_cartesian")
        self.scale_cli = self.create_client(SetScaling, "/set_scaling")
        self.get_joints_cli = self.create_client(GetJointState, "/get_joint_state")
        self.get_pose_cli = self.create_client(GetCurrentPose, "/get_current_pose")
        self.euler_world_cli = self.create_client(GoToEuler, "/goto_euler_world")
        self.euler_local_cli = self.create_client(GoToEuler, "/move_relative_tool")
        self.euler_world_rel_cli = self.create_client(GoToEuler, "/move_relative_world")

        # Wait for services (30s)
        for cli, name in [
            (self.init_cli, "/init_robot"),
            (self.joint_cli, "/goto_joint"),
            (self.pose_cli, "/goto_cartesian"),
            (self.scale_cli, "/set_scaling"),
            (self.get_joints_cli, "/get_joint_state"),
            (self.get_pose_cli, "/get_current_pose"),
            (self.euler_world_cli, "/goto_euler_world"),
            (self.euler_local_cli, "/move_relative_tool"),
        ]:
            if not cli.wait_for_service(timeout_sec=30.0):
                self.get_logger().error(f"Service {name} not available. Is motion_server running?")

    def _wait_for_future(self, fut, timeout: Optional[float]):
        """
        Attente manuelle car rclpy.Future.result() ne prend pas d'argument timeout.
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

    def call_joint(self, req: JointReq) -> Dict[str, Any]:
        ros_req = GoToJoint.Request()
        ros_req.joints = [float(x) for x in req.joints]
        ros_req.execute = bool(req.execute)

        fut = self.joint_cli.call_async(ros_req)
        
        try:
            # Timeout None = Infinite (we wait for the end of the movement) 
            res = self._wait_for_future(fut, timeout=None)
        except Exception as e:
            raise RuntimeError(f"GoToJoint failed: {e}")

        return {"success": bool(res.success), "message": str(res.message)}

    def call_pose(self, req: PoseReq) -> Dict[str, Any]:
        pose = PoseStamped()
        pose.header.frame_id = req.frame_id

        # set position and orientation from request
        pose.pose.position.x = float(req.position["x"])
        pose.pose.position.y = float(req.position["y"])
        pose.pose.position.z = float(req.position["z"])

        pose.pose.orientation.x = float(req.orientation["x"])
        pose.pose.orientation.y = float(req.orientation["y"])
        pose.pose.orientation.z = float(req.orientation["z"])
        pose.pose.orientation.w = float(req.orientation["w"])

        # Execute the service call
        ros_req = GoToPose.Request()
        ros_req.target = pose
        ros_req.execute = bool(req.execute)

        fut = self.pose_cli.call_async(ros_req)
        
        try:
            res = self._wait_for_future(fut, timeout=None)
        except Exception as e:
            raise RuntimeError(f"GoToPose failed: {e}")

        return {"success": bool(res.success), "message": str(res.message)}
    
    def call_euler_world(self, req: EulerReq) -> Dict[str, Any]:
        ros_req = GoToEuler.Request()
        ros_req.frame_id = req.frame_id
        ros_req.x = float(req.x)
        ros_req.y = float(req.y)
        ros_req.z = float(req.z)
        ros_req.rx = float(req.rx)
        ros_req.ry = float(req.ry)
        ros_req.rz = float(req.rz)
        ros_req.execute = bool(req.execute)

        fut = self.euler_world_cli.call_async(ros_req)
        try:
            res = self._wait_for_future(fut, timeout=None)
        except Exception as e:
            raise RuntimeError(f"GoToEulerWorld failed: {e}")
        return {"success": bool(res.success), "message": str(res.message)}

    def call_euler_local(self, req: EulerReq) -> Dict[str, Any]:
        ros_req = GoToEuler.Request()
        ros_req.frame_id = req.frame_id 
        ros_req.x = float(req.x)
        ros_req.y = float(req.y)
        ros_req.z = float(req.z)
        ros_req.rx = float(req.rx)
        ros_req.ry = float(req.ry)
        ros_req.rz = float(req.rz)
        ros_req.execute = bool(req.execute)

        fut = self.euler_local_cli.call_async(ros_req)
        try:
            res = self._wait_for_future(fut, timeout=None)
        except Exception as e:
            raise RuntimeError(f"MoveRelativeTool failed: {e}")
        return {"success": bool(res.success), "message": str(res.message)}
    
    def call_euler_world_rel(self, req: EulerReq) -> Dict[str, Any]:
        ros_req = GoToEuler.Request()
        ros_req.frame_id = req.frame_id # Souvent ignoré ou forcé à world
        ros_req.x = float(req.x)
        ros_req.y = float(req.y)
        ros_req.z = float(req.z)
        ros_req.rx = float(req.rx)
        ros_req.ry = float(req.ry)
        ros_req.rz = float(req.rz)
        ros_req.execute = bool(req.execute)

        fut = self.euler_world_rel_cli.call_async(ros_req)
        try:
            res = self._wait_for_future(fut, timeout=None)
        except Exception as e:
            raise RuntimeError(f"MoveRelativeWorld failed: {e}")
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

@app.post("/goto_joint")
def goto_joint(req: JointReq):
    try:
        return _ros_client.call_joint(req)
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

@app.post("/goto_pose")
def goto_pose(req: PoseReq):
    try:
        return _ros_client.call_pose(req)
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    
@app.post("/goto_euler_world")
def goto_euler_world(req: EulerReq):
    try:
        return _ros_client.call_euler_world(req)
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

@app.post("/move_relative_tool")
def move_relative_tool(req: EulerReq):
    try:
        return _ros_client.call_euler_local(req)
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

@app.post("/move_relative_world")
def move_relative_world(req: EulerReq):
    try:
        return _ros_client.call_euler_world_rel(req)
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

@app.get("/state/joints")
def state_joints():
    return _ros_client.call_get_joints()

@app.get("/state/pose")
def state_pose(frame_id: str = "", child_frame_id: str = ""):
    return _ros_client.call_get_pose(frame_id, child_frame_id)