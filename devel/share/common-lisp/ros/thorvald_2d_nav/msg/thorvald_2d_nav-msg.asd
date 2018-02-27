
(cl:in-package :asdf)

(defsystem "thorvald_2d_nav-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "landmarks" :depends-on ("_package_landmarks"))
    (:file "_package_landmarks" :depends-on ("_package"))
    (:file "scan_detected_line" :depends-on ("_package_scan_detected_line"))
    (:file "_package_scan_detected_line" :depends-on ("_package"))
  ))