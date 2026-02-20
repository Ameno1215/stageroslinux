# generated from rosidl_generator_py/resource/_idl.py.em
# with input from denso_robot_core_interfaces:msg/PoseData.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'value'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_PoseData(type):
    """Metaclass of message 'PoseData'."""

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
            module = import_type_support('denso_robot_core_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'denso_robot_core_interfaces.msg.PoseData')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__pose_data
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__pose_data
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__pose_data
            cls._TYPE_SUPPORT = module.type_support_msg__msg__pose_data
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__pose_data

            from denso_robot_core_interfaces.msg import ExJoints
            if ExJoints.__class__._TYPE_SUPPORT is None:
                ExJoints.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class PoseData(metaclass=Metaclass_PoseData):
    """Message class 'PoseData'."""

    __slots__ = [
        '_value',
        '_type',
        '_passflag',
        '_exjoints',
    ]

    _fields_and_field_types = {
        'value': 'sequence<float>',
        'type': 'int32',
        'passflag': 'int32',
        'exjoints': 'denso_robot_core_interfaces/ExJoints',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['denso_robot_core_interfaces', 'msg'], 'ExJoints'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.value = array.array('f', kwargs.get('value', []))
        self.type = kwargs.get('type', int())
        self.passflag = kwargs.get('passflag', int())
        from denso_robot_core_interfaces.msg import ExJoints
        self.exjoints = kwargs.get('exjoints', ExJoints())

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
        if self.value != other.value:
            return False
        if self.type != other.type:
            return False
        if self.passflag != other.passflag:
            return False
        if self.exjoints != other.exjoints:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def value(self):
        """Message field 'value'."""
        return self._value

    @value.setter
    def value(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'value' array.array() must have the type code of 'f'"
            self._value = value
            return
        if __debug__:
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
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'value' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._value = array.array('f', value)

    @builtins.property  # noqa: A003
    def type(self):  # noqa: A003
        """Message field 'type'."""
        return self._type

    @type.setter  # noqa: A003
    def type(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'type' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'type' field must be an integer in [-2147483648, 2147483647]"
        self._type = value

    @builtins.property
    def passflag(self):
        """Message field 'passflag'."""
        return self._passflag

    @passflag.setter
    def passflag(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'passflag' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'passflag' field must be an integer in [-2147483648, 2147483647]"
        self._passflag = value

    @builtins.property
    def exjoints(self):
        """Message field 'exjoints'."""
        return self._exjoints

    @exjoints.setter
    def exjoints(self, value):
        if __debug__:
            from denso_robot_core_interfaces.msg import ExJoints
            assert \
                isinstance(value, ExJoints), \
                "The 'exjoints' field must be a sub message of type 'ExJoints'"
        self._exjoints = value
