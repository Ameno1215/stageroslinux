import threading
import time
import math
from typing import List, Optional, Dict, Any
import logging
from logging.handlers import RotatingFileHandler
import traceback

import rclpy
from rclpy.node import Node

from fastapi import FastAPI, HTTPException
from pydantic import BaseModel, Field

from denso_motion_control.srv import InitRobot, MoveJoints, MoveToPose, MoveWaypoints, SetScaling, GetJointState, GetCurrentPose, SetVirtualCage, ManageBox
from geometry_msgs.msg import PoseStamped, Pose
from rcl_interfaces.srv import GetParameters
from moveit_msgs.msg import PlanningScene, CollisionObject, ObjectColor
from shape_msgs.msg import SolidPrimitive




# ----------------------------
# Logger Configuration
# ----------------------------
logger = logging.getLogger("DensoBridge")
logger.setLevel(logging.DEBUG)
formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')

console_handler = logging.StreamHandler()
console_handler.setFormatter(formatter)
logger.addHandler(console_handler)

# log file with rotation (5 MB per file, keep 3 backups)
file_handler = RotatingFileHandler("robot_system.log", maxBytes=5*1024*1024, backupCount=3)
file_handler.setFormatter(formatter)
logger.addHandler(file_handler)


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
    is_relative: bool = False
    reference_frame: str = "WORLD"
    rotation_format: str = "RPY"

class MoveWaypointsReq(BaseModel):
    waypoints: List[WaypointItem]
    cartesian_path: bool = True
    execute: bool = True

class MoveApproachReq(BaseModel):
    x: float
    y: float
    z: float
    r1: float
    r2: float
    r3: float
    r4: float = 0.0
    rotation_format: str = "RPY"
    z_offset: float = 0.1
    cartesian_path: bool = False
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

