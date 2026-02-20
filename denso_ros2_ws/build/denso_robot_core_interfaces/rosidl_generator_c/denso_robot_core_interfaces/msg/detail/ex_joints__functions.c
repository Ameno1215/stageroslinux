// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from denso_robot_core_interfaces:msg/ExJoints.idl
// generated code does not contain a copyright notice
#include "denso_robot_core_interfaces/msg/detail/ex_joints__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `joints`
#include "denso_robot_core_interfaces/msg/detail/joints__functions.h"

bool
denso_robot_core_interfaces__msg__ExJoints__init(denso_robot_core_interfaces__msg__ExJoints * msg)
{
  if (!msg) {
    return false;
  }
  // mode
  // joints
  if (!denso_robot_core_interfaces__msg__Joints__Sequence__init(&msg->joints, 0)) {
    denso_robot_core_interfaces__msg__ExJoints__fini(msg);
    return false;
  }
  return true;
}

void
denso_robot_core_interfaces__msg__ExJoints__fini(denso_robot_core_interfaces__msg__ExJoints * msg)
{
  if (!msg) {
    return;
  }
  // mode
  // joints
  denso_robot_core_interfaces__msg__Joints__Sequence__fini(&msg->joints);
}

bool
denso_robot_core_interfaces__msg__ExJoints__are_equal(const denso_robot_core_interfaces__msg__ExJoints * lhs, const denso_robot_core_interfaces__msg__ExJoints * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // mode
  if (lhs->mode != rhs->mode) {
    return false;
  }
  // joints
  if (!denso_robot_core_interfaces__msg__Joints__Sequence__are_equal(
      &(lhs->joints), &(rhs->joints)))
  {
    return false;
  }
  return true;
}

bool
denso_robot_core_interfaces__msg__ExJoints__copy(
  const denso_robot_core_interfaces__msg__ExJoints * input,
  denso_robot_core_interfaces__msg__ExJoints * output)
{
  if (!input || !output) {
    return false;
  }
  // mode
  output->mode = input->mode;
  // joints
  if (!denso_robot_core_interfaces__msg__Joints__Sequence__copy(
      &(input->joints), &(output->joints)))
  {
    return false;
  }
  return true;
}

denso_robot_core_interfaces__msg__ExJoints *
denso_robot_core_interfaces__msg__ExJoints__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_robot_core_interfaces__msg__ExJoints * msg = (denso_robot_core_interfaces__msg__ExJoints *)allocator.allocate(sizeof(denso_robot_core_interfaces__msg__ExJoints), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(denso_robot_core_interfaces__msg__ExJoints));
  bool success = denso_robot_core_interfaces__msg__ExJoints__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
denso_robot_core_interfaces__msg__ExJoints__destroy(denso_robot_core_interfaces__msg__ExJoints * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    denso_robot_core_interfaces__msg__ExJoints__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
denso_robot_core_interfaces__msg__ExJoints__Sequence__init(denso_robot_core_interfaces__msg__ExJoints__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_robot_core_interfaces__msg__ExJoints * data = NULL;

  if (size) {
    data = (denso_robot_core_interfaces__msg__ExJoints *)allocator.zero_allocate(size, sizeof(denso_robot_core_interfaces__msg__ExJoints), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = denso_robot_core_interfaces__msg__ExJoints__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        denso_robot_core_interfaces__msg__ExJoints__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
denso_robot_core_interfaces__msg__ExJoints__Sequence__fini(denso_robot_core_interfaces__msg__ExJoints__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      denso_robot_core_interfaces__msg__ExJoints__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

denso_robot_core_interfaces__msg__ExJoints__Sequence *
denso_robot_core_interfaces__msg__ExJoints__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_robot_core_interfaces__msg__ExJoints__Sequence * array = (denso_robot_core_interfaces__msg__ExJoints__Sequence *)allocator.allocate(sizeof(denso_robot_core_interfaces__msg__ExJoints__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = denso_robot_core_interfaces__msg__ExJoints__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
denso_robot_core_interfaces__msg__ExJoints__Sequence__destroy(denso_robot_core_interfaces__msg__ExJoints__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    denso_robot_core_interfaces__msg__ExJoints__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
denso_robot_core_interfaces__msg__ExJoints__Sequence__are_equal(const denso_robot_core_interfaces__msg__ExJoints__Sequence * lhs, const denso_robot_core_interfaces__msg__ExJoints__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!denso_robot_core_interfaces__msg__ExJoints__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
denso_robot_core_interfaces__msg__ExJoints__Sequence__copy(
  const denso_robot_core_interfaces__msg__ExJoints__Sequence * input,
  denso_robot_core_interfaces__msg__ExJoints__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(denso_robot_core_interfaces__msg__ExJoints);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    denso_robot_core_interfaces__msg__ExJoints * data =
      (denso_robot_core_interfaces__msg__ExJoints *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!denso_robot_core_interfaces__msg__ExJoints__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          denso_robot_core_interfaces__msg__ExJoints__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!denso_robot_core_interfaces__msg__ExJoints__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
