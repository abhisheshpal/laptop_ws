;; Auto-generated. Do not edit!


(when (boundp 'thorvald_2d_nav::sub_goal)
  (if (not (find-package "THORVALD_2D_NAV"))
    (make-package "THORVALD_2D_NAV"))
  (shadow 'sub_goal (find-package "THORVALD_2D_NAV")))
(unless (find-package "THORVALD_2D_NAV::SUB_GOAL")
  (make-package "THORVALD_2D_NAV::SUB_GOAL"))
(unless (find-package "THORVALD_2D_NAV::SUB_GOALREQUEST")
  (make-package "THORVALD_2D_NAV::SUB_GOALREQUEST"))
(unless (find-package "THORVALD_2D_NAV::SUB_GOALRESPONSE")
  (make-package "THORVALD_2D_NAV::SUB_GOALRESPONSE"))

(in-package "ROS")





(defclass thorvald_2d_nav::sub_goalRequest
  :super ros::object
  :slots (_counter ))

(defmethod thorvald_2d_nav::sub_goalRequest
  (:init
   (&key
    ((:counter __counter) 0)
    )
   (send-super :init)
   (setq _counter (round __counter))
   self)
  (:counter
   (&optional __counter)
   (if __counter (setq _counter __counter)) _counter)
  (:serialization-length
   ()
   (+
    ;; int64 _counter
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _counter
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _counter (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _counter) (= (length (_counter . bv)) 2)) ;; bignum
              (write-long (ash (elt (_counter . bv) 0) 0) s)
              (write-long (ash (elt (_counter . bv) 1) -1) s))
             ((and (class _counter) (= (length (_counter . bv)) 1)) ;; big1
              (write-long (elt (_counter . bv) 0) s)
              (write-long (if (>= _counter 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _counter s)(write-long (if (>= _counter 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _counter
#+(or :alpha :irix6 :x86_64)
      (setf _counter (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _counter (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
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

(defclass thorvald_2d_nav::sub_goalResponse
  :super ros::object
  :slots ())

(defmethod thorvald_2d_nav::sub_goalResponse
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass thorvald_2d_nav::sub_goal
  :super ros::object
  :slots ())

(setf (get thorvald_2d_nav::sub_goal :md5sum-) "bf8fa84d852a8768a882827724d718cf")
(setf (get thorvald_2d_nav::sub_goal :datatype-) "thorvald_2d_nav/sub_goal")
(setf (get thorvald_2d_nav::sub_goal :request) thorvald_2d_nav::sub_goalRequest)
(setf (get thorvald_2d_nav::sub_goal :response) thorvald_2d_nav::sub_goalResponse)

(defmethod thorvald_2d_nav::sub_goalRequest
  (:response () (instance thorvald_2d_nav::sub_goalResponse :init)))

(setf (get thorvald_2d_nav::sub_goalRequest :md5sum-) "bf8fa84d852a8768a882827724d718cf")
(setf (get thorvald_2d_nav::sub_goalRequest :datatype-) "thorvald_2d_nav/sub_goalRequest")
(setf (get thorvald_2d_nav::sub_goalRequest :definition-)
      "int64 counter
---


")

(setf (get thorvald_2d_nav::sub_goalResponse :md5sum-) "bf8fa84d852a8768a882827724d718cf")
(setf (get thorvald_2d_nav::sub_goalResponse :datatype-) "thorvald_2d_nav/sub_goalResponse")
(setf (get thorvald_2d_nav::sub_goalResponse :definition-)
      "int64 counter
---


")



(provide :thorvald_2d_nav/sub_goal "bf8fa84d852a8768a882827724d718cf")


