// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from denso_robot_core_interfaces:srv/ChangeMode.idl
// generated code does not contain a copyright notice
#include "denso_robot_core_interfaces/srv/detail/change_mode__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
denso_robot_core_interfaces__srv__ChangeMode_Request__init(denso_robot_core_interfaces__srv__ChangeMode_Request * msg)
{
  if (!msg) {
    return false;
  }
  // mode
  return true;
}

void
denso_robot_core_interfaces__srv__ChangeMode_Request__fini(denso_robot_core_interfaces__srv__ChangeMode_Request * msg)
{
  if (!msg) {
    return;
  }
  // mode
}

bool
denso_robot_core_interfaces__srv__ChangeMode_Request__are_equal(const denso_robot_core_interfaces__srv__ChangeMode_Request * lhs, const denso_robot_core_interfaces__srv__ChangeMode_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // mode
  if (lhs->mode != rhs->mode) {
    return false;
  }
  return true;
}

bool
denso_robot_core_interfaces__srv__ChangeMode_Request__copy(
  const denso_robot_core_interfaces__srv__ChangeMode_Request * input,
  denso_robot_core_interfaces__srv__ChangeMode_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // mode
  output->mode = input->mode;
  return true;
}

denso_robot_core_interfaces__srv__ChangeMode_Request *
denso_robot_core_interfaces__srv__ChangeMode_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_robot_core_interfaces__srv__ChangeMode_Request * msg = (denso_robot_core_interfaces__srv__ChangeMode_Request *)allocator.allocate(sizeof(denso_robot_core_interfaces__srv__ChangeMode_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(denso_robot_core_interfaces__srv__ChangeMode_Request));
  bool success = denso_robot_core_interfaces__srv__ChangeMode_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
denso_robot_core_interfaces__srv__ChangeMode_Request__destroy(denso_robot_core_interfaces__srv__ChangeMode_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    denso_robot_core_interfaces__srv__ChangeMode_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence__init(denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_robot_core_interfaces__srv__ChangeMode_Request * data = NULL;

  if (size) {
    data = (denso_robot_core_interfaces__srv__ChangeMode_Request *)allocator.zero_allocate(size, sizeof(denso_robot_core_interfaces__srv__ChangeMode_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = denso_robot_core_interfaces__srv__ChangeMode_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        denso_robot_core_interfaces__srv__ChangeMode_Request__fini(&data[i - 1]);
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
denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence__fini(denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence * array)
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
      denso_robot_core_interfaces__srv__ChangeMode_Request__fini(&array->data[i]);
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

denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence *
denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence * array = (denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence *)allocator.allocate(sizeof(denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence__destroy(denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence__are_equal(const denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence * lhs, const denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!denso_robot_core_interfaces__srv__ChangeMode_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence__copy(
  const denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence * input,
  denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(denso_robot_core_interfaces__srv__ChangeMode_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    denso_robot_core_interfaces__srv__ChangeMode_Request * data =
      (denso_robot_core_interfaces__srv__ChangeMode_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!denso_robot_core_interfaces__srv__ChangeMode_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          denso_robot_core_interfaces__srv__ChangeMode_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!denso_robot_core_interfaces__srv__ChangeMode_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
denso_robot_core_interfaces__srv__ChangeMode_Response__init(denso_robot_core_interfaces__srv__ChangeMode_Response * msg)
{
  if (!msg) {
    return false;
  }
  // hresult
  return true;
}

void
denso_robot_core_interfaces__srv__ChangeMode_Response__fini(denso_robot_core_interfaces__srv__ChangeMode_Response * msg)
{
  if (!msg) {
    return;
  }
  // hresult
}

bool
denso_robot_core_interfaces__srv__ChangeMode_Response__are_equal(const denso_robot_core_interfaces__srv__ChangeMode_Response * lhs, const denso_robot_core_interfaces__srv__ChangeMode_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // hresult
  if (lhs->hresult != rhs->hresult) {
    return false;
  }
  return true;
}

bool
denso_robot_core_interfaces__srv__ChangeMode_Response__copy(
  const denso_robot_core_interfaces__srv__ChangeMode_Response * input,
  denso_robot_core_interfaces__srv__ChangeMode_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // hresult
  output->hresult = input->hresult;
  return true;
}

denso_robot_core_interfaces__srv__ChangeMode_Response *
denso_robot_core_interfaces__srv__ChangeMode_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_robot_core_interfaces__srv__ChangeMode_Response * msg = (denso_robot_core_interfaces__srv__ChangeMode_Response *)allocator.allocate(sizeof(denso_robot_core_interfaces__srv__ChangeMode_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(denso_robot_core_interfaces__srv__ChangeMode_Response));
  bool success = denso_robot_core_interfaces__srv__ChangeMode_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
denso_robot_core_interfaces__srv__ChangeMode_Response__destroy(denso_robot_core_interfaces__srv__ChangeMode_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    denso_robot_core_interfaces__srv__ChangeMode_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence__init(denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_robot_core_interfaces__srv__ChangeMode_Response * data = NULL;

  if (size) {
    data = (denso_robot_core_interfaces__srv__ChangeMode_Response *)allocator.zero_allocate(size, sizeof(denso_robot_core_interfaces__srv__ChangeMode_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = denso_robot_core_interfaces__srv__ChangeMode_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        denso_robot_core_interfaces__srv__ChangeMode_Response__fini(&data[i - 1]);
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
denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence__fini(denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence * array)
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
      denso_robot_core_interfaces__srv__ChangeMode_Response__fini(&array->data[i]);
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

denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence *
denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence * array = (denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence *)allocator.allocate(sizeof(denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence__destroy(denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence__are_equal(const denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence * lhs, const denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!denso_robot_core_interfaces__srv__ChangeMode_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence__copy(
  const denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence * input,
  denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(denso_robot_core_interfaces__srv__ChangeMode_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    denso_robot_core_interfaces__srv__ChangeMode_Response * data =
      (denso_robot_core_interfaces__srv__ChangeMode_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!denso_robot_core_interfaces__srv__ChangeMode_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          denso_robot_core_interfaces__srv__ChangeMode_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!denso_robot_core_interfaces__srv__ChangeMode_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
