// Generated by gencpp from file thorvald_2d_nav/landmarks.msg
// DO NOT EDIT!


#ifndef THORVALD_2D_NAV_MESSAGE_LANDMARKS_H
#define THORVALD_2D_NAV_MESSAGE_LANDMARKS_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Point.h>

namespace thorvald_2d_nav
{
template <class ContainerAllocator>
struct landmarks_
{
  typedef landmarks_<ContainerAllocator> Type;

  landmarks_()
    : header()
    , pt_1()
    , pt_2()
    , pt_3()
    , pt_4()  {
    }
  landmarks_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , pt_1(_alloc)
    , pt_2(_alloc)
    , pt_3(_alloc)
    , pt_4(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::geometry_msgs::Point_<ContainerAllocator>  _pt_1_type;
  _pt_1_type pt_1;

   typedef  ::geometry_msgs::Point_<ContainerAllocator>  _pt_2_type;
  _pt_2_type pt_2;

   typedef  ::geometry_msgs::Point_<ContainerAllocator>  _pt_3_type;
  _pt_3_type pt_3;

   typedef  ::geometry_msgs::Point_<ContainerAllocator>  _pt_4_type;
  _pt_4_type pt_4;




  typedef boost::shared_ptr< ::thorvald_2d_nav::landmarks_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::thorvald_2d_nav::landmarks_<ContainerAllocator> const> ConstPtr;

}; // struct landmarks_

typedef ::thorvald_2d_nav::landmarks_<std::allocator<void> > landmarks;

typedef boost::shared_ptr< ::thorvald_2d_nav::landmarks > landmarksPtr;
typedef boost::shared_ptr< ::thorvald_2d_nav::landmarks const> landmarksConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::thorvald_2d_nav::landmarks_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::thorvald_2d_nav::landmarks_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace thorvald_2d_nav

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'thorvald_2d_nav': ['/home/vigneshnuc/laptop_ws/src/thorvald_2d_nav/msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::thorvald_2d_nav::landmarks_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::thorvald_2d_nav::landmarks_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::thorvald_2d_nav::landmarks_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::thorvald_2d_nav::landmarks_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::thorvald_2d_nav::landmarks_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::thorvald_2d_nav::landmarks_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::thorvald_2d_nav::landmarks_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8eef2551dccb95eccba1954107457f32";
  }

  static const char* value(const ::thorvald_2d_nav::landmarks_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8eef2551dccb95ecULL;
  static const uint64_t static_value2 = 0xcba1954107457f32ULL;
};

template<class ContainerAllocator>
struct DataType< ::thorvald_2d_nav::landmarks_<ContainerAllocator> >
{
  static const char* value()
  {
    return "thorvald_2d_nav/landmarks";
  }

  static const char* value(const ::thorvald_2d_nav::landmarks_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::thorvald_2d_nav::landmarks_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
geometry_msgs/Point pt_1\n\
geometry_msgs/Point pt_2\n\
geometry_msgs/Point pt_3\n\
geometry_msgs/Point pt_4\n\
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
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
";
  }

  static const char* value(const ::thorvald_2d_nav::landmarks_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::thorvald_2d_nav::landmarks_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.pt_1);
      stream.next(m.pt_2);
      stream.next(m.pt_3);
      stream.next(m.pt_4);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct landmarks_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::thorvald_2d_nav::landmarks_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::thorvald_2d_nav::landmarks_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "pt_1: ";
    s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.pt_1);
    s << indent << "pt_2: ";
    s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.pt_2);
    s << indent << "pt_3: ";
    s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.pt_3);
    s << indent << "pt_4: ";
    s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.pt_4);
  }
};

} // namespace message_operations
} // namespace ros

#endif // THORVALD_2D_NAV_MESSAGE_LANDMARKS_H
