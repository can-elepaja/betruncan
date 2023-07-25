#include "states.h"
#include "function_code_parse.h"
#include "eeprom.h"
#include "pdo_services.h"

void read_canbus() {
  MCP2515::ERROR err;
  err = mcp.readMessage(&can_msg);
  if (err == MCP2515::ERROR_OK) {
    parse_function_code(can_msg);
  }
}

void state_initialising() {
  while (new_state == STATE_INITIALISING) {
    mcp.reset();
    mcp.setBitrate(CAN_500KBPS, MCP_8MHZ);
    mcp.setNormalMode();
    conf_eeprom();
    pinMode(PIN_ANALOGOUT, OUTPUT);
    Serial.begin(9600); //DEBUG
    new_state = STATE_RESETAPPLICATION;
  }
}

void state_resetapplication() {
  while (new_state == STATE_RESETAPPLICATION) {
    new_state = STATE_RESETCOMMUNICATION;
  }
}

void state_resetcommunication() {
  while (new_state == STATE_RESETCOMMUNICATION) {
    device_id = DEFAULT_CANID;
    new_state = STATE_PREOPERATIONAL;
  }
}

void state_preoperational() {
  while (new_state == STATE_PREOPERATIONAL) {
    read_canbus();
  }
}

void state_stopped() {
  while (new_state == STATE_STOPPED) {
    read_canbus();
  }
}

void state_operational() {
  update_pdo_transmissiontype_statuses();
  pdo_start(can_msg);
  while (new_state == STATE_OPERATIONAL) {
    read_canbus();
  }
  pdo_exit(can_msg);
}


void go_to_new_state(const uint8_t new_state) {
  switch (new_state) {
    case (STATE_INITIALISING):
    state_initialising();
    return;
    case (STATE_RESETAPPLICATION):
    state_resetapplication();
    return;
    case (STATE_RESETCOMMUNICATION):
    state_resetcommunication();
    return;
    case (STATE_PREOPERATIONAL):
    state_preoperational();
    return;
    case (STATE_STOPPED):
    state_stopped();
    return;
    case (STATE_OPERATIONAL):
    state_operational();
    return;
  }
}
