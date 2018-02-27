; Auto-generated. Do not edit!


(cl:in-package trigger_sync-msg)


;//! \htmlinclude EventStamped.msg.html

(cl:defclass <EventStamped> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (event
    :reader event
    :initarg :event
    :type trigger_sync-msg:Event
    :initform (cl:make-instance 'trigger_sync-msg:Event)))
)

(cl:defclass EventStamped (<EventStamped>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <EventStamped>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'EventStamped)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name trigger_sync-msg:<EventStamped> is deprecated: use trigger_sync-msg:EventStamped instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <EventStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader trigger_sync-msg:header-val is deprecated.  Use trigger_sync-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'event-val :lambda-list '(m))
(cl:defmethod event-val ((m <EventStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader trigger_sync-msg:event-val is deprecated.  Use trigger_sync-msg:event instead.")
  (event m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <EventStamped>) ostream)
  "Serializes a message object of type '<EventStamped>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'event) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <EventStamped>) istream)
  "Deserializes a message object of type '<EventStamped>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'event) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<EventStamped>)))
  "Returns string type for a message object of type '<EventStamped>"
  "trigger_sync/EventStamped")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'EventStamped)))
  "Returns string type for a message object of type 'EventStamped"
  "trigger_sync/EventStamped")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<EventStamped>)))
  "Returns md5sum for a message object of type '<EventStamped>"
  "34a32cadbe3dd53056306b476370bc22")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'EventStamped)))
  "Returns md5sum for a message object of type 'EventStamped"
  "34a32cadbe3dd53056306b476370bc22")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<EventStamped>)))
  "Returns full string definition for message of type '<EventStamped>"
  (cl:format cl:nil "Header header~%Event  event~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: trigger_sync/Event~%string  event_name~%time    local_request_time~%string  device_clock_id~%time    device_time~%string  local_clock_id~%time    local_receive_time~%time    corrected_local_time~%float64 clock_skew~%duration    min_transport_delay~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'EventStamped)))
  "Returns full string definition for message of type 'EventStamped"
  (cl:format cl:nil "Header header~%Event  event~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: trigger_sync/Event~%string  event_name~%time    local_request_time~%string  device_clock_id~%time    device_time~%string  local_clock_id~%time    local_receive_time~%time    corrected_local_time~%float64 clock_skew~%duration    min_transport_delay~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <EventStamped>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'event))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <EventStamped>))
  "Converts a ROS message object to a list"
  (cl:list 'EventStamped
    (cl:cons ':header (header msg))
    (cl:cons ':event (event msg))
))
