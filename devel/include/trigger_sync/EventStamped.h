// Generated by gencpp from file trigger_sync/EventStamped.msg
// DO NOT EDIT!


#ifndef TRIGGER_SYNC_MESSAGE_EVENTSTAMPED_H
#define TRIGGER_SYNC_MESSAGE_EVENTSTAMPED_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <trigger_sync/Event.h>

namespace trigger_sync
{
template <class ContainerAllocator>
struct EventStamped_
{
  typedef EventStamped_<ContainerAllocator> Type;

  EventStamped_()
    : header()
    , event()  {
    }
  EventStamped_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , event(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::trigger_sync::Event_<ContainerAllocator>  _event_type;
  _event_type event;




  typedef boost::shared_ptr< ::trigger_sync::EventStamped_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::trigger_sync::EventStamped_<ContainerAllocator> const> ConstPtr;

}; // struct EventStamped_

typedef ::trigger_sync::EventStamped_<std::allocator<void> > EventStamped;

typedef boost::shared_ptr< ::trigger_sync::EventStamped > EventStampedPtr;
typedef boost::shared_ptr< ::trigger_sync::EventStamped const> EventStampedConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::trigger_sync::EventStamped_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::trigger_sync::EventStamped_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace trigger_sync

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'trigger_sync': ['/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::trigger_sync::EventStamped_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::trigger_sync::EventStamped_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::trigger_sync::EventStamped_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::trigger_sync::EventStamped_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::trigger_sync::EventStamped_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::trigger_sync::EventStamped_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::trigger_sync::EventStamped_<ContainerAllocator> >
{
  static const char* value()
  {
    return "34a32cadbe3dd53056306b476370bc22";
  }

  static const char* value(const ::trigger_sync::EventStamped_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x34a32cadbe3dd530ULL;
  static const uint64_t static_value2 = 0x56306b476370bc22ULL;
};

template<class ContainerAllocator>
struct DataType< ::trigger_sync::EventStamped_<ContainerAllocator> >
{
  static const char* value()
  {
    return "trigger_sync/EventStamped";
  }

  static const char* value(const ::trigger_sync::EventStamped_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::trigger_sync::EventStamped_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
Event  event\n\
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
MSG: trigger_sync/Event\n\
string  event_name\n\
time    local_request_time\n\
string  device_clock_id\n\
time    device_time\n\
string  local_clock_id\n\
time    local_receive_time\n\
time    corrected_local_time\n\
float64 clock_skew\n\
duration    min_transport_delay\n\
";
  }

  static const char* value(const ::trigger_sync::EventStamped_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::trigger_sync::EventStamped_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.event);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct EventStamped_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::trigger_sync::EventStamped_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::trigger_sync::EventStamped_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "event: ";
    s << std::endl;
    Printer< ::trigger_sync::Event_<ContainerAllocator> >::stream(s, indent + "  ", v.event);
  }
};

} // namespace message_operations
} // namespace ros

#endif // TRIGGER_SYNC_MESSAGE_EVENTSTAMPED_H
