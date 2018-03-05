// Generated by gencpp from file thorvald_2d_nav/scan_detected_line.msg
// DO NOT EDIT!


#ifndef THORVALD_2D_NAV_MESSAGE_SCAN_DETECTED_LINE_H
#define THORVALD_2D_NAV_MESSAGE_SCAN_DETECTED_LINE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace thorvald_2d_nav
{
template <class ContainerAllocator>
struct scan_detected_line_
{
  typedef scan_detected_line_<ContainerAllocator> Type;

  scan_detected_line_()
    : header()
    , range()
    , bearing()  {
      range.assign(0.0);

      bearing.assign(0.0);
  }
  scan_detected_line_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , range()
    , bearing()  {
  (void)_alloc;
      range.assign(0.0);

      bearing.assign(0.0);
  }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef boost::array<float, 10>  _range_type;
  _range_type range;

   typedef boost::array<float, 10>  _bearing_type;
  _bearing_type bearing;




  typedef boost::shared_ptr< ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator> const> ConstPtr;

}; // struct scan_detected_line_

typedef ::thorvald_2d_nav::scan_detected_line_<std::allocator<void> > scan_detected_line;

typedef boost::shared_ptr< ::thorvald_2d_nav::scan_detected_line > scan_detected_linePtr;
typedef boost::shared_ptr< ::thorvald_2d_nav::scan_detected_line const> scan_detected_lineConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace thorvald_2d_nav

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'thorvald_2d_nav': ['/home/vignesh/laptop_ws/src/thorvald_2d_nav/msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e898260d96b8c031fca2533c01815bf0";
  }

  static const char* value(const ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe898260d96b8c031ULL;
  static const uint64_t static_value2 = 0xfca2533c01815bf0ULL;
};

template<class ContainerAllocator>
struct DataType< ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator> >
{
  static const char* value()
  {
    return "thorvald_2d_nav/scan_detected_line";
  }

  static const char* value(const ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
float32[10] range\n\
float32[10] bearing\n\
\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.range);
      stream.next(m.bearing);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct scan_detected_line_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::thorvald_2d_nav::scan_detected_line_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "range[]" << std::endl;
    for (size_t i = 0; i < v.range.size(); ++i)
    {
      s << indent << "  range[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.range[i]);
    }
    s << indent << "bearing[]" << std::endl;
    for (size_t i = 0; i < v.bearing.size(); ++i)
    {
      s << indent << "  bearing[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.bearing[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // THORVALD_2D_NAV_MESSAGE_SCAN_DETECTED_LINE_H
