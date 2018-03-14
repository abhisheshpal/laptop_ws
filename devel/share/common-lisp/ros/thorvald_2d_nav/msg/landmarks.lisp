; Auto-generated. Do not edit!


(cl:in-package thorvald_2d_nav-msg)


;//! \htmlinclude landmarks.msg.html

(cl:defclass <landmarks> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (pt_1
    :reader pt_1
    :initarg :pt_1
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (pt_2
    :reader pt_2
    :initarg :pt_2
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (pt_3
    :reader pt_3
    :initarg :pt_3
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (pt_4
    :reader pt_4
    :initarg :pt_4
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (pt_5
    :reader pt_5
    :initarg :pt_5
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (pt_6
    :reader pt_6
    :initarg :pt_6
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (landmark_check
    :reader landmark_check
    :initarg :landmark_check
    :type cl:integer
    :initform 0))
)

(cl:defclass landmarks (<landmarks>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <landmarks>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'landmarks)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name thorvald_2d_nav-msg:<landmarks> is deprecated: use thorvald_2d_nav-msg:landmarks instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <landmarks>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader thorvald_2d_nav-msg:header-val is deprecated.  Use thorvald_2d_nav-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'pt_1-val :lambda-list '(m))
(cl:defmethod pt_1-val ((m <landmarks>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader thorvald_2d_nav-msg:pt_1-val is deprecated.  Use thorvald_2d_nav-msg:pt_1 instead.")
  (pt_1 m))

(cl:ensure-generic-function 'pt_2-val :lambda-list '(m))
(cl:defmethod pt_2-val ((m <landmarks>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader thorvald_2d_nav-msg:pt_2-val is deprecated.  Use thorvald_2d_nav-msg:pt_2 instead.")
  (pt_2 m))

(cl:ensure-generic-function 'pt_3-val :lambda-list '(m))
(cl:defmethod pt_3-val ((m <landmarks>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader thorvald_2d_nav-msg:pt_3-val is deprecated.  Use thorvald_2d_nav-msg:pt_3 instead.")
  (pt_3 m))

(cl:ensure-generic-function 'pt_4-val :lambda-list '(m))
(cl:defmethod pt_4-val ((m <landmarks>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader thorvald_2d_nav-msg:pt_4-val is deprecated.  Use thorvald_2d_nav-msg:pt_4 instead.")
  (pt_4 m))

(cl:ensure-generic-function 'pt_5-val :lambda-list '(m))
(cl:defmethod pt_5-val ((m <landmarks>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader thorvald_2d_nav-msg:pt_5-val is deprecated.  Use thorvald_2d_nav-msg:pt_5 instead.")
  (pt_5 m))

(cl:ensure-generic-function 'pt_6-val :lambda-list '(m))
(cl:defmethod pt_6-val ((m <landmarks>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader thorvald_2d_nav-msg:pt_6-val is deprecated.  Use thorvald_2d_nav-msg:pt_6 instead.")
  (pt_6 m))

(cl:ensure-generic-function 'landmark_check-val :lambda-list '(m))
(cl:defmethod landmark_check-val ((m <landmarks>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader thorvald_2d_nav-msg:landmark_check-val is deprecated.  Use thorvald_2d_nav-msg:landmark_check instead.")
  (landmark_check m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <landmarks>) ostream)
  "Serializes a message object of type '<landmarks>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pt_1) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pt_2) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pt_3) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pt_4) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pt_5) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pt_6) ostream)
  (cl:let* ((signed (cl:slot-value msg 'landmark_check)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <landmarks>) istream)
  "Deserializes a message object of type '<landmarks>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pt_1) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pt_2) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pt_3) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pt_4) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pt_5) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pt_6) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'landmark_check) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<landmarks>)))
  "Returns string type for a message object of type '<landmarks>"
  "thorvald_2d_nav/landmarks")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'landmarks)))
  "Returns string type for a message object of type 'landmarks"
  "thorvald_2d_nav/landmarks")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<landmarks>)))
  "Returns md5sum for a message object of type '<landmarks>"
  "af209cef473c1468511c6d5084a11b46")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'landmarks)))
  "Returns md5sum for a message object of type 'landmarks"
  "af209cef473c1468511c6d5084a11b46")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<landmarks>)))
  "Returns full string definition for message of type '<landmarks>"
  (cl:format cl:nil "Header header~%geometry_msgs/Point pt_1~%geometry_msgs/Point pt_2~%geometry_msgs/Point pt_3~%geometry_msgs/Point pt_4~%geometry_msgs/Point pt_5~%geometry_msgs/Point pt_6~%int64 landmark_check~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'landmarks)))
  "Returns full string definition for message of type 'landmarks"
  (cl:format cl:nil "Header header~%geometry_msgs/Point pt_1~%geometry_msgs/Point pt_2~%geometry_msgs/Point pt_3~%geometry_msgs/Point pt_4~%geometry_msgs/Point pt_5~%geometry_msgs/Point pt_6~%int64 landmark_check~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <landmarks>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pt_1))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pt_2))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pt_3))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pt_4))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pt_5))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pt_6))
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <landmarks>))
  "Converts a ROS message object to a list"
  (cl:list 'landmarks
    (cl:cons ':header (header msg))
    (cl:cons ':pt_1 (pt_1 msg))
    (cl:cons ':pt_2 (pt_2 msg))
    (cl:cons ':pt_3 (pt_3 msg))
    (cl:cons ':pt_4 (pt_4 msg))
    (cl:cons ':pt_5 (pt_5 msg))
    (cl:cons ':pt_6 (pt_6 msg))
    (cl:cons ':landmark_check (landmark_check msg))
))
