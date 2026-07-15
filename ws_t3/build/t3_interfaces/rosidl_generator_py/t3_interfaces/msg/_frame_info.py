# generated from rosidl_generator_py/resource/_idl.py.em
# with input from t3_interfaces:msg/FrameInfo.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_FrameInfo(type):
    """Metaclass of message 'FrameInfo'."""

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
            module = import_type_support('t3_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                't3_interfaces.msg.FrameInfo')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__frame_info
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__frame_info
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__frame_info
            cls._TYPE_SUPPORT = module.type_support_msg__msg__frame_info
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__frame_info

            from sensor_msgs.msg import Image
            if Image.__class__._TYPE_SUPPORT is None:
                Image.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class FrameInfo(metaclass=Metaclass_FrameInfo):
    """Message class 'FrameInfo'."""

    __slots__ = [
        '_header',
        '_frame_index',
        '_frame_url',
        '_video_name',
        '_session',
        '_ref_x',
        '_ref_y',
        '_ref_z',
        '_ref_valid',
        '_health_status',
        '_image',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'frame_index': 'int64',
        'frame_url': 'string',
        'video_name': 'string',
        'session': 'string',
        'ref_x': 'double',
        'ref_y': 'double',
        'ref_z': 'double',
        'ref_valid': 'boolean',
        'health_status': 'int8',
        'image': 'sensor_msgs/Image',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['sensor_msgs', 'msg'], 'Image'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.frame_index = kwargs.get('frame_index', int())
        self.frame_url = kwargs.get('frame_url', str())
        self.video_name = kwargs.get('video_name', str())
        self.session = kwargs.get('session', str())
        self.ref_x = kwargs.get('ref_x', float())
        self.ref_y = kwargs.get('ref_y', float())
        self.ref_z = kwargs.get('ref_z', float())
        self.ref_valid = kwargs.get('ref_valid', bool())
        self.health_status = kwargs.get('health_status', int())
        from sensor_msgs.msg import Image
        self.image = kwargs.get('image', Image())

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
        if self.header != other.header:
            return False
        if self.frame_index != other.frame_index:
            return False
        if self.frame_url != other.frame_url:
            return False
        if self.video_name != other.video_name:
            return False
        if self.session != other.session:
            return False
        if self.ref_x != other.ref_x:
            return False
        if self.ref_y != other.ref_y:
            return False
        if self.ref_z != other.ref_z:
            return False
        if self.ref_valid != other.ref_valid:
            return False
        if self.health_status != other.health_status:
            return False
        if self.image != other.image:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def frame_index(self):
        """Message field 'frame_index'."""
        return self._frame_index

    @frame_index.setter
    def frame_index(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'frame_index' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'frame_index' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._frame_index = value

    @builtins.property
    def frame_url(self):
        """Message field 'frame_url'."""
        return self._frame_url

    @frame_url.setter
    def frame_url(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'frame_url' field must be of type 'str'"
        self._frame_url = value

    @builtins.property
    def video_name(self):
        """Message field 'video_name'."""
        return self._video_name

    @video_name.setter
    def video_name(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'video_name' field must be of type 'str'"
        self._video_name = value

    @builtins.property
    def session(self):
        """Message field 'session'."""
        return self._session

    @session.setter
    def session(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'session' field must be of type 'str'"
        self._session = value

    @builtins.property
    def ref_x(self):
        """Message field 'ref_x'."""
        return self._ref_x

    @ref_x.setter
    def ref_x(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ref_x' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'ref_x' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._ref_x = value

    @builtins.property
    def ref_y(self):
        """Message field 'ref_y'."""
        return self._ref_y

    @ref_y.setter
    def ref_y(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ref_y' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'ref_y' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._ref_y = value

    @builtins.property
    def ref_z(self):
        """Message field 'ref_z'."""
        return self._ref_z

    @ref_z.setter
    def ref_z(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ref_z' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'ref_z' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._ref_z = value

    @builtins.property
    def ref_valid(self):
        """Message field 'ref_valid'."""
        return self._ref_valid

    @ref_valid.setter
    def ref_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ref_valid' field must be of type 'bool'"
        self._ref_valid = value

    @builtins.property
    def health_status(self):
        """Message field 'health_status'."""
        return self._health_status

    @health_status.setter
    def health_status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'health_status' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'health_status' field must be an integer in [-128, 127]"
        self._health_status = value

    @builtins.property
    def image(self):
        """Message field 'image'."""
        return self._image

    @image.setter
    def image(self, value):
        if __debug__:
            from sensor_msgs.msg import Image
            assert \
                isinstance(value, Image), \
                "The 'image' field must be a sub message of type 'Image'"
        self._image = value
