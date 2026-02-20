# generated from rosidl_generator_py/resource/_idl.py.em
# with input from bcap_service_interfaces:srv/Bcap.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Bcap_Request(type):
    """Metaclass of message 'Bcap_Request'."""

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
            module = import_type_support('bcap_service_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'bcap_service_interfaces.srv.Bcap_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__bcap__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__bcap__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__bcap__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__bcap__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__bcap__request

            from bcap_service_interfaces.msg import Variant
            if Variant.__class__._TYPE_SUPPORT is None:
                Variant.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Bcap_Request(metaclass=Metaclass_Bcap_Request):
    """Message class 'Bcap_Request'."""

    __slots__ = [
        '_func_id',
        '_vnt_args',
    ]

    _fields_and_field_types = {
        'func_id': 'int32',
        'vnt_args': 'sequence<bcap_service_interfaces/Variant>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['bcap_service_interfaces', 'msg'], 'Variant')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.func_id = kwargs.get('func_id', int())
        self.vnt_args = kwargs.get('vnt_args', [])

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
        if self.func_id != other.func_id:
            return False
        if self.vnt_args != other.vnt_args:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def func_id(self):
        """Message field 'func_id'."""
        return self._func_id

    @func_id.setter
    def func_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'func_id' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'func_id' field must be an integer in [-2147483648, 2147483647]"
        self._func_id = value

    @builtins.property
    def vnt_args(self):
        """Message field 'vnt_args'."""
        return self._vnt_args

    @vnt_args.setter
    def vnt_args(self, value):
        if __debug__:
            from bcap_service_interfaces.msg import Variant
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
                 all(isinstance(v, Variant) for v in value) and
                 True), \
                "The 'vnt_args' field must be a set or sequence and each value of type 'Variant'"
        self._vnt_args = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_Bcap_Response(type):
    """Metaclass of message 'Bcap_Response'."""

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
            module = import_type_support('bcap_service_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'bcap_service_interfaces.srv.Bcap_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__bcap__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__bcap__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__bcap__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__bcap__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__bcap__response

            from bcap_service_interfaces.msg import Variant
            if Variant.__class__._TYPE_SUPPORT is None:
                Variant.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Bcap_Response(metaclass=Metaclass_Bcap_Response):
    """Message class 'Bcap_Response'."""

    __slots__ = [
        '_hresult',
        '_vnt_ret',
    ]

    _fields_and_field_types = {
        'hresult': 'int32',
        'vnt_ret': 'bcap_service_interfaces/Variant',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['bcap_service_interfaces', 'msg'], 'Variant'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.hresult = kwargs.get('hresult', int())
        from bcap_service_interfaces.msg import Variant
        self.vnt_ret = kwargs.get('vnt_ret', Variant())

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
        if self.hresult != other.hresult:
            return False
        if self.vnt_ret != other.vnt_ret:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def hresult(self):
        """Message field 'hresult'."""
        return self._hresult

    @hresult.setter
    def hresult(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'hresult' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'hresult' field must be an integer in [-2147483648, 2147483647]"
        self._hresult = value

    @builtins.property
    def vnt_ret(self):
        """Message field 'vnt_ret'."""
        return self._vnt_ret

    @vnt_ret.setter
    def vnt_ret(self, value):
        if __debug__:
            from bcap_service_interfaces.msg import Variant
            assert \
                isinstance(value, Variant), \
                "The 'vnt_ret' field must be a sub message of type 'Variant'"
        self._vnt_ret = value


class Metaclass_Bcap(type):
    """Metaclass of service 'Bcap'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('bcap_service_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'bcap_service_interfaces.srv.Bcap')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__bcap

            from bcap_service_interfaces.srv import _bcap
            if _bcap.Metaclass_Bcap_Request._TYPE_SUPPORT is None:
                _bcap.Metaclass_Bcap_Request.__import_type_support__()
            if _bcap.Metaclass_Bcap_Response._TYPE_SUPPORT is None:
                _bcap.Metaclass_Bcap_Response.__import_type_support__()


class Bcap(metaclass=Metaclass_Bcap):
    from bcap_service_interfaces.srv._bcap import Bcap_Request as Request
    from bcap_service_interfaces.srv._bcap import Bcap_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
