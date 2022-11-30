#include "states.h"
#include "function_code_parse.h"
#include "eeprom.h"

void state_initialising() {
  while (new_state == STATE_INITIALISING) {
    //do initialising shit
    mcp.reset();
    mcp.setBitrate(CAN_500KBPS, MCP_8MHZ);
    mcp.setNormalMode();
    //conf_eeprom();
    pinMode(PIN_ANALOGOUT, OUTPUT);
    Serial.begin(9600); //DEBUG
    Serial.println(STATE_INITIALISING, HEX); //DEBUG
    new_state = STATE_RESETAPPLICATION;
  }
}

void state_resetapplication() {
  while (new_state == STATE_RESETAPPLICATION) {
    //Reset the application
    Serial.println(STATE_RESETAPPLICATION, HEX); //DEBUG
    new_state = STATE_RESETCOMMUNICATION;
  }
}

void state_resetcommunication() {
  while (new_state == STATE_RESETCOMMUNICATION) {
    //Reset the communication
    Serial.println(STATE_RESETCOMMUNICATION, HEX); //DEBUG
    new_state = STATE_PREOPERATIONAL;
  }
}

void state_preoperational() {
  while (new_state == STATE_PREOPERATIONAL) {
    //Be in preoperational state
    Serial.println(STATE_PREOPERATIONAL, HEX); //DEBUG
    MCP2515::ERROR err;
    err = mcp.readMessage(&can_msg);
    if (err == MCP2515::ERROR_OK) {
      parse_function_code(can_msg);
    }
  }
}

void state_stopped() {
  while (new_state == STATE_STOPPED) {
    //Be in stopped state
    Serial.println(STATE_STOPPED, HEX);
    MCP2515::ERROR err;
    err = mcp.readMessage(&can_msg);
    if (err == MCP2515::ERROR_OK) {
      parse_function_code(can_msg);
    }
  }
}

void state_operational() {
  while (new_state == STATE_OPERATIONAL) {
    //Do operational shit
    Serial.println(STATE_OPERATIONAL, HEX);
    MCP2515::ERROR err;
    err = mcp.readMessage(&can_msg);
    if (err == MCP2515::ERROR_OK) {
      parse_function_code(can_msg);
    }
  }
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