class ManageBoxReq(BaseModel):
    box_id: str
    x: float = 0.0
    y: float = 0.0
    z: float = 0.0
    r1: float = 0.0
    r2: float = 0.0
    r3: float = 0.0
    r4: float = 0.0
    rotation_format: str = "RPY"
    size_x: float = 0.1
    size_y: float = 0.1
    size_z: float = 0.1
    action: str = "ADD" # Can be "ADD" or "REMOVE"


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
        self.param_client = self.create_client(GetParameters, "/denso_motion_server/get_parameters")
        self.manage_box_cli = self.create_client(ManageBox, "/manage_box")
        

        # Wait for services
        logger.info("Waiting for ROS 2 services...")
        for cli, name in [
            (self.init_cli, "/init_robot"),
            (self.scale_cli, "/set_scaling"),
            (self.get_joints_cli, "/get_joint_state"),
            (self.get_pose_cli, "/get_current_pose"),
            (self.move_pose_cli, "/move_to_pose"),
            (self.move_joints_cli, "/move_joints"),
            (self.move_waypoints_cli, "/move_waypoints"),
            (self.cage_cli, "/set_virtual_cage"),
            (self.param_client, "/denso_motion_server/get_parameters"),
            (self.manage_box_cli, "/manage_box")
        ]:
            if not cli.wait_for_service(timeout_sec=30.0):
                logger.error(f"Service {name} not available. Is motion_server running?")
        logger.info("All ROS 2 services are connected.")

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
            
            time.sleep(0.005)
        
        # Once finished, we retrieve the result
        return fut.result()

    def call_init(self, req: InitReq) -> Dict[str, Any]:
        logger.info(f"Initialization request (Model: {req.model}, Group: {req.planning_group})")
        ros_req = InitRobot.Request()
        ros_req.model = str(req.model)
        ros_req.planning_group = str(req.planning_group)
        ros_req.velocity_scale = float(req.velocity_scale)
        ros_req.accel_scale = float(req.accel_scale)

        fut = self.init_cli.call_async(ros_req)
        
        try:
            # 60 seconds for initialization (loading robot model, setting up MoveIt, etc.)
            res = self._wait_for_future(fut, timeout=60.0)
            if res.success:
                logger.info(f"Initialization successful: {res.message}")
            else:
                logger.error(f"Initialization failed: {res.message}")
            return {"success": bool(res.success), "message": str(res.message)}
        except Exception as e:
            logger.error(f"Critical error during InitRobot call: {e}")
            logger.debug(traceback.format_exc())
            raise RuntimeError(f"InitRobot failed: {e}")
            
        return {"success": bool(res.success), "message": str(res.message)}

    def call_scaling(self, req: ScalingReq) -> Dict[str, Any]:
        logger.info(f"Scaling change request (Vel: {req.velocity_scale}, Acc: {req.accel_scale})")
        ros_req = SetScaling.Request()
        ros_req.velocity_scale = float(req.velocity_scale)
        ros_req.accel_scale = float(req.accel_scale)

        fut = self.scale_cli.call_async(ros_req)
        
        try:
            res = self._wait_for_future(fut, timeout=5.0)
            if res.success:
                logger.info(f"Scaling change successful: {res.message}")
            else:
                logger.error(f"Scaling change failed: {res.message}")
            return {"success": bool(res.success), "message": str(res.message)}
        except Exception as e:
            logger.error(f"Critical error during SetScaling call: {e}")
            logger.debug(traceback.format_exc())
            raise RuntimeError(f"SetScaling failed: {e}")

    def call_move_joints(self, req: JointReq) -> Dict[str, Any]:
        logger.info(f"Joint movement request: {req.joints} (Relative={req.is_relative}, Execute={req.execute})")
        ros_req = MoveJoints.Request()
        ros_req.joints = [float(x) for x in req.joints]
        ros_req.is_relative = bool(req.is_relative)
        ros_req.execute = bool(req.execute)

        fut = self.move_joints_cli.call_async(ros_req)
        try:
            res = self._wait_for_future(fut, timeout=None)
            if res.success:
                logger.info(f"Joint movement successful: {res.message}")
            else:
                logger.error(f"Joint movement failed: {res.message}")
            return {"success": bool(res.success), "message": str(res.message)}
        except Exception as e:
            logger.error(f"Critical error during MoveJoints call: {e}")
            logger.debug(traceback.format_exc())
            raise RuntimeError(f"MoveJoints failed: {e}")

    def call_move_to_pose(self, req: MoveToPoseReq) -> Dict[str, Any]:
        logger.info(f"Request for movement received : X={req.x}, Y={req.y}, Z={req.z} (Relative={req.is_relative}, Cartesian={req.cartesian_path}, Execute={req.execute})")
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
            if res.success:
                logger.info(f"Successful movement : {res.message}")
            else:
                logger.error(f"Failed movement ! Cause returned by MoveIt : {res.message}")
                
            return {"success": bool(res.success), "message": str(res.message)}
        except Exception as e:
            logger.error(f"Critical error during the MoveToPose call : {e}")
            logger.debug(traceback.format_exc())
            raise RuntimeError(f"MoveToPose failed: {e}")

    def call_move_waypoints(self, req: MoveWaypointsReq) -> Dict[str, Any]:
        logger.info(f"Waypoints movement request: {len(req.waypoints)} points (Cartesian={req.cartesian_path}, execute={req.execute})")
        ros_req = MoveWaypoints.Request()
        ros_req.cartesian_path = bool(req.cartesian_path)
        ros_req.execute = bool(req.execute)

        # Construction of the geometry_msgs/Pose table
        for wp in req.waypoints:
            p = Pose()
            p.position.x = float(wp.x)
            p.position.y = float(wp.y)
            p.position.z = float(wp.z)
            
            if wp.rotation_format == "RPY": # We convert RPY to quaternion for the Pose message
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
            ros_req.is_relative_list.append(bool(wp.is_relative))
            ros_req.reference_frame_list.append(str(wp.reference_frame))

        fut = self.move_waypoints_cli.call_async(ros_req)
        try:
            res = self._wait_for_future(fut, timeout=None)
            if res.success:
                logger.info(f"Waypoints movement successful: {res.message}")
            else:
                logger.error(f"Waypoints movement failed: {res.message}")
            return {"success": bool(res.success), "message": str(res.message)}
        except Exception as e:
            logger.error(f"Critical error during MoveWaypoints call: {e}")
            logger.debug(traceback.format_exc())
            raise RuntimeError(f"MoveWaypoints failed: {e}")

    def call_get_joints(self):
        logger.info("Joint state read request")
        req = GetJointState.Request()
        fut = self.get_joints_cli.call_async(req)
        try:
            res = self._wait_for_future(fut, timeout=5.0)
            if res.success:
                logger.info(f"Joint state read successful. Joints: [{list(res.joints)}]")
            else:
                logger.error(f"Joint state read failed: {res.message}")
            return {"success": res.success, "message": res.message, "joints": list(res.joints)}
        except Exception as e:
            logger.error(f"Critical error during GetJointState call: {e}")
            logger.debug(traceback.format_exc())
            raise RuntimeError(f"GetJointState failed: {e}")
    
    def call_get_pose(self, frame_id: str = "", child_frame_id: str = ""):
        logger.info(f"Pose read request (frame={frame_id}, child={child_frame_id})")
        req = GetCurrentPose.Request()
        req.frame_id = frame_id # Reference frame for the returned pose (e.g. "base_link"). If empty, the robot's default frame will be used.
        req.child_frame_id = child_frame_id # (Optional) If specified, the service will attempt to return the pose of this child frame. If empty, the end-effector frame will be used.
        
        fut = self.get_pose_cli.call_async(req)
        try:
            res = self._wait_for_future(fut, timeout=5.0)
            if not res.success:
                logger.error(f"Pose read failed: {res.message}")
        except Exception as e:
            logger.error(f"Critical error during GetCurrentPose call: {e}")
            logger.debug(traceback.format_exc())
            raise RuntimeError(f"GetCurrentPose failed: {e}")

        p = res.pose.pose
        
        # Safe extraction of Euler angles (default to 0.0 if empty for any reason)
        rx, ry, rz = 0.0, 0.0, 0.0
        if len(res.euler_rpy) >= 3:
            rx = res.euler_rpy[0]
            ry = res.euler_rpy[1]
            rz = res.euler_rpy[2]
        
        logger.info(
            f"Pose read successful. "
            f"XYZ: [{p.position.x:.3f}, {p.position.y:.3f}, {p.position.z:.3f}], "
            f"Quat: [{p.orientation.x:.3f}, {p.orientation.y:.3f}, {p.orientation.z:.3f}, {p.orientation.w:.3f}], "
            f"RPY: [{rx:.3f}, {ry:.3f}, {rz:.3f}]"
        )

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
        logger.info(f"Virtual cage modification request (Enable={req.enable})")
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
            if res.success:
                logger.info(f"Virtual cage modification successful: {res.message}")
            else:
                logger.error(f"Virtual cage modification failed: {res.message}")
            return {"success": bool(res.success), "message": str(res.message)}
        except Exception as e:
            logger.error(f"Critical error during SetVirtualCage call: {e}")
            logger.debug(traceback.format_exc())
            raise RuntimeError(f"SetVirtualCage failed: {e}")

    def call_get_solver(self) -> Dict[str, Any]:
        logger.info("Requesting IK solver info from C++ node...")
        
        if not self.param_client.wait_for_service(timeout_sec=2.0):
            logger.error("Parameter service not available. Is motion_server running?")
            return {"success": False, "message": "denso_motion_server parameter service not available."}
        
        req = GetParameters.Request()
        req.names = ['robot_description_kinematics.arm.kinematics_solver']
        
        fut = self.param_client.call_async(req)
        try:
            res = self._wait_for_future(fut, timeout=5.0)
            
            if res.values and len(res.values) > 0:
                plugin_name = res.values[0].string_value
                
                if plugin_name:
                    short_name = plugin_name.split('/')[0] if '/' in plugin_name else plugin_name
                    logger.info(f"Current IK solver plugin: {plugin_name} (short name: {short_name})")
                    
                    return {
                        "success": True, 
                        "solver": short_name, 
                        "full_plugin_name": plugin_name
                    }
                    
            logger.error("Solver parameter not found or empty in response.")
            return {"success": False, "message": "Solver parameter is not set in C++ node."}
            
        except Exception as e:
            logger.error(f"Failed to get solver parameter: {e}")
            return {"success": False, "message": str(e)}

    def call_move_approach(self, req: MoveApproachReq):
        import math
        logger.info(f"Calculating approach pose: target=({req.x:.3f}, {req.y:.3f}, {req.z:.3f}), z_offset={req.z_offset}m")
        
        # Convert RPY to Quaternion if necessary
        if req.rotation_format.upper() == "RPY":
            roll, pitch, yaw = req.r1, req.r2, req.r3
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
        else:
            qx, qy, qz, qw = req.r1, req.r2, req.r3, req.r4

        # Extract the local Z-vector (the direction the tool is pointing)
        vx = 2.0 * (qx * qz + qw * qy)
        vy = 2.0 * (qy * qz - qw * qx)
        vz = 1.0 - 2.0 * (qx * qx + qy * qy)

        # Calculate the approach position by backing up along the Z-vector
        app_x = req.x - (req.z_offset * vx)
        app_y = req.y - (req.z_offset * vy)
        app_z = req.z - (req.z_offset * vz)

        logger.info(f"Approach position computed: x={app_x:.3f}, y={app_y:.3f}, z={app_z:.3f}")

        # Directly create the ROS request for the C++ node
        ros_req = MoveToPose.Request()
        ros_req.x = float(app_x)
        ros_req.y = float(app_y)
        ros_req.z = float(app_z)
        ros_req.r1 = float(qx)
        ros_req.r2 = float(qy)
        ros_req.r3 = float(qz)
        ros_req.r4 = float(qw)
        ros_req.rotation_format = "QUAT"   # Force quaternion format
        ros_req.reference_frame = "WORLD"  # Absolute position
        ros_req.is_relative = False
        ros_req.cartesian_path = req.cartesian_path
        ros_req.execute = req.execute

        logger.info("Sending approach request to ROS C++ node...")
        fut = self.move_pose_cli.call_async(ros_req)
        
        try:
            # Wait for the result (long timeout if execute=True)
            res = self._wait_for_future(fut, timeout=120.0)
            
            if res.success:
                logger.info(f"Approach movement successful: {res.message}")
            else:
                logger.error(f"Approach movement failed: {res.message}")
                
            return {"success": res.success, "message": res.message}
            
        except Exception as e:
            logger.error(f"Error during approach movement: {e}")
            return {"success": False, "message": str(e)}

    def call_manage_box(self, req: ManageBoxReq):
        logger.info(f"Sending {req.action} for box {req.box_id} to C++ node...")
        if not self.manage_box_cli.wait_for_service(timeout_sec=2.0):
            return {"success": False, "message": "Service manage_box unavailable."}

        ros_req = ManageBox.Request()
        ros_req.box_id = req.box_id
        ros_req.x = float(req.x)
        ros_req.y = float(req.y)
        ros_req.z = float(req.z)
        ros_req.r1 = float(req.r1)
        ros_req.r2 = float(req.r2)
        ros_req.r3 = float(req.r3)
        ros_req.r4 = float(req.r4)
        ros_req.rotation_format = req.rotation_format
        ros_req.size_x = float(req.size_x)
        ros_req.size_y = float(req.size_y)
        ros_req.size_z = float(req.size_z)
        ros_req.action = req.action

        fut = self.manage_box_cli.call_async(ros_req)
        try:
            res = self._wait_for_future(fut, timeout=5.0)
            return {"success": res.success, "message": res.message}
        except Exception as e:
            logger.error(f"Failed to manage box: {e}")
            return {"success": False, "message": str(e)}

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

@app.get("/state/solver")
def state_solver():
    return _ros_client.call_get_solver()

@app.post("/move_approach")
def move_approach(req: MoveApproachReq):
    try:
        return _ros_client.call_move_approach(req)
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

@app.post("/manage_box")
def manage_box(req: ManageBoxReq):
    try:
        return _ros_client.call_manage_box(req)
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))