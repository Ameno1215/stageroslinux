// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from denso_motion_control:srv/MoveJoints.idl
// generated code does not contain a copyright notice
#include "denso_motion_control/srv/detail/move_joints__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `joints`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
denso_motion_control__srv__MoveJoints_Request__init(denso_motion_control__srv__MoveJoints_Request * msg)
{
  if (!msg) {
    return false;
  }
  // joints
  if (!rosidl_runtime_c__double__Sequence__init(&msg->joints, 0)) {
    denso_motion_control__srv__MoveJoints_Request__fini(msg);
    return false;
  }
  // is_relative
  // execute
  return true;
}

void
denso_motion_control__srv__MoveJoints_Request__fini(denso_motion_control__srv__MoveJoints_Request * msg)
{
  if (!msg) {
    return;
  }
  // joints
  rosidl_runtime_c__double__Sequence__fini(&msg->joints);
  // is_relative
  // execute
}

bool
denso_motion_control__srv__MoveJoints_Request__are_equal(const denso_motion_control__srv__MoveJoints_Request * lhs, const denso_motion_control__srv__MoveJoints_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // joints
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->joints), &(rhs->joints)))
  {
    return false;
  }
  // is_relative
  if (lhs->is_relative != rhs->is_relative) {
    return false;
  }
  // execute
  if (lhs->execute != rhs->execute) {
    return false;
  }
  return true;
}

bool
denso_motion_control__srv__MoveJoints_Request__copy(
  const denso_motion_control__srv__MoveJoints_Request * input,
  denso_motion_control__srv__MoveJoints_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // joints
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->joints), &(output->joints)))
  {
    return false;
  }
  // is_relative
  output->is_relative = input->is_relative;
  // execute
  output->execute = input->execute;
  return true;
}

