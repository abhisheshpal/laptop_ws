;; Auto-generated. Do not edit!


(when (boundp 'thorvald_2d_nav::landmarks)
  (if (not (find-package "THORVALD_2D_NAV"))
    (make-package "THORVALD_2D_NAV"))
  (shadow 'landmarks (find-package "THORVALD_2D_NAV")))
(unless (find-package "THORVALD_2D_NAV::LANDMARKS")
  (make-package "THORVALD_2D_NAV::LANDMARKS"))

(in-package "ROS")
;;//! \htmlinclude landmarks.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass thorvald_2d_nav::landmarks
  :super ros::object
  :slots (_header _pt_1 _pt_2 _pt_3 _pt_4 ))

(defmethod thorvald_2d_nav::landmarks
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:pt_1 __pt_1) (instance geometry_msgs::Point :init))
    ((:pt_2 __pt_2) (instance geometry_msgs::Point :init))
    ((:pt_3 __pt_3) (instance geometry_msgs::Point :init))
    ((:pt_4 __pt_4) (instance geometry_msgs::Point :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _pt_1 __pt_1)
   (setq _pt_2 __pt_2)
   (setq _pt_3 __pt_3)
   (setq _pt_4 __pt_4)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:pt_1
   (&rest __pt_1)
   (if (keywordp (car __pt_1))
       (send* _pt_1 __pt_1)
     (progn
       (if __pt_1 (setq _pt_1 (car __pt_1)))
       _pt_1)))
  (:pt_2
   (&rest __pt_2)
   (if (keywordp (car __pt_2))
       (send* _pt_2 __pt_2)
     (progn
       (if __pt_2 (setq _pt_2 (car __pt_2)))
       _pt_2)))
  (:pt_3
   (&rest __pt_3)
   (if (keywordp (car __pt_3))
       (send* _pt_3 __pt_3)
     (progn
       (if __pt_3 (setq _pt_3 (car __pt_3)))
       _pt_3)))
  (:pt_4
   (&rest __pt_4)
   (if (keywordp (car __pt_4))
       (send* _pt_4 __pt_4)
     (progn
       (if __pt_4 (setq _pt_4 (car __pt_4)))
       _pt_4)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; geometry_msgs/Point _pt_1
    (send _pt_1 :serialization-length)
    ;; geometry_msgs/Point _pt_2
    (send _pt_2 :serialization-length)
    ;; geometry_msgs/Point _pt_3
    (send _pt_3 :serialization-length)
    ;; geometry_msgs/Point _pt_4
    (send _pt_4 :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; geometry_msgs/Point _pt_1
       (send _pt_1 :serialize s)
     ;; geometry_msgs/Point _pt_2
       (send _pt_2 :serialize s)
     ;; geometry_msgs/Point _pt_3
       (send _pt_3 :serialize s)
     ;; geometry_msgs/Point _pt_4
       (send _pt_4 :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; geometry_msgs/Point _pt_1
     (send _pt_1 :deserialize buf ptr-) (incf ptr- (send _pt_1 :serialization-length))
   ;; geometry_msgs/Point _pt_2
     (send _pt_2 :deserialize buf ptr-) (incf ptr- (send _pt_2 :serialization-length))
   ;; geometry_msgs/Point _pt_3
     (send _pt_3 :deserialize buf ptr-) (incf ptr- (send _pt_3 :serialization-length))
   ;; geometry_msgs/Point _pt_4
     (send _pt_4 :deserialize buf ptr-) (incf ptr- (send _pt_4 :serialization-length))
   ;;
   self)
  )

(setf (get thorvald_2d_nav::landmarks :md5sum-) "8eef2551dccb95eccba1954107457f32")
(setf (get thorvald_2d_nav::landmarks :datatype-) "thorvald_2d_nav/landmarks")
(setf (get thorvald_2d_nav::landmarks :definition-)
      "Header header
geometry_msgs/Point pt_1
geometry_msgs/Point pt_2
geometry_msgs/Point pt_3
geometry_msgs/Point pt_4


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
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :thorvald_2d_nav/landmarks "8eef2551dccb95eccba1954107457f32")


