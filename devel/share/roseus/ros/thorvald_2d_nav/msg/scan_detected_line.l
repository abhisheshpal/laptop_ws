;; Auto-generated. Do not edit!


(when (boundp 'thorvald_2d_nav::scan_detected_line)
  (if (not (find-package "THORVALD_2D_NAV"))
    (make-package "THORVALD_2D_NAV"))
  (shadow 'scan_detected_line (find-package "THORVALD_2D_NAV")))
(unless (find-package "THORVALD_2D_NAV::SCAN_DETECTED_LINE")
  (make-package "THORVALD_2D_NAV::SCAN_DETECTED_LINE"))

(in-package "ROS")
;;//! \htmlinclude scan_detected_line.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass thorvald_2d_nav::scan_detected_line
  :super ros::object
  :slots (_header _range _bearing ))

(defmethod thorvald_2d_nav::scan_detected_line
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:range __range) (make-array 10 :initial-element 0.0 :element-type :float))
    ((:bearing __bearing) (make-array 10 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _range __range)
   (setq _bearing __bearing)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:range
   (&optional __range)
   (if __range (setq _range __range)) _range)
  (:bearing
   (&optional __bearing)
   (if __bearing (setq _bearing __bearing)) _bearing)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float32[10] _range
    (* 4    10)
    ;; float32[10] _bearing
    (* 4    10)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float32[10] _range
     (dotimes (i 10)
       (sys::poke (elt _range i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[10] _bearing
     (dotimes (i 10)
       (sys::poke (elt _bearing i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float32[10] _range
   (dotimes (i (length _range))
     (setf (elt _range i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[10] _bearing
   (dotimes (i (length _bearing))
     (setf (elt _bearing i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;;
   self)
  )

(setf (get thorvald_2d_nav::scan_detected_line :md5sum-) "e898260d96b8c031fca2533c01815bf0")
(setf (get thorvald_2d_nav::scan_detected_line :datatype-) "thorvald_2d_nav/scan_detected_line")
(setf (get thorvald_2d_nav::scan_detected_line :definition-)
      "Header header
float32[10] range
float32[10] bearing


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

")



(provide :thorvald_2d_nav/scan_detected_line "e898260d96b8c031fca2533c01815bf0")


