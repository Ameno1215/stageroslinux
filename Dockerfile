# ROS 2 Humble (Ubuntu 22.04) + Gazebo + MoveIt pour faire tourner ros2_ws sur un hôte Ubuntu 24.04
FROM osrf/ros:humble-desktop-full

ARG USERNAME=ros
ARG USER_UID=1000
ARG USER_GID=1000

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    ros-humble-gazebo-ros-pkgs ros-humble-gazebo-ros2-control \
    ros-humble-ros2-control ros-humble-ros2-controllers \
    ros-humble-joint-state-broadcaster ros-humble-joint-trajectory-controller \
    ros-humble-xacro ros-humble-moveit ros-humble-moveit-planners-ompl \
    ros-humble-moveit-ros-visualization ros-humble-pick-ik \
    ros-humble-rmw-cyclonedds-cpp \
    python3-pip python3-colcon-common-extensions sudo nano iputils-ping \
    && rm -rf /var/lib/apt/lists/*

# Dépendances Python du bridge (wsl_ros_bridge.py)
RUN pip3 install --no-cache-dir fastapi uvicorn requests numpy

# Dépendances déclarées dans les package.xml du workspace
COPY ros2_ws/src /tmp/src
RUN apt-get update && rosdep update \
    && rosdep install --from-paths /tmp/src --ignore-src -r -y --rosdistro humble \
    && rm -rf /tmp/src /var/lib/apt/lists/*

# Utilisateur avec le même UID que l'hôte : les fichiers créés dans le dossier monté t'appartiennent
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m -s /bin/bash $USERNAME \
    && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/$USERNAME

USER $USERNAME
RUN echo 'source /opt/ros/humble/setup.bash' >> ~/.bashrc \
    && echo '[ -f ~/stageroslinux/ros2_ws/install/setup.bash ] && source ~/stageroslinux/ros2_ws/install/setup.bash' >> ~/.bashrc

WORKDIR /home/ros/stageroslinux/ros2_ws
CMD ["bash"]
