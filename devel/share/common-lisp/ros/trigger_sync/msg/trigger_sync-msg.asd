
(cl:in-package :asdf)

(defsystem "trigger_sync-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Event" :depends-on ("_package_Event"))
    (:file "_package_Event" :depends-on ("_package"))
    (:file "EventStamped" :depends-on ("_package_EventStamped"))
    (:file "_package_EventStamped" :depends-on ("_package"))
  ))