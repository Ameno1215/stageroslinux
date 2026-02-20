// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from bcap_service_interfaces:srv/Bcap.idl
// generated code does not contain a copyright notice
#include "bcap_service_interfaces/srv/detail/bcap__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `vnt_args`
#include "bcap_service_interfaces/msg/detail/variant__functions.h"

bool
bcap_service_interfaces__srv__Bcap_Request__init(bcap_service_interfaces__srv__Bcap_Request * msg)
{
  if (!msg) {
    return false;
  }
  // func_id
  // vnt_args
  if (!bcap_service_interfaces__msg__Variant__Sequence__init(&msg->vnt_args, 0)) {
    bcap_service_interfaces__srv__Bcap_Request__fini(msg);
    return false;
  }
  return true;
}

void
bcap_service_interfaces__srv__Bcap_Request__fini(bcap_service_interfaces__srv__Bcap_Request * msg)
{
  if (!msg) {
    return;
  }
  // func_id
  // vnt_args
  bcap_service_interfaces__msg__Variant__Sequence__fini(&msg->vnt_args);
}

bool
bcap_service_interfaces__srv__Bcap_Request__are_equal(const bcap_service_interfaces__srv__Bcap_Request * lhs, const bcap_service_interfaces__srv__Bcap_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // func_id
  if (lhs->func_id != rhs->func_id) {
    return false;
  }
  // vnt_args
  if (!bcap_service_interfaces__msg__Variant__Sequence__are_equal(
      &(lhs->vnt_args), &(rhs->vnt_args)))
  {
    return false;
  }
  return true;
}

bool
bcap_service_interfaces__srv__Bcap_Request__copy(
  const bcap_service_interfaces__srv__Bcap_Request * input,
  bcap_service_interfaces__srv__Bcap_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // func_id
  output->func_id = input->func_id;
  // vnt_args
  if (!bcap_service_interfaces__msg__Variant__Sequence__copy(
      &(input->vnt_args), &(output->vnt_args)))
  {
    return false;
  }
  return true;
}

