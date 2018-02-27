; Auto-generated. Do not edit!


(cl:in-package thorvald_2d_nav-msg)


;//! \htmlinclude scan_detected_line.msg.html

(cl:defclass <scan_detected_line> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (range
    :reader range
    :initarg :range
    :type (cl:vector cl:float)
   :initform (cl:make-array 10 :element-type 'cl:float :initial-element 0.0))
   (bearing
    :reader bearing
    :initarg :bearing
    :type (cl:vector cl:float)
   :initform (cl:make-array 10 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass scan_detected_line (<scan_detected_line>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <scan_detected_line>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'scan_detected_line)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name thorvald_2d_nav-msg:<scan_detected_line> is deprecated: use thorvald_2d_nav-msg:scan_detected_line instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <scan_detected_line>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader thorvald_2d_nav-msg:header-val is deprecated.  Use thorvald_2d_nav-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'range-val :lambda-list '(m))
(cl:defmethod range-val ((m <scan_detected_line>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader thorvald_2d_nav-msg:range-val is deprecated.  Use thorvald_2d_nav-msg:range instead.")
  (range m))

(cl:ensure-generic-function 'bearing-val :lambda-list '(m))
(cl:defmethod bearing-val ((m <scan_detected_line>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader thorvald_2d_nav-msg:bearing-val is deprecated.  Use thorvald_2d_nav-msg:bearing instead.")
  (bearing m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <scan_detected_line>) ostream)
  "Serializes a message object of type '<scan_detected_line>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'range))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'bearing))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <scan_detected_line>) istream)
  "Deserializes a message object of type '<scan_detected_line>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'range) (cl:make-array 10))
  (cl:let ((vals (cl:slot-value msg 'range)))
    (cl:dotimes (i 10)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'bearing) (cl:make-array 10))
  (cl:let ((vals (cl:slot-value msg 'bearing)))
    (cl:dotimes (i 10)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<scan_detected_line>)))
  "Returns string type for a message object of type '<scan_detected_line>"
  "thorvald_2d_nav/scan_detected_line")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'scan_detected_line)))
  "Returns string type for a message object of type 'scan_detected_line"
  "thorvald_2d_nav/scan_detected_line")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<scan_detected_line>)))
  "Returns md5sum for a message object of type '<scan_detected_line>"
  "e898260d96b8c031fca2533c01815bf0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'scan_detected_line)))
  "Returns md5sum for a message object of type 'scan_detected_line"
  "e898260d96b8c031fca2533c01815bf0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<scan_detected_line>)))
  "Returns full string definition for message of type '<scan_detected_line>"
  (cl:format cl:nil "Header header~%float32[10] range~%float32[10] bearing~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'scan_detected_line)))
  "Returns full string definition for message of type 'scan_detected_line"
  (cl:format cl:nil "Header header~%float32[10] range~%float32[10] bearing~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <scan_detected_line>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'range) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'bearing) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <scan_detected_line>))
  "Converts a ROS message object to a list"
  (cl:list 'scan_detected_line
    (cl:cons ':header (header msg))
    (cl:cons ':range (range msg))
    (cl:cons ':bearing (bearing msg))
))
