// Auto-generated. Do not edit!

// (in-package thorvald_2d_nav.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class landmarks {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.pt_1 = null;
      this.pt_2 = null;
      this.pt_3 = null;
      this.pt_4 = null;
      this.pt_5 = null;
      this.pt_6 = null;
      this.landmark_check = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('pt_1')) {
        this.pt_1 = initObj.pt_1
      }
      else {
        this.pt_1 = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('pt_2')) {
        this.pt_2 = initObj.pt_2
      }
      else {
        this.pt_2 = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('pt_3')) {
        this.pt_3 = initObj.pt_3
      }
      else {
        this.pt_3 = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('pt_4')) {
        this.pt_4 = initObj.pt_4
      }
      else {
        this.pt_4 = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('pt_5')) {
        this.pt_5 = initObj.pt_5
      }
      else {
        this.pt_5 = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('pt_6')) {
        this.pt_6 = initObj.pt_6
      }
      else {
        this.pt_6 = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('landmark_check')) {
        this.landmark_check = initObj.landmark_check
      }
      else {
        this.landmark_check = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type landmarks
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [pt_1]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.pt_1, buffer, bufferOffset);
    // Serialize message field [pt_2]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.pt_2, buffer, bufferOffset);
    // Serialize message field [pt_3]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.pt_3, buffer, bufferOffset);
    // Serialize message field [pt_4]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.pt_4, buffer, bufferOffset);
    // Serialize message field [pt_5]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.pt_5, buffer, bufferOffset);
    // Serialize message field [pt_6]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.pt_6, buffer, bufferOffset);
    // Serialize message field [landmark_check]
    bufferOffset = _serializer.int64(obj.landmark_check, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type landmarks
    let len;
    let data = new landmarks(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [pt_1]
    data.pt_1 = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [pt_2]
    data.pt_2 = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [pt_3]
    data.pt_3 = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [pt_4]
    data.pt_4 = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [pt_5]
    data.pt_5 = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [pt_6]
    data.pt_6 = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [landmark_check]
    data.landmark_check = _deserializer.int64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 152;
  }

  static datatype() {
    // Returns string type for a message object
    return 'thorvald_2d_nav/landmarks';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'af209cef473c1468511c6d5084a11b46';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    geometry_msgs/Point pt_1
    geometry_msgs/Point pt_2
    geometry_msgs/Point pt_3
    geometry_msgs/Point pt_4
    geometry_msgs/Point pt_5
    geometry_msgs/Point pt_6
    int64 landmark_check
    
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    # 0: no frame
    # 1: global frame
    string frame_id
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new landmarks(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.pt_1 !== undefined) {
      resolved.pt_1 = geometry_msgs.msg.Point.Resolve(msg.pt_1)
    }
    else {
      resolved.pt_1 = new geometry_msgs.msg.Point()
    }

    if (msg.pt_2 !== undefined) {
      resolved.pt_2 = geometry_msgs.msg.Point.Resolve(msg.pt_2)
    }
    else {
      resolved.pt_2 = new geometry_msgs.msg.Point()
    }

    if (msg.pt_3 !== undefined) {
      resolved.pt_3 = geometry_msgs.msg.Point.Resolve(msg.pt_3)
    }
    else {
      resolved.pt_3 = new geometry_msgs.msg.Point()
    }

    if (msg.pt_4 !== undefined) {
      resolved.pt_4 = geometry_msgs.msg.Point.Resolve(msg.pt_4)
    }
    else {
      resolved.pt_4 = new geometry_msgs.msg.Point()
    }

    if (msg.pt_5 !== undefined) {
      resolved.pt_5 = geometry_msgs.msg.Point.Resolve(msg.pt_5)
    }
    else {
      resolved.pt_5 = new geometry_msgs.msg.Point()
    }

    if (msg.pt_6 !== undefined) {
      resolved.pt_6 = geometry_msgs.msg.Point.Resolve(msg.pt_6)
    }
    else {
      resolved.pt_6 = new geometry_msgs.msg.Point()
    }

    if (msg.landmark_check !== undefined) {
      resolved.landmark_check = msg.landmark_check;
    }
    else {
      resolved.landmark_check = 0
    }

    return resolved;
    }
};

module.exports = landmarks;
