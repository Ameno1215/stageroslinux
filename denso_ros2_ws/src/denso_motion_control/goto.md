# Test du package `denso_motion_control` en simulation (VS060)

Ce document décrit **pas à pas** comment tester le package **denso_motion_control**
en **simulation** avec un robot **DENSO VS060**, en utilisant **ROS 2 Humble** et **MoveIt 2**.

---

## 1. Pré-requis

- ROS 2 Humble installé
- Workspace compilé avec succès
- Packages Denso installés :
  - `denso_robot_bringup`
  - `denso_robot_descriptions`
  - `denso_robot_moveit_config`
  - `denso_motion_control`
- RViz et MoveIt fonctionnels

Workspace utilisé dans cet exemple :

```
~/workspace/denso_ros2_ws
```

---

## 2. Préparation de l’environnement

⚠️ À faire **dans chaque terminal**.

```bash
cd ~/workspace/denso_ros2_ws
source /opt/ros/humble/setup.bash
source install/setup.bash
```

Optionnel (souvent nécessaire sous WSL / GPU logiciel) :

```bash
export LIBGL_ALWAYS_SOFTWARE=1
```

---

## 3. Lancer la simulation Denso + MoveIt

### Terminal 1

```bash
ros2 launch denso_robot_bringup denso_robot_bringup.launch.py model:=vs060 sim:=true
```

Attendre :
- le démarrage de `move_group`
- l’ouverture de RViz
- aucune erreur critique dans les logs

---

## 4. Lancer le serveur de contrôle de mouvement

### Terminal 2

```bash
ros2 launch denso_motion_control motion_server.launch.py model:=vs060 sim:=true
```

Message attendu :

```
[denso_motion_server] MotionServer ready. Call /init_robot first.
```

---

## 5. Vérifier les services disponibles

```bash
ros2 service list | grep -E "init_robot|goto_joint|goto_cartesian"
```

---

## 6. Initialisation du robot

```bash
ros2 service call /init_robot denso_motion_control/srv/InitRobot \
"{model: 'vs060', planning_group: 'arm', velocity_scale: 0.1, accel_scale: 0.1}"
```

---

## 7. Mouvement articulaire

```bash
ros2 service call /goto_joint denso_motion_control/srv/GoToJoint \
"{joints: [1.57, 0.0, 1.57, 0.0, 1.57, 0.0], execute: true}"
```

---

## 8. Mouvement cartésien

```bash
ros2 service call /goto_cartesian denso_motion_control/srv/GoToPose \
"{
  target: {
    header: { frame_id: 'base_link' },
    pose: {
      position: { x: -0.10, y: 0.40, z: 0.40 },
      orientation: { x: 0.7071068, y: -0.7071068, z: 0.0, w: 0.0 }
    }
  },
  execute: true
}"
```

---

## 9. Mise à jour de la vitesse et de l'accélération

```bash
ros2 service call /set_scaling denso_motion_control/srv/SetScaling "{velocity_scale: 0.5, accel_scale: 0.5}"
```

---


Fin du document.
