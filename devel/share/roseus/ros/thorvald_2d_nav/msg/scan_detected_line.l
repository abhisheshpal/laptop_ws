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
    ((:range __range) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:bearing __bearing) (make-array 0 :initial-element 0.0 :element-type :float))
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
    ;; float64[] _range
    (* 8    (length _range)) 4
    ;; float64[] _bearing
    (* 8    (length _bearing)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64[] _range
     (write-long (length _range) s)
     (dotimes (i (length _range))
       (sys::poke (elt _range i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _bearing
     (write-long (length _bearing) s)
     (dotimes (i (length _bearing))
       (sys::poke (elt _bearing i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64[] _range
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _range (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _range i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _bearing
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _bearing (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _bearing i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get thorvald_2d_nav::scan_detected_line :md5sum-) "0e8b578cc1fe15d012aeba376c62f328")
(setf (get thorvald_2d_nav::scan_detected_line :datatype-) "thorvald_2d_nav/scan_detected_line")
(setf (get thorvald_2d_nav::scan_detected_line :definition-)
      "Header header
float64[] range
float64[] bearing


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



(provide :thorvald_2d_nav/scan_detected_line "0e8b578cc1fe15d012aeba376c62f328")


