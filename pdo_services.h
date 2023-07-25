#ifndef PDO_SERVICES_H
#define PDO_SERVICES_H

#include <stdint.h>
#include <can.h>
#include <Arduino.h>
#include <mcp2515.h>
#include "states.h"

extern MCP2515 mcp;
extern struct can_frame can_msg;
extern uint32_t device_id;

void parse_pdo_service(struct can_frame can_msg);
void analog_in(const struct can_frame can_msg);
void analog_out(const struct can_frame can_msg);
void pdo_start(struct can_frame can_msg);
void pdo_exit(struct can_frame can_msg);

// TBD are these needed?
/*
#define FUNCTION_CODE_PDO_ONETX_START 0x181
#define FUNCTION_CODE_PDO_ONETX_END 0x1FF
#define FUNCTION_CODE_PDO_ONERX_START 0x201
#define FUNCTION_CODE_PDO_ONERX_END 0x27F

#define FUNCTION_CODE_PDO_TWOTX_START 0x281
#define FUNCTION_CODE_PDO_TWOTX_END 0x2FF
#define FUNCTION_CODE_PDO_TWORX_START 0x301
#define FUNCTION_CODE_PDO_TWORX_END 0x37F

#define FUNCTION_CODE_PDO_THREETX_START 0x381
#define FUNCTION_CODE_PDO_THREETX_END 0x3FF
#define FUNCTION_CODE_PDO_THREERX_START 0x401
#define FUNCTION_CODE_PDO_THREERX_END 0x47F

#define FUNCTION_CODE_PDO_FOURTX_START 0x481
#define FUNCTION_CODE_PDO_FOURTX_END 0x4FF
#define FUNCTION_CODE_PDO_FOURRX_START 0x501
#define FUNCTION_CODE_PDO_FOURRX_END 0x57F
*/

#define MULTIPLEXER_ERRORREGISTER 0x00100100
#define MULTIPLEXER_ANALOGINPUT 0x00640101
#define MULTIPLEXER_ANALOGOUTPUT 0x00641101
#define MULTIPLEXER_TPDO 0x00180101

#define MASK_AO_COBID 0x0300
#define MASK_AI_COBID 0x0280
#define MASK_COBID 0x0000

#endif
