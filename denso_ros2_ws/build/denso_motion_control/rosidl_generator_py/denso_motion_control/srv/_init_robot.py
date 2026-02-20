# generated from rosidl_generator_py/resource/_idl.py.em
# with input from denso_motion_control:srv/InitRobot.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_InitRobot_Request(type):
    """Metaclass of message 'InitRobot_Request'."""

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
                'denso_motion_control.srv.InitRobot_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__init_robot__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__init_robot__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__init_robot__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__init_robot__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__init_robot__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class InitRobot_Request(metaclass=Metaclass_InitRobot_Request):
    """Message class 'InitRobot_Request'."""

    __slots__ = [
        '_model',
        '_planning_group',
        '_velocity_scale',
        '_accel_scale',
    ]

    _fields_and_field_types = {
        'model': 'string',
        'planning_group': 'string',
        'velocity_scale': 'double',
        'accel_scale': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.model = kwargs.get('model', str())
        self.planning_group = kwargs.get('planning_group', str())
        self.velocity_scale = kwargs.get('velocity_scale', float())
        self.accel_scale = kwargs.get('accel_scale', float())

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
        if self.model != other.model:
            return False
        if self.planning_group != other.planning_group:
            return False
        if self.velocity_scale != other.velocity_scale:
            return False
        if self.accel_scale != other.accel_scale:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def model(self):
        """Message field 'model'."""
        return self._model

    @model.setter
    def model(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'model' field must be of type 'str'"
        self._model = value

    @builtins.property
    def planning_group(self):
        """Message field 'planning_group'."""
        return self._planning_group

    @planning_group.setter
    def planning_group(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'planning_group' field must be of type 'str'"
        self._planning_group = value

    @builtins.property
    def velocity_scale(self):
        """Message field 'velocity_scale'."""
        return self._velocity_scale

    @velocity_scale.setter
    def velocity_scale(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'velocity_scale' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'velocity_scale' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._velocity_scale = value

    @builtins.property
    def accel_scale(self):
        """Message field 'accel_scale'."""
        return self._accel_scale

    @accel_scale.setter
    def accel_scale(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'accel_scale' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'accel_scale' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._accel_scale = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_InitRobot_Response(type):
    """Metaclass of message 'InitRobot_Response'."""

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
                'denso_motion_control.srv.InitRobot_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__init_robot__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__init_robot__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__init_robot__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__init_robot__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__init_robot__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class InitRobot_Response(metaclass=Metaclass_InitRobot_Response):
    """Message class 'InitRobot_Response'."""

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


class Metaclass_InitRobot(type):
    """Metaclass of service 'InitRobot'."""

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
                'denso_motion_control.srv.InitRobot')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__init_robot

            from denso_motion_control.srv import _init_robot
            if _init_robot.Metaclass_InitRobot_Request._TYPE_SUPPORT is None:
                _init_robot.Metaclass_InitRobot_Request.__import_type_support__()
            if _init_robot.Metaclass_InitRobot_Response._TYPE_SUPPORT is None:
                _init_robot.Metaclass_InitRobot_Response.__import_type_support__()


class InitRobot(metaclass=Metaclass_InitRobot):
    from denso_motion_control.srv._init_robot import InitRobot_Request as Request
    from denso_motion_control.srv._init_robot import InitRobot_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
