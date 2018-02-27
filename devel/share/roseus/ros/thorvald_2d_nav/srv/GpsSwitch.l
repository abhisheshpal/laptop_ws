;; Auto-generated. Do not edit!


(when (boundp 'thorvald_2d_nav::GpsSwitch)
  (if (not (find-package "THORVALD_2D_NAV"))
    (make-package "THORVALD_2D_NAV"))
  (shadow 'GpsSwitch (find-package "THORVALD_2D_NAV")))
(unless (find-package "THORVALD_2D_NAV::GPSSWITCH")
  (make-package "THORVALD_2D_NAV::GPSSWITCH"))
(unless (find-package "THORVALD_2D_NAV::GPSSWITCHREQUEST")
  (make-package "THORVALD_2D_NAV::GPSSWITCHREQUEST"))
(unless (find-package "THORVALD_2D_NAV::GPSSWITCHRESPONSE")
  (make-package "THORVALD_2D_NAV::GPSSWITCHRESPONSE"))

(in-package "ROS")





(defclass thorvald_2d_nav::GpsSwitchRequest
  :super ros::object
  :slots (_a ))

(defmethod thorvald_2d_nav::GpsSwitchRequest
  (:init
   (&key
    ((:a __a) 0)
    )
   (send-super :init)
   (setq _a (round __a))
   self)
  (:a
   (&optional __a)
   (if __a (setq _a __a)) _a)
  (:serialization-length
   ()
   (+
    ;; int64 _a
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _a
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _a (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _a) (= (length (_a . bv)) 2)) ;; bignum
              (write-long (ash (elt (_a . bv) 0) 0) s)
              (write-long (ash (elt (_a . bv) 1) -1) s))
             ((and (class _a) (= (length (_a . bv)) 1)) ;; big1
              (write-long (elt (_a . bv) 0) s)
              (write-long (if (>= _a 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _a s)(write-long (if (>= _a 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _a
#+(or :alpha :irix6 :x86_64)
      (setf _a (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _a (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
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

(defclass thorvald_2d_nav::GpsSwitchResponse
  :super ros::object
  :slots (_gps_switch ))

(defmethod thorvald_2d_nav::GpsSwitchResponse
  (:init
   (&key
    ((:gps_switch __gps_switch) 0)
    )
   (send-super :init)
   (setq _gps_switch (round __gps_switch))
   self)
  (:gps_switch
   (&optional __gps_switch)
   (if __gps_switch (setq _gps_switch __gps_switch)) _gps_switch)
  (:serialization-length
   ()
   (+
    ;; int64 _gps_switch
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _gps_switch
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _gps_switch (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _gps_switch) (= (length (_gps_switch . bv)) 2)) ;; bignum
              (write-long (ash (elt (_gps_switch . bv) 0) 0) s)
              (write-long (ash (elt (_gps_switch . bv) 1) -1) s))
             ((and (class _gps_switch) (= (length (_gps_switch . bv)) 1)) ;; big1
              (write-long (elt (_gps_switch . bv) 0) s)
              (write-long (if (>= _gps_switch 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _gps_switch s)(write-long (if (>= _gps_switch 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _gps_switch
#+(or :alpha :irix6 :x86_64)
      (setf _gps_switch (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _gps_switch (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
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

(defclass thorvald_2d_nav::GpsSwitch
  :super ros::object
  :slots ())

(setf (get thorvald_2d_nav::GpsSwitch :md5sum-) "2e3c0c75e8b47d5932d7a16eda636d7b")
(setf (get thorvald_2d_nav::GpsSwitch :datatype-) "thorvald_2d_nav/GpsSwitch")
(setf (get thorvald_2d_nav::GpsSwitch :request) thorvald_2d_nav::GpsSwitchRequest)
(setf (get thorvald_2d_nav::GpsSwitch :response) thorvald_2d_nav::GpsSwitchResponse)

(defmethod thorvald_2d_nav::GpsSwitchRequest
  (:response () (instance thorvald_2d_nav::GpsSwitchResponse :init)))

(setf (get thorvald_2d_nav::GpsSwitchRequest :md5sum-) "2e3c0c75e8b47d5932d7a16eda636d7b")
(setf (get thorvald_2d_nav::GpsSwitchRequest :datatype-) "thorvald_2d_nav/GpsSwitchRequest")
(setf (get thorvald_2d_nav::GpsSwitchRequest :definition-)
      "int64 a
---
int64 gps_switch

")

(setf (get thorvald_2d_nav::GpsSwitchResponse :md5sum-) "2e3c0c75e8b47d5932d7a16eda636d7b")
(setf (get thorvald_2d_nav::GpsSwitchResponse :datatype-) "thorvald_2d_nav/GpsSwitchResponse")
(setf (get thorvald_2d_nav::GpsSwitchResponse :definition-)
      "int64 a
---
int64 gps_switch

")



(provide :thorvald_2d_nav/GpsSwitch "2e3c0c75e8b47d5932d7a16eda636d7b")


