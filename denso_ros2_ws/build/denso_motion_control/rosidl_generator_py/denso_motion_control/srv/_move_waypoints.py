# generated from rosidl_generator_py/resource/_idl.py.em
# with input from denso_motion_control:srv/MoveWaypoints.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MoveWaypoints_Request(type):
    """Metaclass of message 'MoveWaypoints_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('denso_motion_control')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'denso_motion_control.srv.MoveWaypoints_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__move_waypoints__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__move_waypoints__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__move_waypoints__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__move_waypoints__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__move_waypoints__request

            from geometry_msgs.msg import Pose
            if Pose.__class__._TYPE_SUPPORT is None:
                Pose.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class MoveWaypoints_Request(metaclass=Metaclass_MoveWaypoints_Request):
    """Message class 'MoveWaypoints_Request'."""

    __slots__ = [
        '_waypoints',
        '_reference_frame',
        '_is_relative',
        '_cartesian_path',
        '_execute',
    ]

    _fields_and_field_types = {
        'waypoints': 'sequence<geometry_msgs/Pose>',
        'reference_frame': 'string',
        'is_relative': 'boolean',
        'cartesian_path': 'boolean',
        'execute': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Pose')),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.waypoints = kwargs.get('waypoints', [])
        self.reference_frame = kwargs.get('reference_frame', str())
        self.is_relative = kwargs.get('is_relative', bool())
        self.cartesian_path = kwargs.get('cartesian_path', bool())
        self.execute = kwargs.get('execute', bool())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.waypoints != other.waypoints:
            return False
        if self.reference_frame != other.reference_frame:
            return False
        if self.is_relative != other.is_relative:
            return False
        if self.cartesian_path != other.cartesian_path:
            return False
        if self.execute != other.execute:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def waypoints(self):
        """Message field 'waypoints'."""
        return self._waypoints

    @waypoints.setter
    def waypoints(self, value):
        if __debug__:
            from geometry_msgs.msg import Pose
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, Pose) for v in value) and
                 True), \
                "The 'waypoints' field must be a set or sequence and each value of type 'Pose'"
        self._waypoints = value

    @builtins.property
    def reference_frame(self):
        """Message field 'reference_frame'."""
        return self._reference_frame

    @reference_frame.setter
    def reference_frame(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'reference_frame' field must be of type 'str'"
        self._reference_frame = value

    @builtins.property
    def is_relative(self):
        """Message field 'is_relative'."""
        return self._is_relative

    @is_relative.setter
    def is_relative(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_relative' field must be of type 'bool'"
        self._is_relative = value

    @builtins.property
    def cartesian_path(self):
        """Message field 'cartesian_path'."""
        return self._cartesian_path

    @cartesian_path.setter
    def cartesian_path(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'cartesian_path' field must be of type 'bool'"
        self._cartesian_path = value

    @builtins.property
    def execute(self):
        """Message field 'execute'."""
        return self._execute

    @execute.setter
    def execute(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'execute' field must be of type 'bool'"
        self._execute = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_MoveWaypoints_Response(type):
    """Metaclass of message 'MoveWaypoints_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('denso_motion_control')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'denso_motion_control.srv.MoveWaypoints_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__move_waypoints__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__move_waypoints__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__move_waypoints__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__move_waypoints__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__move_waypoints__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class MoveWaypoints_Response(metaclass=Metaclass_MoveWaypoints_Response):
    """Message class 'MoveWaypoints_Response'."""

    __slots__ = [
        '_success',
        '_message',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.message = kwargs.get('message', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.success != other.success:
            return False
        if self.message != other.message:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value

    @builtins.property
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value


class Metaclass_MoveWaypoints(type):
    """Metaclass of service 'MoveWaypoints'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('denso_motion_control')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'denso_motion_control.srv.MoveWaypoints')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__move_waypoints

            from denso_motion_control.srv import _move_waypoints
            if _move_waypoints.Metaclass_MoveWaypoints_Request._TYPE_SUPPORT is None:
                _move_waypoints.Metaclass_MoveWaypoints_Request.__import_type_support__()
            if _move_waypoints.Metaclass_MoveWaypoints_Response._TYPE_SUPPORT is None:
                _move_waypoints.Metaclass_MoveWaypoints_Response.__import_type_support__()


class MoveWaypoints(metaclass=Metaclass_MoveWaypoints):
    from denso_motion_control.srv._move_waypoints import MoveWaypoints_Request as Request
    from denso_motion_control.srv._move_waypoints import MoveWaypoints_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
