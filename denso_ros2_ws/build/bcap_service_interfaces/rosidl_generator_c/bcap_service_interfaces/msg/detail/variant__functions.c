// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from bcap_service_interfaces:msg/Variant.idl
// generated code does not contain a copyright notice
#include "bcap_service_interfaces/msg/detail/variant__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `value`
#include "rosidl_runtime_c/string_functions.h"

bool
bcap_service_interfaces__msg__Variant__init(bcap_service_interfaces__msg__Variant * msg)
{
  if (!msg) {
    return false;
  }
  // vt
  // value
  if (!rosidl_runtime_c__String__init(&msg->value)) {
    bcap_service_interfaces__msg__Variant__fini(msg);
    return false;
  }
  return true;
}

void
bcap_service_interfaces__msg__Variant__fini(bcap_service_interfaces__msg__Variant * msg)
{
  if (!msg) {
    return;
  }
  // vt
  // value
  rosidl_runtime_c__String__fini(&msg->value);
}

bool
bcap_service_interfaces__msg__Variant__are_equal(const bcap_service_interfaces__msg__Variant * lhs, const bcap_service_interfaces__msg__Variant * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // vt
  if (lhs->vt != rhs->vt) {
    return false;
  }
  // value
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->value), &(rhs->value)))
  {
    return false;
  }
  return true;
}

bool
bcap_service_interfaces__msg__Variant__copy(
  const bcap_service_interfaces__msg__Variant * input,
  bcap_service_interfaces__msg__Variant * output)
{
  if (!input || !output) {
    return false;
  }
  // vt
  output->vt = input->vt;
  // value
  if (!rosidl_runtime_c__String__copy(
      &(input->value), &(output->value)))
  {
    return false;
  }
  return true;
}

bcap_service_interfaces__msg__Variant *
bcap_service_interfaces__msg__Variant__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bcap_service_interfaces__msg__Variant * msg = (bcap_service_interfaces__msg__Variant *)allocator.allocate(sizeof(bcap_service_interfaces__msg__Variant), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(bcap_service_interfaces__msg__Variant));
  bool success = bcap_service_interfaces__msg__Variant__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
bcap_service_interfaces__msg__Variant__destroy(bcap_service_interfaces__msg__Variant * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    bcap_service_interfaces__msg__Variant__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
bcap_service_interfaces__msg__Variant__Sequence__init(bcap_service_interfaces__msg__Variant__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bcap_service_interfaces__msg__Variant * data = NULL;

  if (size) {
    data = (bcap_service_interfaces__msg__Variant *)allocator.zero_allocate(size, sizeof(bcap_service_interfaces__msg__Variant), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = bcap_service_interfaces__msg__Variant__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        bcap_service_interfaces__msg__Variant__fini(&data[i - 1]);
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
bcap_service_interfaces__msg__Variant__Sequence__fini(bcap_service_interfaces__msg__Variant__Sequence * array)
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
      bcap_service_interfaces__msg__Variant__fini(&array->data[i]);
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

bcap_service_interfaces__msg__Variant__Sequence *
bcap_service_interfaces__msg__Variant__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bcap_service_interfaces__msg__Variant__Sequence * array = (bcap_service_interfaces__msg__Variant__Sequence *)allocator.allocate(sizeof(bcap_service_interfaces__msg__Variant__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = bcap_service_interfaces__msg__Variant__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
bcap_service_interfaces__msg__Variant__Sequence__destroy(bcap_service_interfaces__msg__Variant__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    bcap_service_interfaces__msg__Variant__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
bcap_service_interfaces__msg__Variant__Sequence__are_equal(const bcap_service_interfaces__msg__Variant__Sequence * lhs, const bcap_service_interfaces__msg__Variant__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!bcap_service_interfaces__msg__Variant__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
bcap_service_interfaces__msg__Variant__Sequence__copy(
  const bcap_service_interfaces__msg__Variant__Sequence * input,
  bcap_service_interfaces__msg__Variant__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(bcap_service_interfaces__msg__Variant);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    bcap_service_interfaces__msg__Variant * data =
      (bcap_service_interfaces__msg__Variant *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!bcap_service_interfaces__msg__Variant__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          bcap_service_interfaces__msg__Variant__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!bcap_service_interfaces__msg__Variant__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
