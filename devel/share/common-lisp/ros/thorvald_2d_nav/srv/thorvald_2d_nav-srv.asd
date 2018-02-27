
(cl:in-package :asdf)

(defsystem "thorvald_2d_nav-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "GpsSwitch" :depends-on ("_package_GpsSwitch"))
    (:file "_package_GpsSwitch" :depends-on ("_package"))
    (:file "sub_goal" :depends-on ("_package_sub_goal"))
    (:file "_package_sub_goal" :depends-on ("_package"))
  ))