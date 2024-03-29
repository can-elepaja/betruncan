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
uint8_t parse_function_code(struct can_frame can_msg);
void update_pdo_transmissiontype_statuses();

#define FUNCTION_CODE_NMT 0
#define FUNCTION_CODE_SYNC 0x080
#define FUNCTION_CODE_PDO_START 0x181
#define FUNCTION_CODE_PDO_END 0x57F
#define FUNCTION_CODE_SDO_START 0x581
#define FUNCTION_CODE_SDO_END 0x67F

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

#define PDO_COUNT 2
#define MULTIPLEXER_ANALOGOUT_TRANSMISSIONTYPE 0x00140102
#define MULTIPLEXER_ANALOGIN_TRANSMISSIONTYPE 0x00160102

#define MAX_OF_SYNC_LIST 0xF1

#endif 
