# generated from rosidl_generator_py/resource/_idl.py.em
# with input from denso_motion_control:srv/MoveToPose.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MoveToPose_Request(type):
    """Metaclass of message 'MoveToPose_Request'."""

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
                'denso_motion_control.srv.MoveToPose_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__move_to_pose__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__move_to_pose__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__move_to_pose__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__move_to_pose__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__move_to_pose__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class MoveToPose_Request(metaclass=Metaclass_MoveToPose_Request):
    """Message class 'MoveToPose_Request'."""

    __slots__ = [
        '_x',
        '_y',
        '_z',
        '_r1',
        '_r2',
        '_r3',
        '_r4',
        '_rotation_format',
        '_reference_frame',
        '_is_relative',
        '_cartesian_path',
        '_execute',
    ]

    _fields_and_field_types = {
        'x': 'double',
        'y': 'double',
        'z': 'double',
        'r1': 'double',
        'r2': 'double',
        'r3': 'double',
        'r4': 'double',
        'rotation_format': 'string',
        'reference_frame': 'string',
        'is_relative': 'boolean',
        'cartesian_path': 'boolean',
        'execute': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.x = kwargs.get('x', float())
        self.y = kwargs.get('y', float())
        self.z = kwargs.get('z', float())
        self.r1 = kwargs.get('r1', float())
        self.r2 = kwargs.get('r2', float())
        self.r3 = kwargs.get('r3', float())
        self.r4 = kwargs.get('r4', float())
        self.rotation_format = kwargs.get('rotation_format', str())
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
        if self.x != other.x:
            return False
        if self.y != other.y:
            return False
        if self.z != other.z:
            return False
        if self.r1 != other.r1:
            return False
        if self.r2 != other.r2:
            return False
        if self.r3 != other.r3:
            return False
        if self.r4 != other.r4:
            return False
        if self.rotation_format != other.rotation_format:
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
    def x(self):
        """Message field 'x'."""
        return self._x

    @x.setter
    def x(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'x' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'x' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._x = value

    @builtins.property
    def y(self):
        """Message field 'y'."""
        return self._y

    @y.setter
    def y(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'y' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'y' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._y = value

    @builtins.property
    def z(self):
        """Message field 'z'."""
        return self._z

    @z.setter
    def z(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'z' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'z' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._z = value

    @builtins.property
    def r1(self):
        """Message field 'r1'."""
        return self._r1

    @r1.setter
    def r1(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'r1' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'r1' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._r1 = value

    @builtins.property
    def r2(self):
        """Message field 'r2'."""
        return self._r2

    @r2.setter
    def r2(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'r2' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'r2' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._r2 = value

    @builtins.property
    def r3(self):
        """Message field 'r3'."""
        return self._r3

    @r3.setter
    def r3(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'r3' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'r3' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._r3 = value

    @builtins.property
    def r4(self):
        """Message field 'r4'."""
        return self._r4

    @r4.setter
    def r4(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'r4' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'r4' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._r4 = value

    @builtins.property
    def rotation_format(self):
        """Message field 'rotation_format'."""
        return self._rotation_format

    @rotation_format.setter
    def rotation_format(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'rotation_format' field must be of type 'str'"
        self._rotation_format = value

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


class Metaclass_MoveToPose_Response(type):
    """Metaclass of message 'MoveToPose_Response'."""

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
                'denso_motion_control.srv.MoveToPose_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__move_to_pose__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__move_to_pose__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__move_to_pose__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__move_to_pose__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__move_to_pose__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class MoveToPose_Response(metaclass=Metaclass_MoveToPose_Response):
    """Message class 'MoveToPose_Response'."""

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


class Metaclass_MoveToPose(type):
    """Metaclass of service 'MoveToPose'."""

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
                'denso_motion_control.srv.MoveToPose')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__move_to_pose

            from denso_motion_control.srv import _move_to_pose
            if _move_to_pose.Metaclass_MoveToPose_Request._TYPE_SUPPORT is None:
                _move_to_pose.Metaclass_MoveToPose_Request.__import_type_support__()
            if _move_to_pose.Metaclass_MoveToPose_Response._TYPE_SUPPORT is None:
                _move_to_pose.Metaclass_MoveToPose_Response.__import_type_support__()


class MoveToPose(metaclass=Metaclass_MoveToPose):
    from denso_motion_control.srv._move_to_pose import MoveToPose_Request as Request
    from denso_motion_control.srv._move_to_pose import MoveToPose_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
