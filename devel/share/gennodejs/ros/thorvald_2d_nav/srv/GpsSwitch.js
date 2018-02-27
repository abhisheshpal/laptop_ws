// Auto-generated. Do not edit!

// (in-package thorvald_2d_nav.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class GpsSwitchRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.a = null;
    }
    else {
      if (initObj.hasOwnProperty('a')) {
        this.a = initObj.a
      }
      else {
        this.a = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GpsSwitchRequest
    // Serialize message field [a]
    bufferOffset = _serializer.int64(obj.a, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GpsSwitchRequest
    let len;
    let data = new GpsSwitchRequest(null);
    // Deserialize message field [a]
    data.a = _deserializer.int64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'thorvald_2d_nav/GpsSwitchRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '019706110004b728d56d8baaa8e32797';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int64 a
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GpsSwitchRequest(null);
    if (msg.a !== undefined) {
      resolved.a = msg.a;
    }
    else {
      resolved.a = 0
    }

    return resolved;
    }
};

class GpsSwitchResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gps_switch = null;
    }
    else {
      if (initObj.hasOwnProperty('gps_switch')) {
        this.gps_switch = initObj.gps_switch
      }
      else {
        this.gps_switch = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GpsSwitchResponse
    // Serialize message field [gps_switch]
    bufferOffset = _serializer.int64(obj.gps_switch, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GpsSwitchResponse
    let len;
    let data = new GpsSwitchResponse(null);
    // Deserialize message field [gps_switch]
    data.gps_switch = _deserializer.int64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'thorvald_2d_nav/GpsSwitchResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ce564dae7b6601debe0ae3c386f15d19';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int64 gps_switch
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GpsSwitchResponse(null);
    if (msg.gps_switch !== undefined) {
      resolved.gps_switch = msg.gps_switch;
    }
    else {
      resolved.gps_switch = 0
    }

    return resolved;
    }
};

module.exports = {
  Request: GpsSwitchRequest,
  Response: GpsSwitchResponse,
  md5sum() { return '2e3c0c75e8b47d5932d7a16eda636d7b'; },
  datatype() { return 'thorvald_2d_nav/GpsSwitch'; }
};
