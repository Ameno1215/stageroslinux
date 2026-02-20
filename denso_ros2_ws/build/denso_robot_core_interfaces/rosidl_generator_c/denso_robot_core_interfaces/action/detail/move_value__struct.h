// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from denso_robot_core_interfaces:action/MoveValue.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__MOVE_VALUE__STRUCT_H_
#define DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__MOVE_VALUE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'pose'
#include "denso_robot_core_interfaces/msg/detail/pose_data__struct.h"
// Member 'option'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/MoveValue in the package denso_robot_core_interfaces.
typedef struct denso_robot_core_interfaces__action__MoveValue_Goal
{
  int32_t comp;
  denso_robot_core_interfaces__msg__PoseData pose;
  rosidl_runtime_c__String option;
} denso_robot_core_interfaces__action__MoveValue_Goal;

// Struct for a sequence of denso_robot_core_interfaces__action__MoveValue_Goal.
typedef struct denso_robot_core_interfaces__action__MoveValue_Goal__Sequence
{
  denso_robot_core_interfaces__action__MoveValue_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_robot_core_interfaces__action__MoveValue_Goal__Sequence;


// Constants defined in the message

/// Struct defined in action/MoveValue in the package denso_robot_core_interfaces.
typedef struct denso_robot_core_interfaces__action__MoveValue_Result
{
  int32_t hresult;
} denso_robot_core_interfaces__action__MoveValue_Result;

// Struct for a sequence of denso_robot_core_interfaces__action__MoveValue_Result.
typedef struct denso_robot_core_interfaces__action__MoveValue_Result__Sequence
{
  denso_robot_core_interfaces__action__MoveValue_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_robot_core_interfaces__action__MoveValue_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'pose'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in action/MoveValue in the package denso_robot_core_interfaces.
typedef struct denso_robot_core_interfaces__action__MoveValue_Feedback
{
  rosidl_runtime_c__double__Sequence pose;
} denso_robot_core_interfaces__action__MoveValue_Feedback;

// Struct for a sequence of denso_robot_core_interfaces__action__MoveValue_Feedback.
typedef struct denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence
{
  denso_robot_core_interfaces__action__MoveValue_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "denso_robot_core_interfaces/action/detail/move_value__struct.h"

/// Struct defined in action/MoveValue in the package denso_robot_core_interfaces.
typedef struct denso_robot_core_interfaces__action__MoveValue_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  denso_robot_core_interfaces__action__MoveValue_Goal goal;
} denso_robot_core_interfaces__action__MoveValue_SendGoal_Request;

// Struct for a sequence of denso_robot_core_interfaces__action__MoveValue_SendGoal_Request.
typedef struct denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence
{
  denso_robot_core_interfaces__action__MoveValue_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/MoveValue in the package denso_robot_core_interfaces.
typedef struct denso_robot_core_interfaces__action__MoveValue_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} denso_robot_core_interfaces__action__MoveValue_SendGoal_Response;

// Struct for a sequence of denso_robot_core_interfaces__action__MoveValue_SendGoal_Response.
typedef struct denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence
{
  denso_robot_core_interfaces__action__MoveValue_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/MoveValue in the package denso_robot_core_interfaces.
typedef struct denso_robot_core_interfaces__action__MoveValue_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} denso_robot_core_interfaces__action__MoveValue_GetResult_Request;

// Struct for a sequence of denso_robot_core_interfaces__action__MoveValue_GetResult_Request.
typedef struct denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence
{
  denso_robot_core_interfaces__action__MoveValue_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "denso_robot_core_interfaces/action/detail/move_value__struct.h"

/// Struct defined in action/MoveValue in the package denso_robot_core_interfaces.
typedef struct denso_robot_core_interfaces__action__MoveValue_GetResult_Response
{
  int8_t status;
  denso_robot_core_interfaces__action__MoveValue_Result result;
} denso_robot_core_interfaces__action__MoveValue_GetResult_Response;

// Struct for a sequence of denso_robot_core_interfaces__action__MoveValue_GetResult_Response.
typedef struct denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence
{
  denso_robot_core_interfaces__action__MoveValue_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "denso_robot_core_interfaces/action/detail/move_value__struct.h"

/// Struct defined in action/MoveValue in the package denso_robot_core_interfaces.
typedef struct denso_robot_core_interfaces__action__MoveValue_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  denso_robot_core_interfaces__action__MoveValue_Feedback feedback;
} denso_robot_core_interfaces__action__MoveValue_FeedbackMessage;

// Struct for a sequence of denso_robot_core_interfaces__action__MoveValue_FeedbackMessage.
typedef struct denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence
{
  denso_robot_core_interfaces__action__MoveValue_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__MOVE_VALUE__STRUCT_H_
