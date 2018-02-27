; Auto-generated. Do not edit!


(cl:in-package thorvald_2d_nav-srv)


;//! \htmlinclude GpsSwitch-request.msg.html

(cl:defclass <GpsSwitch-request> (roslisp-msg-protocol:ros-message)
  ((a
    :reader a
    :initarg :a
    :type cl:integer
    :initform 0))
)

(cl:defclass GpsSwitch-request (<GpsSwitch-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GpsSwitch-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GpsSwitch-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name thorvald_2d_nav-srv:<GpsSwitch-request> is deprecated: use thorvald_2d_nav-srv:GpsSwitch-request instead.")))

(cl:ensure-generic-function 'a-val :lambda-list '(m))
(cl:defmethod a-val ((m <GpsSwitch-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader thorvald_2d_nav-srv:a-val is deprecated.  Use thorvald_2d_nav-srv:a instead.")
  (a m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GpsSwitch-request>) ostream)
  "Serializes a message object of type '<GpsSwitch-request>"
  (cl:let* ((signed (cl:slot-value msg 'a)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GpsSwitch-request>) istream)
  "Deserializes a message object of type '<GpsSwitch-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'a) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GpsSwitch-request>)))
  "Returns string type for a service object of type '<GpsSwitch-request>"
  "thorvald_2d_nav/GpsSwitchRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GpsSwitch-request)))
  "Returns string type for a service object of type 'GpsSwitch-request"
  "thorvald_2d_nav/GpsSwitchRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GpsSwitch-request>)))
  "Returns md5sum for a message object of type '<GpsSwitch-request>"
  "2e3c0c75e8b47d5932d7a16eda636d7b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GpsSwitch-request)))
  "Returns md5sum for a message object of type 'GpsSwitch-request"
  "2e3c0c75e8b47d5932d7a16eda636d7b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GpsSwitch-request>)))
  "Returns full string definition for message of type '<GpsSwitch-request>"
  (cl:format cl:nil "int64 a~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GpsSwitch-request)))
  "Returns full string definition for message of type 'GpsSwitch-request"
  (cl:format cl:nil "int64 a~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GpsSwitch-request>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GpsSwitch-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GpsSwitch-request
    (cl:cons ':a (a msg))
))
;//! \htmlinclude GpsSwitch-response.msg.html

(cl:defclass <GpsSwitch-response> (roslisp-msg-protocol:ros-message)
  ((gps_switch
    :reader gps_switch
    :initarg :gps_switch
    :type cl:integer
    :initform 0))
)

(cl:defclass GpsSwitch-response (<GpsSwitch-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GpsSwitch-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GpsSwitch-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name thorvald_2d_nav-srv:<GpsSwitch-response> is deprecated: use thorvald_2d_nav-srv:GpsSwitch-response instead.")))

(cl:ensure-generic-function 'gps_switch-val :lambda-list '(m))
(cl:defmethod gps_switch-val ((m <GpsSwitch-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader thorvald_2d_nav-srv:gps_switch-val is deprecated.  Use thorvald_2d_nav-srv:gps_switch instead.")
  (gps_switch m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GpsSwitch-response>) ostream)
  "Serializes a message object of type '<GpsSwitch-response>"
  (cl:let* ((signed (cl:slot-value msg 'gps_switch)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GpsSwitch-response>) istream)
  "Deserializes a message object of type '<GpsSwitch-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'gps_switch) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GpsSwitch-response>)))
  "Returns string type for a service object of type '<GpsSwitch-response>"
  "thorvald_2d_nav/GpsSwitchResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GpsSwitch-response)))
  "Returns string type for a service object of type 'GpsSwitch-response"
  "thorvald_2d_nav/GpsSwitchResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GpsSwitch-response>)))
  "Returns md5sum for a message object of type '<GpsSwitch-response>"
  "2e3c0c75e8b47d5932d7a16eda636d7b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GpsSwitch-response)))
  "Returns md5sum for a message object of type 'GpsSwitch-response"
  "2e3c0c75e8b47d5932d7a16eda636d7b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GpsSwitch-response>)))
  "Returns full string definition for message of type '<GpsSwitch-response>"
  (cl:format cl:nil "int64 gps_switch~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GpsSwitch-response)))
  "Returns full string definition for message of type 'GpsSwitch-response"
  (cl:format cl:nil "int64 gps_switch~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GpsSwitch-response>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GpsSwitch-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GpsSwitch-response
    (cl:cons ':gps_switch (gps_switch msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GpsSwitch)))
  'GpsSwitch-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GpsSwitch)))
  'GpsSwitch-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GpsSwitch)))
  "Returns string type for a service object of type '<GpsSwitch>"
  "thorvald_2d_nav/GpsSwitch")