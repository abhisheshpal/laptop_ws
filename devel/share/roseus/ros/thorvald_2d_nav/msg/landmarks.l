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
  :slots (_header _pt_1 _pt_2 _pt_3 _pt_4 _pt_5 _pt_6 _landmark_check ))

(defmethod thorvald_2d_nav::landmarks
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:pt_1 __pt_1) (instance geometry_msgs::Point :init))
    ((:pt_2 __pt_2) (instance geometry_msgs::Point :init))
    ((:pt_3 __pt_3) (instance geometry_msgs::Point :init))
    ((:pt_4 __pt_4) (instance geometry_msgs::Point :init))
    ((:pt_5 __pt_5) (instance geometry_msgs::Point :init))
    ((:pt_6 __pt_6) (instance geometry_msgs::Point :init))
    ((:landmark_check __landmark_check) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _pt_1 __pt_1)
   (setq _pt_2 __pt_2)
   (setq _pt_3 __pt_3)
   (setq _pt_4 __pt_4)
   (setq _pt_5 __pt_5)
   (setq _pt_6 __pt_6)
   (setq _landmark_check (round __landmark_check))
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
  (:pt_5
   (&rest __pt_5)
   (if (keywordp (car __pt_5))
       (send* _pt_5 __pt_5)
     (progn
       (if __pt_5 (setq _pt_5 (car __pt_5)))
       _pt_5)))
  (:pt_6
   (&rest __pt_6)
   (if (keywordp (car __pt_6))
       (send* _pt_6 __pt_6)
     (progn
       (if __pt_6 (setq _pt_6 (car __pt_6)))
       _pt_6)))
  (:landmark_check
   (&optional __landmark_check)
   (if __landmark_check (setq _landmark_check __landmark_check)) _landmark_check)
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
    ;; geometry_msgs/Point _pt_5
    (send _pt_5 :serialization-length)
    ;; geometry_msgs/Point _pt_6
    (send _pt_6 :serialization-length)
    ;; int64 _landmark_check
    8
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
     ;; geometry_msgs/Point _pt_5
       (send _pt_5 :serialize s)
     ;; geometry_msgs/Point _pt_6
       (send _pt_6 :serialize s)
     ;; int64 _landmark_check
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _landmark_check (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _landmark_check) (= (length (_landmark_check . bv)) 2)) ;; bignum
              (write-long (ash (elt (_landmark_check . bv) 0) 0) s)
              (write-long (ash (elt (_landmark_check . bv) 1) -1) s))
             ((and (class _landmark_check) (= (length (_landmark_check . bv)) 1)) ;; big1
              (write-long (elt (_landmark_check . bv) 0) s)
              (write-long (if (>= _landmark_check 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _landmark_check s)(write-long (if (>= _landmark_check 0) 0 #xffffffff) s)))
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
   ;; geometry_msgs/Point _pt_5
     (send _pt_5 :deserialize buf ptr-) (incf ptr- (send _pt_5 :serialization-length))
   ;; geometry_msgs/Point _pt_6
     (send _pt_6 :deserialize buf ptr-) (incf ptr- (send _pt_6 :serialization-length))
   ;; int64 _landmark_check
#+(or :alpha :irix6 :x86_64)
      (setf _landmark_check (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _landmark_check (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(setf (get thorvald_2d_nav::landmarks :md5sum-) "af209cef473c1468511c6d5084a11b46")
(setf (get thorvald_2d_nav::landmarks :datatype-) "thorvald_2d_nav/landmarks")
(setf (get thorvald_2d_nav::landmarks :definition-)
      "Header header
geometry_msgs/Point pt_1
geometry_msgs/Point pt_2
geometry_msgs/Point pt_3
geometry_msgs/Point pt_4
geometry_msgs/Point pt_5
geometry_msgs/Point pt_6
int64 landmark_check


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



(provide :thorvald_2d_nav/landmarks "af209cef473c1468511c6d5084a11b46")


