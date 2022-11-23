#ifndef FUNCTION_CODE_PARSE_H
#define FUNCTION_CODE_PARSE_H

#include <stdint.h>
#include <can.h>

extern uint8_t new_state;

bool state_change_allowed(const uint8_t first_state, const uint8_t second_state);
uint8_t current_state();
void change_state(uint8_t requested_state);
void start_remote_node();
void stop_remote_node();
void go_to_preoperational();
void reset_node();
void reset_communication();
void initialize();
void execute_nmt(const uint8_t first_databyte);
void execute_sync();
uint8_t parse_function_code(const struct can_frame can_msg);

#define FUNCTION_CODE_NMT 0
#define FUNCTION_CODE_SYNC 128
#define FUNCTION_CODE_SDO_START 1409
#define FUNCTION_CODE_SDO_END 1663

#define NODE_ID_NMT_START 0x01
#define NODE_ID_NMT_STOP 0x02
#define NODE_ID_NMT_PREOP 0x80
#define NODE_ID_NMT_RESETNODE 0x81
#define NODE_ID_NMT_RESETCOM 0x82

#define STATE_OPERATIONAL 0x05
#define STATE_STOPPED 0x02
#define STATE_PREOPERATIONAL 0x7F
#define STATE_RESETAPPLICATION 0x80
#define STATE_RESETCOMMUNICATION 0x81
#define STATE_INITIALISING 0x00

#endif 
