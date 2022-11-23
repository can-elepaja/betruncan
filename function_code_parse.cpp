#include "function_code_parse.h"
#include "sdo_services.h"

bool state_change_allowed(const uint8_t first_state, const uint8_t second_state) {
  switch(first_state) {
    case (STATE_INITIALISING):
    if (second_state == STATE_RESETAPPLICATION) {
      return true;
    }
    case (STATE_RESETAPPLICATION):
    if (second_state == STATE_RESETCOMMUNICATION) {
      return true;
    }
    case (STATE_RESETCOMMUNICATION):
    if (second_state == STATE_PREOPERATIONAL) {
      return true;
    }
    case (STATE_PREOPERATIONAL):
    if (second_state == STATE_RESETAPPLICATION) {
      return true;
    }
    else if (second_state == STATE_RESETCOMMUNICATION) {
      return true; 
    }
    else if (second_state == STATE_STOPPED) {
      return true; 
    }
    else if (second_state == STATE_OPERATIONAL) {
      return true; 
    }
    case (STATE_STOPPED):
    if (second_state == STATE_RESETAPPLICATION) {
      return true;
    }
    else if (second_state == STATE_RESETCOMMUNICATION) {
      return true; 
    }
    else if (second_state == STATE_PREOPERATIONAL) {
      return true; 
    }
    else if (second_state == STATE_OPERATIONAL) {
      return true; 
    }
    case (STATE_OPERATIONAL):
    if (second_state == STATE_RESETAPPLICATION) {
      return true;
    }
    else if (second_state == STATE_RESETCOMMUNICATION) {
      return true; 
    }
    else if (second_state == STATE_PREOPERATIONAL) {
      return true; 
    }
    else if (second_state == STATE_STOPPED) {
      return true; 
    }
    default:
    return false;
  }
  return false;
}

void change_state(const uint8_t requested_state) {
  if (new_state == requested_state) {
    return;
  }
  if (state_change_allowed(new_state, requested_state)){
  new_state = requested_state;
  }
}

void start_remote_node() {
  change_state(STATE_OPERATIONAL);
}

void stop_remote_node() {
  change_state(STATE_STOPPED);
}

void go_to_preoperational() {
  change_state(STATE_PREOPERATIONAL);
}

void reset_node() {
  change_state(STATE_RESETAPPLICATION);
}

void reset_communication() {
  change_state(STATE_RESETCOMMUNICATION);
}

void initialize() {
  change_state(STATE_INITIALISING);
}

void execute_nmt(const uint8_t first_databyte) {
  switch(first_databyte){
    case (NODE_ID_NMT_START):
      start_remote_node();
      return;
    case (NODE_ID_NMT_STOP):
      stop_remote_node();
      return;
    case (NODE_ID_NMT_PREOP):
      go_to_preoperational();
      return;
    case (NODE_ID_NMT_RESETNODE):
      reset_node();
      return;
    case (NODE_ID_NMT_RESETCOM):
      reset_communication();
      return;
  }
  return;
}

void execute_sync() {
  return;
}

uint8_t parse_function_code(const struct can_frame can_msg) {
  switch (can_msg.can_id) {
    case(FUNCTION_CODE_SYNC):
    execute_sync();
    return 0x01;
    case(FUNCTION_CODE_NMT):
    execute_nmt(can_msg.data[0]);
    return 0x02;
  }
  if ((can_msg.can_id >= FUNCTION_CODE_SDO_START) && (can_msg.can_id <= FUNCTION_CODE_SDO_END)) {
    parse_sdo_service(can_msg);
    return 0x03;
  }
  return 0x00;
}
