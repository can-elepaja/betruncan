#ifndef PDO_SERVICES_H
#define PDO_SERVICES_H

#include <stdint.h>
#include <can.h>
#include <Arduino.h>
#include <mcp2515.h>
#include "states.h"

extern MCP2515 mcp;
extern struct can_frame can_msg;

void parse_pdo_service(struct can_frame can_msg);
void pdo_service_two(const struct can_frame can_msg);
void pdo_service_one(const struct can_frame can_msg);

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


#endif
