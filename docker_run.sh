#!/usr/bin/env bash
# Conteneur ROS 2 Humble.
#   ./docker_run.sh          -> démarre le conteneur si besoin et ouvre un terminal dedans
#   ./docker_run.sh start    -> démarre le conteneur en arrière-plan (utilisé par launch_controller.py)
#   ./docker_run.sh stop     -> arrête le conteneur
#   ./docker_run.sh build    -> (re)construit l'image
set -e

IMAGE=ros-humble-robot
NAME=ros-humble
HERE="$(cd "$(dirname "$0")" && pwd)"
PROJECT="$(dirname "$HERE")"

build() {
    docker build --build-arg USER_UID="$(id -u)" --build-arg USER_GID="$(id -g)" -t "$IMAGE" "$HERE"
}

running() {
    [ -n "$(docker ps -q -f name="^${NAME}$")" ]
}

start() {
    running && return 0
    if ! docker image inspect "$IMAGE" >/dev/null 2>&1; then
        echo "Image absente, construction (première fois : 10-20 min)..."
        build
    fi
    # Autorise le conteneur à afficher des fenêtres (RViz, Gazebo)
    xhost +local:docker >/dev/null || true
    # Le dossier du projet est aussi monté à son chemin d'origine : les chemins file:// des
    # meshes envoyés par le client (stageroswindows) sont ainsi valides dans le conteneur.
    docker run -d --rm \
        --name "$NAME" \
        --network host \
        --ipc host \
        -e DISPLAY="$DISPLAY" \
        -e ROS_DOMAIN_ID="${ROS_DOMAIN_ID:-0}" \
        -v /tmp/.X11-unix:/tmp/.X11-unix \
        --device /dev/dri \
        -v "$HERE":/home/ros/stageroslinux \
        -v "$PROJECT":"$PROJECT":ro \
        "$IMAGE" sleep infinity >/dev/null
}

case "$1" in
    build) build ;;
    start) start ;;
    stop)  docker stop "$NAME" >/dev/null 2>&1 || true ;;
    "")    start && exec docker exec -it "$NAME" bash ;;
    *)     echo "Usage: $0 [build|start|stop]"; exit 1 ;;
esac
