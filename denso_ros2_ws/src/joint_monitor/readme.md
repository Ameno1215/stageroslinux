# joint_monitor

ROS 2 Humble package that listens to `/joint_states` and tracks **min/max** values of **position**, **velocity**, and **acceleration** for each joint. Recording is controlled on-demand via services.

## Usage

### Launch the node

```bash
ros2 run joint_monitor joint_monitor_node
```

By default the node listens on `/joint_states`. To use a different topic:

```bash
ros2 run joint_monitor joint_monitor_node --ros-args -p joint_states_topic:=/vs060/joint_states
```

### Control recording (from another terminal)

Start recording:

```bash
ros2 service call /joint_monitor/start_recording std_srvs/srv/Trigger
```

Stop recording:

```bash
ros2 service call /joint_monitor/stop_recording std_srvs/srv/Trigger
```

Reset all stats:

```bash
ros2 service call /joint_monitor/reset std_srvs/srv/Trigger
```

Get current stats:

```bash
ros2 service call /joint_monitor/get_stats std_srvs/srv/Trigger
```

### Pretty-print stats

```bash
ros2 service call /joint_monitor/get_stats std_srvs/srv/Trigger 2>&1 \
  | grep "message=" \
  | sed "s/.*message='//" \
  | sed "s/'$//" \
  | python3 -m json.tool
```

### Example output

```json
{
  "recording": false,
  "joints": {
    "joint_1": {
      "position": { "min": -0.523, "max": 0.312 },
      "velocity": { "min": -1.204, "max": 1.108 },
      "acceleration": { "min": -5.012, "max": 4.831 },
      "sample_count": 1200
    },
    "joint_2": {
      "position": { "min": -0.101, "max": 0.750 },
      "velocity": { "min": -0.800, "max": 0.622 },
      "acceleration": { "min": -3.400, "max": 3.100 },
      "sample_count": 1200
    }
  }
}
```

## Behavior details

- **Acceleration** is computed by finite-differencing velocity between consecutive messages.
- **Start** begins recording. If called again while already recording, it has no effect.
- **Stop** pauses recording but preserves all accumulated stats.
- **Start after stop** resumes recording. The velocity history is cleared to avoid computing a bogus acceleration spike across the pause gap.
- **Reset** clears all stats for all joints. Can be called whether recording or not.
- **Get stats** returns data at any time, whether recording or paused.
- Values that have never been recorded appear as `null` in the JSON output.

## Services summary

| Service | Type | Description |
|---|---|---|
| `~/start_recording` | `std_srvs/Trigger` | Begin tracking min/max values |
| `~/stop_recording` | `std_srvs/Trigger` | Pause tracking (stats kept) |
| `~/reset` | `std_srvs/Trigger` | Clear all accumulated stats |
| `~/get_stats` | `std_srvs/Trigger` | Return JSON with all min/max data |

## Parameters

| Parameter | Default | Description |
|---|---|---|
| `joint_states_topic` | `/joint_states` | Topic to subscribe to |