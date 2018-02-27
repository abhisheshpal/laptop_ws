// Auto-generated. Do not edit!

// (in-package thorvald_2d_nav.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class scan_detected_line {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.range = null;
      this.bearing = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('range')) {
        this.range = initObj.range
      }
      else {
        this.range = new Array(10).fill(0);
      }
      if (initObj.hasOwnProperty('bearing')) {
        this.bearing = initObj.bearing
      }
      else {
        this.bearing = new Array(10).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type scan_detected_line
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Check that the constant length array field [range] has the right length
    if (obj.range.length !== 10) {
      throw new Error('Unable to serialize array field range - length must be 10')
    }
    // Serialize message field [range]
    bufferOffset = _arraySerializer.float32(obj.range, buffer, bufferOffset, 10);
    // Check that the constant length array field [bearing] has the right length
    if (obj.bearing.length !== 10) {
      throw new Error('Unable to serialize array field bearing - length must be 10')
    }
    // Serialize message field [bearing]
    bufferOffset = _arraySerializer.float32(obj.bearing, buffer, bufferOffset, 10);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type scan_detected_line
    let len;
    let data = new scan_detected_line(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [range]
    data.range = _arrayDeserializer.float32(buffer, bufferOffset, 10)
    // Deserialize message field [bearing]
    data.bearing = _arrayDeserializer.float32(buffer, bufferOffset, 10)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 80;
  }

  static datatype() {
    // Returns string type for a message object
    return 'thorvald_2d_nav/scan_detected_line';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e898260d96b8c031fca2533c01815bf0';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    float32[10] range
    float32[10] bearing
    
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new scan_detected_line(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.range !== undefined) {
      resolved.range = msg.range;
    }
    else {
      resolved.range = new Array(10).fill(0)
    }

    if (msg.bearing !== undefined) {
      resolved.bearing = msg.bearing;
    }
    else {
      resolved.bearing = new Array(10).fill(0)
    }

    return resolved;
    }
};

module.exports = scan_detected_line;
