// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from bcap_service_interfaces:srv/Bcap.idl
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
#include "bcap_service_interfaces/srv/detail/bcap__struct.h"
#include "bcap_service_interfaces/srv/detail/bcap__functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

// Nested array functions includes
#include "bcap_service_interfaces/msg/detail/variant__functions.h"
// end nested array functions include
bool bcap_service_interfaces__msg__variant__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * bcap_service_interfaces__msg__variant__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool bcap_service_interfaces__srv__bcap__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[47];
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
    assert(strncmp("bcap_service_interfaces.srv._bcap.Bcap_Request", full_classname_dest, 46) == 0);
  }
  bcap_service_interfaces__srv__Bcap_Request * ros_message = _ros_message;
  {  // func_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "func_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->func_id = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // vnt_args
    PyObject * field = PyObject_GetAttrString(_pymsg, "vnt_args");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'vnt_args'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!bcap_service_interfaces__msg__Variant__Sequence__init(&(ros_message->vnt_args), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create bcap_service_interfaces__msg__Variant__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    bcap_service_interfaces__msg__Variant * dest = ros_message->vnt_args.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!bcap_service_interfaces__msg__variant__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * bcap_service_interfaces__srv__bcap__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Bcap_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("bcap_service_interfaces.srv._bcap");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Bcap_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  bcap_service_interfaces__srv__Bcap_Request * ros_message = (bcap_service_interfaces__srv__Bcap_Request *)raw_ros_message;
  {  // func_id
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->func_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "func_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // vnt_args
    PyObject * field = NULL;
    size_t size = ros_message->vnt_args.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    bcap_service_interfaces__msg__Variant * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->vnt_args.data[i]);
      PyObject * pyitem = bcap_service_interfaces__msg__variant__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "vnt_args", field);
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
// #include "bcap_service_interfaces/srv/detail/bcap__struct.h"
// already included above
// #include "bcap_service_interfaces/srv/detail/bcap__functions.h"

bool bcap_service_interfaces__msg__variant__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * bcap_service_interfaces__msg__variant__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool bcap_service_interfaces__srv__bcap__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[48];
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
    assert(strncmp("bcap_service_interfaces.srv._bcap.Bcap_Response", full_classname_dest, 47) == 0);
  }
  bcap_service_interfaces__srv__Bcap_Response * ros_message = _ros_message;
  {  // hresult
    PyObject * field = PyObject_GetAttrString(_pymsg, "hresult");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->hresult = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // vnt_ret
    PyObject * field = PyObject_GetAttrString(_pymsg, "vnt_ret");
    if (!field) {
      return false;
    }
    if (!bcap_service_interfaces__msg__variant__convert_from_py(field, &ros_message->vnt_ret)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * bcap_service_interfaces__srv__bcap__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Bcap_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("bcap_service_interfaces.srv._bcap");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Bcap_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  bcap_service_interfaces__srv__Bcap_Response * ros_message = (bcap_service_interfaces__srv__Bcap_Response *)raw_ros_message;
  {  // hresult
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->hresult);
    {
      int rc = PyObject_SetAttrString(_pymessage, "hresult", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // vnt_ret
    PyObject * field = NULL;
    field = bcap_service_interfaces__msg__variant__convert_to_py(&ros_message->vnt_ret);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "vnt_ret", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
