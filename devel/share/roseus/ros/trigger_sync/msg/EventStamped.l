;; Auto-generated. Do not edit!


(when (boundp 'trigger_sync::EventStamped)
  (if (not (find-package "TRIGGER_SYNC"))
    (make-package "TRIGGER_SYNC"))
  (shadow 'EventStamped (find-package "TRIGGER_SYNC")))
(unless (find-package "TRIGGER_SYNC::EVENTSTAMPED")
  (make-package "TRIGGER_SYNC::EVENTSTAMPED"))

(in-package "ROS")
;;//! \htmlinclude EventStamped.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass trigger_sync::EventStamped
  :super ros::object
  :slots (_header _event ))

(defmethod trigger_sync::EventStamped
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:event __event) (instance trigger_sync::Event :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _event __event)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:event
   (&rest __event)
   (if (keywordp (car __event))
       (send* _event __event)
     (progn
       (if __event (setq _event (car __event)))
       _event)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; trigger_sync/Event _event
    (send _event :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; trigger_sync/Event _event
       (send _event :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; trigger_sync/Event _event
     (send _event :deserialize buf ptr-) (incf ptr- (send _event :serialization-length))
   ;;
   self)
  )

(setf (get trigger_sync::EventStamped :md5sum-) "34a32cadbe3dd53056306b476370bc22")
(setf (get trigger_sync::EventStamped :datatype-) "trigger_sync/EventStamped")
(setf (get trigger_sync::EventStamped :definition-)
      "Header header
Event  event

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: trigger_sync/Event
string  event_name
time    local_request_time
string  device_clock_id
time    device_time
string  local_clock_id
time    local_receive_time
time    corrected_local_time
float64 clock_skew
duration    min_transport_delay

")



(provide :trigger_sync/EventStamped "34a32cadbe3dd53056306b476370bc22")


