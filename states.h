#ifndef STATES_H
#define STATES_H

#include <stdint.h>
#include <mcp2515.h>
#include "function_code_parse.h"

extern uint8_t new_state;
extern MCP2515 mcp;
extern struct can_frame can_msg;
extern uint32_t device_id;

void state_initialising();
void state_resetapplication();
void state_resetcommunication();
void state_preoperational();
void state_stopped();
void state_operational();
void go_to_new_state(const uint8_t new_state);
void read_canbus();

#define PIN_ANALOGOUT 3
#define PIN_ANALOGIN A0

#define DEFAULT_CANID 0x00000000

#endif
