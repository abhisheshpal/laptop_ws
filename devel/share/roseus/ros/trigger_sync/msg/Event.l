;; Auto-generated. Do not edit!


(when (boundp 'trigger_sync::Event)
  (if (not (find-package "TRIGGER_SYNC"))
    (make-package "TRIGGER_SYNC"))
  (shadow 'Event (find-package "TRIGGER_SYNC")))
(unless (find-package "TRIGGER_SYNC::EVENT")
  (make-package "TRIGGER_SYNC::EVENT"))

(in-package "ROS")
;;//! \htmlinclude Event.msg.html


(defclass trigger_sync::Event
  :super ros::object
  :slots (_event_name _local_request_time _device_clock_id _device_time _local_clock_id _local_receive_time _corrected_local_time _clock_skew _min_transport_delay ))

(defmethod trigger_sync::Event
  (:init
   (&key
    ((:event_name __event_name) "")
    ((:local_request_time __local_request_time) (instance ros::time :init))
    ((:device_clock_id __device_clock_id) "")
    ((:device_time __device_time) (instance ros::time :init))
    ((:local_clock_id __local_clock_id) "")
    ((:local_receive_time __local_receive_time) (instance ros::time :init))
    ((:corrected_local_time __corrected_local_time) (instance ros::time :init))
    ((:clock_skew __clock_skew) 0.0)
    ((:min_transport_delay __min_transport_delay) (instance ros::time :init))
    )
   (send-super :init)
   (setq _event_name (string __event_name))
   (setq _local_request_time __local_request_time)
   (setq _device_clock_id (string __device_clock_id))
   (setq _device_time __device_time)
   (setq _local_clock_id (string __local_clock_id))
   (setq _local_receive_time __local_receive_time)
   (setq _corrected_local_time __corrected_local_time)
   (setq _clock_skew (float __clock_skew))
   (setq _min_transport_delay __min_transport_delay)
   self)
  (:event_name
   (&optional __event_name)
   (if __event_name (setq _event_name __event_name)) _event_name)
  (:local_request_time
   (&optional __local_request_time)
   (if __local_request_time (setq _local_request_time __local_request_time)) _local_request_time)
  (:device_clock_id
   (&optional __device_clock_id)
   (if __device_clock_id (setq _device_clock_id __device_clock_id)) _device_clock_id)
  (:device_time
   (&optional __device_time)
   (if __device_time (setq _device_time __device_time)) _device_time)
  (:local_clock_id
   (&optional __local_clock_id)
   (if __local_clock_id (setq _local_clock_id __local_clock_id)) _local_clock_id)
  (:local_receive_time
   (&optional __local_receive_time)
   (if __local_receive_time (setq _local_receive_time __local_receive_time)) _local_receive_time)
  (:corrected_local_time
   (&optional __corrected_local_time)
   (if __corrected_local_time (setq _corrected_local_time __corrected_local_time)) _corrected_local_time)
  (:clock_skew
   (&optional __clock_skew)
   (if __clock_skew (setq _clock_skew __clock_skew)) _clock_skew)
  (:min_transport_delay
   (&optional __min_transport_delay)
   (if __min_transport_delay (setq _min_transport_delay __min_transport_delay)) _min_transport_delay)
  (:serialization-length
   ()
   (+
    ;; string _event_name
    4 (length _event_name)
    ;; time _local_request_time
    8
    ;; string _device_clock_id
    4 (length _device_clock_id)
    ;; time _device_time
    8
    ;; string _local_clock_id
    4 (length _local_clock_id)
    ;; time _local_receive_time
    8
    ;; time _corrected_local_time
    8
    ;; float64 _clock_skew
    8
    ;; duration _min_transport_delay
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _event_name
       (write-long (length _event_name) s) (princ _event_name s)
     ;; time _local_request_time
       (write-long (send _local_request_time :sec) s) (write-long (send _local_request_time :nsec) s)
     ;; string _device_clock_id
       (write-long (length _device_clock_id) s) (princ _device_clock_id s)
     ;; time _device_time
       (write-long (send _device_time :sec) s) (write-long (send _device_time :nsec) s)
     ;; string _local_clock_id
       (write-long (length _local_clock_id) s) (princ _local_clock_id s)
     ;; time _local_receive_time
       (write-long (send _local_receive_time :sec) s) (write-long (send _local_receive_time :nsec) s)
     ;; time _corrected_local_time
       (write-long (send _corrected_local_time :sec) s) (write-long (send _corrected_local_time :nsec) s)
     ;; float64 _clock_skew
       (sys::poke _clock_skew (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; duration _min_transport_delay
       (write-long (send _min_transport_delay :sec) s) (write-long (send _min_transport_delay :nsec) s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _event_name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _event_name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; time _local_request_time
     (send _local_request_time :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _local_request_time :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; string _device_clock_id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _device_clock_id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; time _device_time
     (send _device_time :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _device_time :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; string _local_clock_id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _local_clock_id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; time _local_receive_time
     (send _local_receive_time :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _local_receive_time :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; time _corrected_local_time
     (send _corrected_local_time :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _corrected_local_time :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _clock_skew
     (setq _clock_skew (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; duration _min_transport_delay
     (send _min_transport_delay :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _min_transport_delay :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get trigger_sync::Event :md5sum-) "7bb8e8fc0642e70a90d298e9b70ba013")
(setf (get trigger_sync::Event :datatype-) "trigger_sync/Event")
(setf (get trigger_sync::Event :definition-)
      "string  event_name
time    local_request_time
string  device_clock_id
time    device_time
string  local_clock_id
time    local_receive_time
time    corrected_local_time
float64 clock_skew
duration    min_transport_delay

")



(provide :trigger_sync/Event "7bb8e8fc0642e70a90d298e9b70ba013")


