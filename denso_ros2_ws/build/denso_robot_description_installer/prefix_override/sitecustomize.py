import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/antonin/workspace/denso_ros2_ws/install/denso_robot_description_installer'