denso_motion_control__srv__MoveJoints_Request *
denso_motion_control__srv__MoveJoints_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_motion_control__srv__MoveJoints_Request * msg = (denso_motion_control__srv__MoveJoints_Request *)allocator.allocate(sizeof(denso_motion_control__srv__MoveJoints_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(denso_motion_control__srv__MoveJoints_Request));
  bool success = denso_motion_control__srv__MoveJoints_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
denso_motion_control__srv__MoveJoints_Request__destroy(denso_motion_control__srv__MoveJoints_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    denso_motion_control__srv__MoveJoints_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
denso_motion_control__srv__MoveJoints_Request__Sequence__init(denso_motion_control__srv__MoveJoints_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_motion_control__srv__MoveJoints_Request * data = NULL;

  if (size) {
    data = (denso_motion_control__srv__MoveJoints_Request *)allocator.zero_allocate(size, sizeof(denso_motion_control__srv__MoveJoints_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = denso_motion_control__srv__MoveJoints_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        denso_motion_control__srv__MoveJoints_Request__fini(&data[i - 1]);
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
denso_motion_control__srv__MoveJoints_Request__Sequence__fini(denso_motion_control__srv__MoveJoints_Request__Sequence * array)
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
      denso_motion_control__srv__MoveJoints_Request__fini(&array->data[i]);
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

denso_motion_control__srv__MoveJoints_Request__Sequence *
denso_motion_control__srv__MoveJoints_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_motion_control__srv__MoveJoints_Request__Sequence * array = (denso_motion_control__srv__MoveJoints_Request__Sequence *)allocator.allocate(sizeof(denso_motion_control__srv__MoveJoints_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = denso_motion_control__srv__MoveJoints_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
denso_motion_control__srv__MoveJoints_Request__Sequence__destroy(denso_motion_control__srv__MoveJoints_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    denso_motion_control__srv__MoveJoints_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
denso_motion_control__srv__MoveJoints_Request__Sequence__are_equal(const denso_motion_control__srv__MoveJoints_Request__Sequence * lhs, const denso_motion_control__srv__MoveJoints_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!denso_motion_control__srv__MoveJoints_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
denso_motion_control__srv__MoveJoints_Request__Sequence__copy(
  const denso_motion_control__srv__MoveJoints_Request__Sequence * input,
  denso_motion_control__srv__MoveJoints_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(denso_motion_control__srv__MoveJoints_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    denso_motion_control__srv__MoveJoints_Request * data =
      (denso_motion_control__srv__MoveJoints_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!denso_motion_control__srv__MoveJoints_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          denso_motion_control__srv__MoveJoints_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!denso_motion_control__srv__MoveJoints_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
denso_motion_control__srv__MoveJoints_Response__init(denso_motion_control__srv__MoveJoints_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    denso_motion_control__srv__MoveJoints_Response__fini(msg);
    return false;
  }
  return true;
}

void
denso_motion_control__srv__MoveJoints_Response__fini(denso_motion_control__srv__MoveJoints_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
denso_motion_control__srv__MoveJoints_Response__are_equal(const denso_motion_control__srv__MoveJoints_Response * lhs, const denso_motion_control__srv__MoveJoints_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
denso_motion_control__srv__MoveJoints_Response__copy(
  const denso_motion_control__srv__MoveJoints_Response * input,
  denso_motion_control__srv__MoveJoints_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

denso_motion_control__srv__MoveJoints_Response *
denso_motion_control__srv__MoveJoints_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_motion_control__srv__MoveJoints_Response * msg = (denso_motion_control__srv__MoveJoints_Response *)allocator.allocate(sizeof(denso_motion_control__srv__MoveJoints_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(denso_motion_control__srv__MoveJoints_Response));
  bool success = denso_motion_control__srv__MoveJoints_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
denso_motion_control__srv__MoveJoints_Response__destroy(denso_motion_control__srv__MoveJoints_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    denso_motion_control__srv__MoveJoints_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
denso_motion_control__srv__MoveJoints_Response__Sequence__init(denso_motion_control__srv__MoveJoints_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_motion_control__srv__MoveJoints_Response * data = NULL;

  if (size) {
    data = (denso_motion_control__srv__MoveJoints_Response *)allocator.zero_allocate(size, sizeof(denso_motion_control__srv__MoveJoints_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = denso_motion_control__srv__MoveJoints_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        denso_motion_control__srv__MoveJoints_Response__fini(&data[i - 1]);
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
denso_motion_control__srv__MoveJoints_Response__Sequence__fini(denso_motion_control__srv__MoveJoints_Response__Sequence * array)
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
      denso_motion_control__srv__MoveJoints_Response__fini(&array->data[i]);
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

denso_motion_control__srv__MoveJoints_Response__Sequence *
denso_motion_control__srv__MoveJoints_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_motion_control__srv__MoveJoints_Response__Sequence * array = (denso_motion_control__srv__MoveJoints_Response__Sequence *)allocator.allocate(sizeof(denso_motion_control__srv__MoveJoints_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = denso_motion_control__srv__MoveJoints_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
denso_motion_control__srv__MoveJoints_Response__Sequence__destroy(denso_motion_control__srv__MoveJoints_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    denso_motion_control__srv__MoveJoints_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
denso_motion_control__srv__MoveJoints_Response__Sequence__are_equal(const denso_motion_control__srv__MoveJoints_Response__Sequence * lhs, const denso_motion_control__srv__MoveJoints_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!denso_motion_control__srv__MoveJoints_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
denso_motion_control__srv__MoveJoints_Response__Sequence__copy(
  const denso_motion_control__srv__MoveJoints_Response__Sequence * input,
  denso_motion_control__srv__MoveJoints_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(denso_motion_control__srv__MoveJoints_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    denso_motion_control__srv__MoveJoints_Response * data =
      (denso_motion_control__srv__MoveJoints_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!denso_motion_control__srv__MoveJoints_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          denso_motion_control__srv__MoveJoints_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!denso_motion_control__srv__MoveJoints_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