bcap_service_interfaces__srv__Bcap_Request *
bcap_service_interfaces__srv__Bcap_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bcap_service_interfaces__srv__Bcap_Request * msg = (bcap_service_interfaces__srv__Bcap_Request *)allocator.allocate(sizeof(bcap_service_interfaces__srv__Bcap_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(bcap_service_interfaces__srv__Bcap_Request));
  bool success = bcap_service_interfaces__srv__Bcap_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
bcap_service_interfaces__srv__Bcap_Request__destroy(bcap_service_interfaces__srv__Bcap_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    bcap_service_interfaces__srv__Bcap_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
bcap_service_interfaces__srv__Bcap_Request__Sequence__init(bcap_service_interfaces__srv__Bcap_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bcap_service_interfaces__srv__Bcap_Request * data = NULL;

  if (size) {
    data = (bcap_service_interfaces__srv__Bcap_Request *)allocator.zero_allocate(size, sizeof(bcap_service_interfaces__srv__Bcap_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = bcap_service_interfaces__srv__Bcap_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        bcap_service_interfaces__srv__Bcap_Request__fini(&data[i - 1]);
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
bcap_service_interfaces__srv__Bcap_Request__Sequence__fini(bcap_service_interfaces__srv__Bcap_Request__Sequence * array)
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
      bcap_service_interfaces__srv__Bcap_Request__fini(&array->data[i]);
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

bcap_service_interfaces__srv__Bcap_Request__Sequence *
bcap_service_interfaces__srv__Bcap_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bcap_service_interfaces__srv__Bcap_Request__Sequence * array = (bcap_service_interfaces__srv__Bcap_Request__Sequence *)allocator.allocate(sizeof(bcap_service_interfaces__srv__Bcap_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = bcap_service_interfaces__srv__Bcap_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
bcap_service_interfaces__srv__Bcap_Request__Sequence__destroy(bcap_service_interfaces__srv__Bcap_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    bcap_service_interfaces__srv__Bcap_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
bcap_service_interfaces__srv__Bcap_Request__Sequence__are_equal(const bcap_service_interfaces__srv__Bcap_Request__Sequence * lhs, const bcap_service_interfaces__srv__Bcap_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!bcap_service_interfaces__srv__Bcap_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
bcap_service_interfaces__srv__Bcap_Request__Sequence__copy(
  const bcap_service_interfaces__srv__Bcap_Request__Sequence * input,
  bcap_service_interfaces__srv__Bcap_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(bcap_service_interfaces__srv__Bcap_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    bcap_service_interfaces__srv__Bcap_Request * data =
      (bcap_service_interfaces__srv__Bcap_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!bcap_service_interfaces__srv__Bcap_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          bcap_service_interfaces__srv__Bcap_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!bcap_service_interfaces__srv__Bcap_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `vnt_ret`
// already included above
// #include "bcap_service_interfaces/msg/detail/variant__functions.h"

bool
bcap_service_interfaces__srv__Bcap_Response__init(bcap_service_interfaces__srv__Bcap_Response * msg)
{
  if (!msg) {
    return false;
  }
  // hresult
  // vnt_ret
  if (!bcap_service_interfaces__msg__Variant__init(&msg->vnt_ret)) {
    bcap_service_interfaces__srv__Bcap_Response__fini(msg);
    return false;
  }
  return true;
}

void
bcap_service_interfaces__srv__Bcap_Response__fini(bcap_service_interfaces__srv__Bcap_Response * msg)
{
  if (!msg) {
    return;
  }
  // hresult
  // vnt_ret
  bcap_service_interfaces__msg__Variant__fini(&msg->vnt_ret);
}

bool
bcap_service_interfaces__srv__Bcap_Response__are_equal(const bcap_service_interfaces__srv__Bcap_Response * lhs, const bcap_service_interfaces__srv__Bcap_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // hresult
  if (lhs->hresult != rhs->hresult) {
    return false;
  }
  // vnt_ret
  if (!bcap_service_interfaces__msg__Variant__are_equal(
      &(lhs->vnt_ret), &(rhs->vnt_ret)))
  {
    return false;
  }
  return true;
}

bool
bcap_service_interfaces__srv__Bcap_Response__copy(
  const bcap_service_interfaces__srv__Bcap_Response * input,
  bcap_service_interfaces__srv__Bcap_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // hresult
  output->hresult = input->hresult;
  // vnt_ret
  if (!bcap_service_interfaces__msg__Variant__copy(
      &(input->vnt_ret), &(output->vnt_ret)))
  {
    return false;
  }
  return true;
}

bcap_service_interfaces__srv__Bcap_Response *
bcap_service_interfaces__srv__Bcap_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bcap_service_interfaces__srv__Bcap_Response * msg = (bcap_service_interfaces__srv__Bcap_Response *)allocator.allocate(sizeof(bcap_service_interfaces__srv__Bcap_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(bcap_service_interfaces__srv__Bcap_Response));
  bool success = bcap_service_interfaces__srv__Bcap_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
bcap_service_interfaces__srv__Bcap_Response__destroy(bcap_service_interfaces__srv__Bcap_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    bcap_service_interfaces__srv__Bcap_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
bcap_service_interfaces__srv__Bcap_Response__Sequence__init(bcap_service_interfaces__srv__Bcap_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bcap_service_interfaces__srv__Bcap_Response * data = NULL;

  if (size) {
    data = (bcap_service_interfaces__srv__Bcap_Response *)allocator.zero_allocate(size, sizeof(bcap_service_interfaces__srv__Bcap_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = bcap_service_interfaces__srv__Bcap_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        bcap_service_interfaces__srv__Bcap_Response__fini(&data[i - 1]);
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
bcap_service_interfaces__srv__Bcap_Response__Sequence__fini(bcap_service_interfaces__srv__Bcap_Response__Sequence * array)
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
      bcap_service_interfaces__srv__Bcap_Response__fini(&array->data[i]);
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

bcap_service_interfaces__srv__Bcap_Response__Sequence *
bcap_service_interfaces__srv__Bcap_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bcap_service_interfaces__srv__Bcap_Response__Sequence * array = (bcap_service_interfaces__srv__Bcap_Response__Sequence *)allocator.allocate(sizeof(bcap_service_interfaces__srv__Bcap_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = bcap_service_interfaces__srv__Bcap_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
bcap_service_interfaces__srv__Bcap_Response__Sequence__destroy(bcap_service_interfaces__srv__Bcap_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    bcap_service_interfaces__srv__Bcap_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
bcap_service_interfaces__srv__Bcap_Response__Sequence__are_equal(const bcap_service_interfaces__srv__Bcap_Response__Sequence * lhs, const bcap_service_interfaces__srv__Bcap_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!bcap_service_interfaces__srv__Bcap_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
bcap_service_interfaces__srv__Bcap_Response__Sequence__copy(
  const bcap_service_interfaces__srv__Bcap_Response__Sequence * input,
  bcap_service_interfaces__srv__Bcap_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(bcap_service_interfaces__srv__Bcap_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    bcap_service_interfaces__srv__Bcap_Response * data =
      (bcap_service_interfaces__srv__Bcap_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!bcap_service_interfaces__srv__Bcap_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          bcap_service_interfaces__srv__Bcap_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!bcap_service_interfaces__srv__Bcap_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
