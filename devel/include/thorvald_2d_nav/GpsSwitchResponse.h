// Generated by gencpp from file thorvald_2d_nav/GpsSwitchResponse.msg
// DO NOT EDIT!


#ifndef THORVALD_2D_NAV_MESSAGE_GPSSWITCHRESPONSE_H
#define THORVALD_2D_NAV_MESSAGE_GPSSWITCHRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace thorvald_2d_nav
{
template <class ContainerAllocator>
struct GpsSwitchResponse_
{
  typedef GpsSwitchResponse_<ContainerAllocator> Type;

  GpsSwitchResponse_()
    : gps_switch(0)  {
    }
  GpsSwitchResponse_(const ContainerAllocator& _alloc)
    : gps_switch(0)  {
  (void)_alloc;
    }



   typedef int64_t _gps_switch_type;
  _gps_switch_type gps_switch;





  typedef boost::shared_ptr< ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator> const> ConstPtr;

}; // struct GpsSwitchResponse_

typedef ::thorvald_2d_nav::GpsSwitchResponse_<std::allocator<void> > GpsSwitchResponse;

typedef boost::shared_ptr< ::thorvald_2d_nav::GpsSwitchResponse > GpsSwitchResponsePtr;
typedef boost::shared_ptr< ::thorvald_2d_nav::GpsSwitchResponse const> GpsSwitchResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace thorvald_2d_nav

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'thorvald_2d_nav': ['/home/vigneshnuc/laptop_ws/src/thorvald_2d_nav/msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'nav_msgs': ['/opt/ros/kinetic/share/nav_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ce564dae7b6601debe0ae3c386f15d19";
  }

  static const char* value(const ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xce564dae7b6601deULL;
  static const uint64_t static_value2 = 0xbe0ae3c386f15d19ULL;
};

template<class ContainerAllocator>
struct DataType< ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "thorvald_2d_nav/GpsSwitchResponse";
  }

  static const char* value(const ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int64 gps_switch\n\
\n\
";
  }

  static const char* value(const ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.gps_switch);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GpsSwitchResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::thorvald_2d_nav::GpsSwitchResponse_<ContainerAllocator>& v)
  {
    s << indent << "gps_switch: ";
    Printer<int64_t>::stream(s, indent + "  ", v.gps_switch);
  }
};

} // namespace message_operations
} // namespace ros

#endif // THORVALD_2D_NAV_MESSAGE_GPSSWITCHRESPONSE_H
