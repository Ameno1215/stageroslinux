// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from denso_motion_control:srv/MoveToPose.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "denso_motion_control/srv/detail/move_to_pose__struct.h"
#include "denso_motion_control/srv/detail/move_to_pose__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool denso_motion_control__srv__move_to_pose__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[58];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("denso_motion_control.srv._move_to_pose.MoveToPose_Request", full_classname_dest, 57) == 0);
  }
  denso_motion_control__srv__MoveToPose_Request * ros_message = _ros_message;
  {  // x
    PyObject * field = PyObject_GetAttrString(_pymsg, "x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->x = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // y
    PyObject * field = PyObject_GetAttrString(_pymsg, "y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->y = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // z
    PyObject * field = PyObject_GetAttrString(_pymsg, "z");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->z = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // r1
    PyObject * field = PyObject_GetAttrString(_pymsg, "r1");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->r1 = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // r2
    PyObject * field = PyObject_GetAttrString(_pymsg, "r2");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->r2 = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // r3
    PyObject * field = PyObject_GetAttrString(_pymsg, "r3");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->r3 = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // r4
    PyObject * field = PyObject_GetAttrString(_pymsg, "r4");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->r4 = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // rotation_format
    PyObject * field = PyObject_GetAttrString(_pymsg, "rotation_format");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->rotation_format, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // reference_frame
    PyObject * field = PyObject_GetAttrString(_pymsg, "reference_frame");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->reference_frame, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // is_relative
    PyObject * field = PyObject_GetAttrString(_pymsg, "is_relative");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->is_relative = (Py_True == field);
    Py_DECREF(field);
  }
  {  // cartesian_path
    PyObject * field = PyObject_GetAttrString(_pymsg, "cartesian_path");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->cartesian_path = (Py_True == field);
    Py_DECREF(field);
  }
  {  // execute
    PyObject * field = PyObject_GetAttrString(_pymsg, "execute");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->execute = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * denso_motion_control__srv__move_to_pose__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of MoveToPose_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("denso_motion_control.srv._move_to_pose");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "MoveToPose_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  denso_motion_control__srv__MoveToPose_Request * ros_message = (denso_motion_control__srv__MoveToPose_Request *)raw_ros_message;
  {  // x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // z
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->z);
    {
      int rc = PyObject_SetAttrString(_pymessage, "z", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // r1
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->r1);
    {
      int rc = PyObject_SetAttrString(_pymessage, "r1", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // r2
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->r2);
    {
      int rc = PyObject_SetAttrString(_pymessage, "r2", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // r3
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->r3);
    {
      int rc = PyObject_SetAttrString(_pymessage, "r3", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // r4
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->r4);
    {
      int rc = PyObject_SetAttrString(_pymessage, "r4", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rotation_format
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->rotation_format.data,
      strlen(ros_message->rotation_format.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "rotation_format", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // reference_frame
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->reference_frame.data,
      strlen(ros_message->reference_frame.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "reference_frame", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // is_relative
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->is_relative ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "is_relative", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // cartesian_path
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->cartesian_path ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "cartesian_path", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // execute
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->execute ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "execute", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
// already included above
// #include <Python.h>
// already included above
// #include <stdbool.h>
// already included above
// #include "numpy/ndarrayobject.h"
// already included above
// #include "rosidl_runtime_c/visibility_control.h"
// already included above
// #include "denso_motion_control/srv/detail/move_to_pose__struct.h"
// already included above
// #include "denso_motion_control/srv/detail/move_to_pose__functions.h"

// already included above
// #include "rosidl_runtime_c/string.h"
// already included above
// #include "rosidl_runtime_c/string_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool denso_motion_control__srv__move_to_pose__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[59];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("denso_motion_control.srv._move_to_pose.MoveToPose_Response", full_classname_dest, 58) == 0);
  }
  denso_motion_control__srv__MoveToPose_Response * ros_message = _ros_message;
  {  // success
    PyObject * field = PyObject_GetAttrString(_pymsg, "success");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->success = (Py_True == field);
    Py_DECREF(field);
  }
  {  // message
    PyObject * field = PyObject_GetAttrString(_pymsg, "message");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->message, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * denso_motion_control__srv__move_to_pose__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of MoveToPose_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("denso_motion_control.srv._move_to_pose");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "MoveToPose_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  denso_motion_control__srv__MoveToPose_Response * ros_message = (denso_motion_control__srv__MoveToPose_Response *)raw_ros_message;
  {  // success
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->success ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "success", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // message
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->message.data,
      strlen(ros_message->message.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "message", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
