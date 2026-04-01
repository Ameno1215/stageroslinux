# b-CAP / DENSO ROS2 Error Codes

Source: `bcap_core/include/bcap_core/dn_common.h` and related files from the `denso_robot_drivers_ros2` package.

---

## Success Codes

| Hex Code | Value | Name | Description |
|----------|-------|------|-------------|
| `0x00000000` | `0` | `S_OK` | Operation succeeded. |
| `0x00000001` | `1` | `S_FALSE` | Succeeded but some processes may remain incomplete. |
| `0x00000900` | `2304` | `S_EXECUTING` | Command is currently being executed (not yet finished). |

---

## DENSO b-CAP Specific Error Codes (`0x800009xx`)

| Hex Code | Name | Description |
|----------|------|-------------|
| `0x80000900` | `E_TIMEOUT` | **Communication timeout.** The RC8 did not respond within the expected time. Possible causes: robot in error state, unstable network connection, b-CAP watchdog expired. |
| `0x80000902` | `E_NOT_CONNECTED` | **Connection not established.** No active b-CAP session with the controller. |
| `0x80000905` | `E_MAX_OBJECT` | **Too many objects.** The maximum number of registered b-CAP objects has been reached. |
| `0x80000906` | `E_ALREADY_REGISTER` | **Already registered.** The object is already registered in the current b-CAP session. |
| `0x80000909` | `E_TOO_MUCH_DATA` | **Packet too large.** The data sent exceeds the maximum b-CAP packet size. |
| `0x8000090B` | `E_MAX_CONNECT` | **Too many connections.** The maximum number of simultaneous connections to the RC8 has been reached. |

---

## Standard Windows-compatible Error Codes

| Hex Code | Name | Description |
|----------|------|-------------|
| `0x80004001` | `E_NOTIMPL` | Function is not implemented. |
| `0x80004005` | `E_FAIL` | Unspecified failure. |
| `0x80070005` | `E_ACCESSDENIED` | Access denied — resource is not ready or execution token not granted. |
| `0x80070006` | `E_HANDLE` | Invalid handle. |
| `0x8007000E` | `E_OUTOFMEMORY` | Not enough memory available. |
| `0x80070057` | `E_INVALIDARG` | One or more arguments passed to the function are invalid. |
| `0x8000FFFF` | `E_UNEXPECTED` | Unexpected error occurred. |

---

## DISP Error Codes (type/variant)

| Hex Code | Name | Description |
|----------|------|-------------|
| `0x80020005` | `DISP_E_TYPEMISMATCH` | Variant type is incompatible with the requested operation. |
| `0x80020008` | `DISP_E_BADVARTYPE` | Invalid variant type. |
| `0x8002000A` | `DISP_E_OVERFLOW` | Value is out of range for the destination type. |
| `0x8002000B` | `DISP_E_BADINDEX` | Invalid array index. |

---

## Network / Packet Error Codes

| Hex Code | Name | Description |
|----------|------|-------------|
| `0x80010000` | `E_INVALIDPACKET` | Invalid or corrupted network packet received. |
| `0x8091xxxx` | `OSERR2HRESULT(err)` | OS-level error (lower 16 bits contain the Linux/Windows errno code). |

---

## Quick Reference — Common Errors in Practice

| Code | Most Likely Cause | Action |
|------|-------------------|--------|
| `80000900` (`E_TIMEOUT`) | Robot in error state, watchdog expired, connection lost | Reset on teach pendant, check network connectivity |
| `80000902` (`E_NOT_CONNECTED`) | b-CAP session not opened or closed abnormally | Restart bringup, verify RC8 is reachable on the network |
| `8000090B` (`E_MAX_CONNECT`) | A previous session is still open on the RC8 side | Wait for RC8 session timeout (~2 min) or reboot the controller |
| `80070005` (`E_ACCESSDENIED`) | Execution token not granted | Check Executable Token setting on the teach pendant |
| `80070057` (`E_INVALIDARG`) | Wrong command format sent | Check `send_format` / `recv_format` parameters |

---

## Useful Macros Defined in the Code

```cpp
SUCCEEDED(hr)  // true if hr >= 0 (success)
FAILED(hr)     // true if hr < 0  (error)
```
