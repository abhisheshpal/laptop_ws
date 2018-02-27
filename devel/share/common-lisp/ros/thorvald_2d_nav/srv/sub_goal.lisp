; Auto-generated. Do not edit!


(cl:in-package thorvald_2d_nav-srv)


;//! \htmlinclude sub_goal-request.msg.html

(cl:defclass <sub_goal-request> (roslisp-msg-protocol:ros-message)
  ((counter
    :reader counter
    :initarg :counter
    :type cl:integer
    :initform 0))
)

(cl:defclass sub_goal-request (<sub_goal-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <sub_goal-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'sub_goal-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name thorvald_2d_nav-srv:<sub_goal-request> is deprecated: use thorvald_2d_nav-srv:sub_goal-request instead.")))

(cl:ensure-generic-function 'counter-val :lambda-list '(m))
(cl:defmethod counter-val ((m <sub_goal-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader thorvald_2d_nav-srv:counter-val is deprecated.  Use thorvald_2d_nav-srv:counter instead.")
  (counter m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <sub_goal-request>) ostream)
  "Serializes a message object of type '<sub_goal-request>"
  (cl:let* ((signed (cl:slot-value msg 'counter)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <sub_goal-request>) istream)
  "Deserializes a message object of type '<sub_goal-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'counter) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<sub_goal-request>)))
  "Returns string type for a service object of type '<sub_goal-request>"
  "thorvald_2d_nav/sub_goalRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'sub_goal-request)))
  "Returns string type for a service object of type 'sub_goal-request"
  "thorvald_2d_nav/sub_goalRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<sub_goal-request>)))
  "Returns md5sum for a message object of type '<sub_goal-request>"
  "bf8fa84d852a8768a882827724d718cf")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'sub_goal-request)))
  "Returns md5sum for a message object of type 'sub_goal-request"
  "bf8fa84d852a8768a882827724d718cf")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<sub_goal-request>)))
  "Returns full string definition for message of type '<sub_goal-request>"
  (cl:format cl:nil "int64 counter~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'sub_goal-request)))
  "Returns full string definition for message of type 'sub_goal-request"
  (cl:format cl:nil "int64 counter~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <sub_goal-request>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <sub_goal-request>))
  "Converts a ROS message object to a list"
  (cl:list 'sub_goal-request
    (cl:cons ':counter (counter msg))
))
;//! \htmlinclude sub_goal-response.msg.html

(cl:defclass <sub_goal-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass sub_goal-response (<sub_goal-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <sub_goal-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'sub_goal-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name thorvald_2d_nav-srv:<sub_goal-response> is deprecated: use thorvald_2d_nav-srv:sub_goal-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <sub_goal-response>) ostream)
  "Serializes a message object of type '<sub_goal-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <sub_goal-response>) istream)
  "Deserializes a message object of type '<sub_goal-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<sub_goal-response>)))
  "Returns string type for a service object of type '<sub_goal-response>"
  "thorvald_2d_nav/sub_goalResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'sub_goal-response)))
  "Returns string type for a service object of type 'sub_goal-response"
  "thorvald_2d_nav/sub_goalResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<sub_goal-response>)))
  "Returns md5sum for a message object of type '<sub_goal-response>"
  "bf8fa84d852a8768a882827724d718cf")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'sub_goal-response)))
  "Returns md5sum for a message object of type 'sub_goal-response"
  "bf8fa84d852a8768a882827724d718cf")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<sub_goal-response>)))
  "Returns full string definition for message of type '<sub_goal-response>"
  (cl:format cl:nil "~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'sub_goal-response)))
  "Returns full string definition for message of type 'sub_goal-response"
  (cl:format cl:nil "~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <sub_goal-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <sub_goal-response>))
  "Converts a ROS message object to a list"
  (cl:list 'sub_goal-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'sub_goal)))
  'sub_goal-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'sub_goal)))
  'sub_goal-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'sub_goal)))
  "Returns string type for a service object of type '<sub_goal>"
  "thorvald_2d_nav/sub_goal")