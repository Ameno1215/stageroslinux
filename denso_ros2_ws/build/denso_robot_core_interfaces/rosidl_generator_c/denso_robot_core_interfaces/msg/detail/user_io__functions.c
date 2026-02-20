// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from denso_robot_core_interfaces:msg/UserIO.idl
// generated code does not contain a copyright notice
#include "denso_robot_core_interfaces/msg/detail/user_io__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `value`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
denso_robot_core_interfaces__msg__UserIO__init(denso_robot_core_interfaces__msg__UserIO * msg)
{
  if (!msg) {
    return false;
  }
  // offset
  // size
  // value
  if (!rosidl_runtime_c__uint8__Sequence__init(&msg->value, 0)) {
    denso_robot_core_interfaces__msg__UserIO__fini(msg);
    return false;
  }
  return true;
}

void
denso_robot_core_interfaces__msg__UserIO__fini(denso_robot_core_interfaces__msg__UserIO * msg)
{
  if (!msg) {
    return;
  }
  // offset
  // size
  // value
  rosidl_runtime_c__uint8__Sequence__fini(&msg->value);
}

bool
denso_robot_core_interfaces__msg__UserIO__are_equal(const denso_robot_core_interfaces__msg__UserIO * lhs, const denso_robot_core_interfaces__msg__UserIO * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // offset
  if (lhs->offset != rhs->offset) {
    return false;
  }
  // size
  if (lhs->size != rhs->size) {
    return false;
  }
  // value
  if (!rosidl_runtime_c__uint8__Sequence__are_equal(
      &(lhs->value), &(rhs->value)))
  {
    return false;
  }
  return true;
}

bool
denso_robot_core_interfaces__msg__UserIO__copy(
  const denso_robot_core_interfaces__msg__UserIO * input,
  denso_robot_core_interfaces__msg__UserIO * output)
{
  if (!input || !output) {
    return false;
  }
  // offset
  output->offset = input->offset;
  // size
  output->size = input->size;
  // value
  if (!rosidl_runtime_c__uint8__Sequence__copy(
      &(input->value), &(output->value)))
  {
    return false;
  }
  return true;
}

denso_robot_core_interfaces__msg__UserIO *
denso_robot_core_interfaces__msg__UserIO__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_robot_core_interfaces__msg__UserIO * msg = (denso_robot_core_interfaces__msg__UserIO *)allocator.allocate(sizeof(denso_robot_core_interfaces__msg__UserIO), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(denso_robot_core_interfaces__msg__UserIO));
  bool success = denso_robot_core_interfaces__msg__UserIO__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
denso_robot_core_interfaces__msg__UserIO__destroy(denso_robot_core_interfaces__msg__UserIO * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    denso_robot_core_interfaces__msg__UserIO__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
denso_robot_core_interfaces__msg__UserIO__Sequence__init(denso_robot_core_interfaces__msg__UserIO__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_robot_core_interfaces__msg__UserIO * data = NULL;

  if (size) {
    data = (denso_robot_core_interfaces__msg__UserIO *)allocator.zero_allocate(size, sizeof(denso_robot_core_interfaces__msg__UserIO), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = denso_robot_core_interfaces__msg__UserIO__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        denso_robot_core_interfaces__msg__UserIO__fini(&data[i - 1]);
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
denso_robot_core_interfaces__msg__UserIO__Sequence__fini(denso_robot_core_interfaces__msg__UserIO__Sequence * array)
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
      denso_robot_core_interfaces__msg__UserIO__fini(&array->data[i]);
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

denso_robot_core_interfaces__msg__UserIO__Sequence *
denso_robot_core_interfaces__msg__UserIO__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_robot_core_interfaces__msg__UserIO__Sequence * array = (denso_robot_core_interfaces__msg__UserIO__Sequence *)allocator.allocate(sizeof(denso_robot_core_interfaces__msg__UserIO__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = denso_robot_core_interfaces__msg__UserIO__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
denso_robot_core_interfaces__msg__UserIO__Sequence__destroy(denso_robot_core_interfaces__msg__UserIO__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    denso_robot_core_interfaces__msg__UserIO__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
denso_robot_core_interfaces__msg__UserIO__Sequence__are_equal(const denso_robot_core_interfaces__msg__UserIO__Sequence * lhs, const denso_robot_core_interfaces__msg__UserIO__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!denso_robot_core_interfaces__msg__UserIO__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
denso_robot_core_interfaces__msg__UserIO__Sequence__copy(
  const denso_robot_core_interfaces__msg__UserIO__Sequence * input,
  denso_robot_core_interfaces__msg__UserIO__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(denso_robot_core_interfaces__msg__UserIO);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    denso_robot_core_interfaces__msg__UserIO * data =
      (denso_robot_core_interfaces__msg__UserIO *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!denso_robot_core_interfaces__msg__UserIO__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          denso_robot_core_interfaces__msg__UserIO__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!denso_robot_core_interfaces__msg__UserIO__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
