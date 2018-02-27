// Auto-generated. Do not edit!

// (in-package trigger_sync.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Event {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.event_name = null;
      this.local_request_time = null;
      this.device_clock_id = null;
      this.device_time = null;
      this.local_clock_id = null;
      this.local_receive_time = null;
      this.corrected_local_time = null;
      this.clock_skew = null;
      this.min_transport_delay = null;
    }
    else {
      if (initObj.hasOwnProperty('event_name')) {
        this.event_name = initObj.event_name
      }
      else {
        this.event_name = '';
      }
      if (initObj.hasOwnProperty('local_request_time')) {
        this.local_request_time = initObj.local_request_time
      }
      else {
        this.local_request_time = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('device_clock_id')) {
        this.device_clock_id = initObj.device_clock_id
      }
      else {
        this.device_clock_id = '';
      }
      if (initObj.hasOwnProperty('device_time')) {
        this.device_time = initObj.device_time
      }
      else {
        this.device_time = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('local_clock_id')) {
        this.local_clock_id = initObj.local_clock_id
      }
      else {
        this.local_clock_id = '';
      }
      if (initObj.hasOwnProperty('local_receive_time')) {
        this.local_receive_time = initObj.local_receive_time
      }
      else {
        this.local_receive_time = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('corrected_local_time')) {
        this.corrected_local_time = initObj.corrected_local_time
      }
      else {
        this.corrected_local_time = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('clock_skew')) {
        this.clock_skew = initObj.clock_skew
      }
      else {
        this.clock_skew = 0.0;
      }
      if (initObj.hasOwnProperty('min_transport_delay')) {
        this.min_transport_delay = initObj.min_transport_delay
      }
      else {
        this.min_transport_delay = {secs: 0, nsecs: 0};
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Event
    // Serialize message field [event_name]
    bufferOffset = _serializer.string(obj.event_name, buffer, bufferOffset);
    // Serialize message field [local_request_time]
    bufferOffset = _serializer.time(obj.local_request_time, buffer, bufferOffset);
    // Serialize message field [device_clock_id]
    bufferOffset = _serializer.string(obj.device_clock_id, buffer, bufferOffset);
    // Serialize message field [device_time]
    bufferOffset = _serializer.time(obj.device_time, buffer, bufferOffset);
    // Serialize message field [local_clock_id]
    bufferOffset = _serializer.string(obj.local_clock_id, buffer, bufferOffset);
    // Serialize message field [local_receive_time]
    bufferOffset = _serializer.time(obj.local_receive_time, buffer, bufferOffset);
    // Serialize message field [corrected_local_time]
    bufferOffset = _serializer.time(obj.corrected_local_time, buffer, bufferOffset);
    // Serialize message field [clock_skew]
    bufferOffset = _serializer.float64(obj.clock_skew, buffer, bufferOffset);
    // Serialize message field [min_transport_delay]
    bufferOffset = _serializer.duration(obj.min_transport_delay, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Event
    let len;
    let data = new Event(null);
    // Deserialize message field [event_name]
    data.event_name = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [local_request_time]
    data.local_request_time = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [device_clock_id]
    data.device_clock_id = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [device_time]
    data.device_time = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [local_clock_id]
    data.local_clock_id = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [local_receive_time]
    data.local_receive_time = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [corrected_local_time]
    data.corrected_local_time = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [clock_skew]
    data.clock_skew = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [min_transport_delay]
    data.min_transport_delay = _deserializer.duration(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.event_name.length;
    length += object.device_clock_id.length;
    length += object.local_clock_id.length;
    return length + 60;
  }

  static datatype() {
    // Returns string type for a message object
    return 'trigger_sync/Event';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7bb8e8fc0642e70a90d298e9b70ba013';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string  event_name
    time    local_request_time
    string  device_clock_id
    time    device_time
    string  local_clock_id
    time    local_receive_time
    time    corrected_local_time
    float64 clock_skew
    duration    min_transport_delay
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Event(null);
    if (msg.event_name !== undefined) {
      resolved.event_name = msg.event_name;
    }
    else {
      resolved.event_name = ''
    }

    if (msg.local_request_time !== undefined) {
      resolved.local_request_time = msg.local_request_time;
    }
    else {
      resolved.local_request_time = {secs: 0, nsecs: 0}
    }

    if (msg.device_clock_id !== undefined) {
      resolved.device_clock_id = msg.device_clock_id;
    }
    else {
      resolved.device_clock_id = ''
    }

    if (msg.device_time !== undefined) {
      resolved.device_time = msg.device_time;
    }
    else {
      resolved.device_time = {secs: 0, nsecs: 0}
    }

    if (msg.local_clock_id !== undefined) {
      resolved.local_clock_id = msg.local_clock_id;
    }
    else {
      resolved.local_clock_id = ''
    }

    if (msg.local_receive_time !== undefined) {
      resolved.local_receive_time = msg.local_receive_time;
    }
    else {
      resolved.local_receive_time = {secs: 0, nsecs: 0}
    }

    if (msg.corrected_local_time !== undefined) {
      resolved.corrected_local_time = msg.corrected_local_time;
    }
    else {
      resolved.corrected_local_time = {secs: 0, nsecs: 0}
    }

    if (msg.clock_skew !== undefined) {
      resolved.clock_skew = msg.clock_skew;
    }
    else {
      resolved.clock_skew = 0.0
    }

    if (msg.min_transport_delay !== undefined) {
      resolved.min_transport_delay = msg.min_transport_delay;
    }
    else {
      resolved.min_transport_delay = {secs: 0, nsecs: 0}
    }

    return resolved;
    }
};

module.exports = Event;
