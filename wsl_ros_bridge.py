import threading
from typing import List, Optional, Dict, Any

import rclpy
from rclpy.node import Node

from fastapi import FastAPI, HTTPException
from pydantic import BaseModel, Field

from denso_motion_control.srv import InitRobot, GoToJoint, GoToPose, SetScaling
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
    # frame_id pour MoveIt (souvent "base_link" ou "world" selon config)
    frame_id: str = "base_link"
    position: Dict[str, float]  # {"x":..., "y":..., "z":...}
    orientation: Dict[str, float]  # {"x":..., "y":..., "z":..., "w":...}
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

        # Attente services
        for cli, name in [
            (self.init_cli, "/init_robot"),
            (self.joint_cli, "/goto_joint"),
            (self.pose_cli, "/goto_cartesian"),
            (self.scale_cli, "/set_scaling"),
        ]:
            if not cli.wait_for_service(timeout_sec=10.0):
                raise RuntimeError(f"Service {name} not available. Is motion_server running?")

    def call_init(self, req: InitReq) -> Dict[str, Any]:
        ros_req = InitRobot.Request()
        ros_req.model = req.model
        ros_req.planning_group = req.planning_group
        ros_req.velocity_scale = float(req.velocity_scale)
        ros_req.accel_scale = float(req.accel_scale)

        fut = self.init_cli.call_async(ros_req)
        rclpy.spin_until_future_complete(self, fut, timeout_sec=30.0)
        if fut.result() is None:
            raise RuntimeError("InitRobot call timed out or failed.")
        res = fut.result()
        return {"success": bool(res.success), "message": str(res.message)}

    def call_scaling(self, req: ScalingReq) -> Dict[str, Any]:
        ros_req = SetScaling.Request()
        ros_req.velocity_scale = float(req.velocity_scale)
        ros_req.accel_scale = float(req.accel_scale)

        fut = self.scale_cli.call_async(ros_req)
        rclpy.spin_until_future_complete(self, fut, timeout_sec=10.0)
        if fut.result() is None:
            raise RuntimeError("SetScaling call timed out or failed.")
        res = fut.result()
        return {"success": bool(res.success), "message": str(res.message)}

    def call_joint(self, req: JointReq) -> Dict[str, Any]:
        ros_req = GoToJoint.Request()
        ros_req.joints = [float(x) for x in req.joints]
        ros_req.execute = bool(req.execute)

        fut = self.joint_cli.call_async(ros_req)
        rclpy.spin_until_future_complete(self, fut, timeout_sec=60.0)
        if fut.result() is None:
            raise RuntimeError("GoToJoint call timed out or failed.")
        res = fut.result()
        return {"success": bool(res.success), "message": str(res.message)}

    def call_pose(self, req: PoseReq) -> Dict[str, Any]:
        pose = PoseStamped()
        pose.header.frame_id = req.frame_id

        pose.pose.position.x = float(req.position["x"])
        pose.pose.position.y = float(req.position["y"])
        pose.pose.position.z = float(req.position["z"])

        pose.pose.orientation.x = float(req.orientation["x"])
        pose.pose.orientation.y = float(req.orientation["y"])
        pose.pose.orientation.z = float(req.orientation["z"])
        pose.pose.orientation.w = float(req.orientation["w"])

        ros_req = GoToPose.Request()
        ros_req.target = pose
        ros_req.execute = bool(req.execute)

        fut = self.pose_cli.call_async(ros_req)
        rclpy.spin_until_future_complete(self, fut, timeout_sec=60.0)
        if fut.result() is None:
            raise RuntimeError("GoToPose call timed out or failed.")
        res = fut.result()
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

    # Spin en background (pour timers/callbacks si besoin)
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
    