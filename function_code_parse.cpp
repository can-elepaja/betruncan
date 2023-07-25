#include "function_code_parse.h"
#include "sdo_services.h"
#include "pdo_services.h"
#include "eeprom.h"

struct pdo_transmissiontype_statuses {
  uint8_t status_array[PDO_COUNT];
} pdo_transmissiontype_statuses;

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

// TBD wtf does this do???
void update_pdo_transmissiontype_statuses() {
  pdo_transmissiontype_statuses.status_array[0] = EEPROM_read(MULTIPLEXER_ANALOGOUT_TRANSMISSIONTYPE);
  pdo_transmissiontype_statuses.status_array[1] = EEPROM_read(MULTIPLEXER_ANALOGIN_TRANSMISSIONTYPE);
}

void execute_sync(can_frame can_msg) {
  if (pdo_transmissiontype_statuses.status_array[1] < MAX_OF_SYNC_LIST) {
    analog_in(can_msg);
  }
  return;
}

uint8_t parse_function_code(struct can_frame can_msg) {
  switch (can_msg.can_id) {
    case(FUNCTION_CODE_SYNC):
      if ((new_state == STATE_OPERATIONAL) || (new_state == STATE_PREOPERATIONAL)) {
        execute_sync(can_msg);
        return 0x01;
      }
    case(FUNCTION_CODE_NMT):
      execute_nmt(can_msg.data[0]);
      return 0x02;
  }
  if ((can_msg.can_id >= FUNCTION_CODE_SDO_START) && (can_msg.can_id <= FUNCTION_CODE_SDO_END)) {
    if ((new_state == STATE_OPERATIONAL) || (new_state == STATE_PREOPERATIONAL)) {
      //parse_sdo_service(can_msg);
      return 0x03;
    }
  }
  if ((can_msg.can_id >= FUNCTION_CODE_PDO_START) && (can_msg.can_id <= FUNCTION_CODE_PDO_END)) {
    if ((new_state == STATE_OPERATIONAL)) {
      parse_pdo_service(can_msg);
      return 0x04;
    }
  }
  return 0x00;
}
