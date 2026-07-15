// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from t3_interfaces:msg/FrameInfo.idl
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
#include "t3_interfaces/msg/detail/frame_info__struct.h"
#include "t3_interfaces/msg/detail/frame_info__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool sensor_msgs__msg__image__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * sensor_msgs__msg__image__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool t3_interfaces__msg__frame_info__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[40];
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
    assert(strncmp("t3_interfaces.msg._frame_info.FrameInfo", full_classname_dest, 39) == 0);
  }
  t3_interfaces__msg__FrameInfo * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // frame_index
    PyObject * field = PyObject_GetAttrString(_pymsg, "frame_index");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->frame_index = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }
  {  // frame_url
    PyObject * field = PyObject_GetAttrString(_pymsg, "frame_url");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->frame_url, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // video_name
    PyObject * field = PyObject_GetAttrString(_pymsg, "video_name");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->video_name, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // session
    PyObject * field = PyObject_GetAttrString(_pymsg, "session");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->session, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // ref_x
    PyObject * field = PyObject_GetAttrString(_pymsg, "ref_x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->ref_x = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // ref_y
    PyObject * field = PyObject_GetAttrString(_pymsg, "ref_y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->ref_y = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // ref_z
    PyObject * field = PyObject_GetAttrString(_pymsg, "ref_z");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->ref_z = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // ref_valid
    PyObject * field = PyObject_GetAttrString(_pymsg, "ref_valid");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->ref_valid = (Py_True == field);
    Py_DECREF(field);
  }
  {  // health_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "health_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->health_status = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // image
    PyObject * field = PyObject_GetAttrString(_pymsg, "image");
    if (!field) {
      return false;
    }
    if (!sensor_msgs__msg__image__convert_from_py(field, &ros_message->image)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * t3_interfaces__msg__frame_info__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of FrameInfo */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("t3_interfaces.msg._frame_info");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "FrameInfo");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  t3_interfaces__msg__FrameInfo * ros_message = (t3_interfaces__msg__FrameInfo *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "header", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // frame_index
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->frame_index);
    {
      int rc = PyObject_SetAttrString(_pymessage, "frame_index", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // frame_url
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->frame_url.data,
      strlen(ros_message->frame_url.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "frame_url", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // video_name
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->video_name.data,
      strlen(ros_message->video_name.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "video_name", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // session
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->session.data,
      strlen(ros_message->session.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "session", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ref_x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->ref_x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ref_x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ref_y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->ref_y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ref_y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ref_z
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->ref_z);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ref_z", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ref_valid
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->ref_valid ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ref_valid", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // health_status
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->health_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "health_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // image
    PyObject * field = NULL;
    field = sensor_msgs__msg__image__convert_to_py(&ros_message->image);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "image", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
