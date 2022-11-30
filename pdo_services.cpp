#include "pdo_services.h"

void pdo_service_one(const struct can_frame can_msg) {
  analogWrite(PIN_ANALOGOUT, can_msg.data[0]);
}

void pdo_service_two(struct can_frame can_msg) {
  uint16_t value = analogRead(PIN_ANALOGIN);
  for (uint8_t i=0; i<8; i++) {
    can_msg.data[i] = 0x00; 
  }
  can_msg.data[0] = value;
  can_msg.data[1] = (value >> 8);
  can_msg.can_id = FUNCTION_CODE_PDO_TWOTX_START;
  can_msg.can_dlc = 0x08;
  while (mcp.sendMessage(&can_msg) != MCP2515::ERROR_OK);
  Serial.println(value);
}

void parse_pdo_service(struct can_frame can_msg) {
  if ((can_msg.can_id >= FUNCTION_CODE_PDO_ONERX_START) && (can_msg.can_id <= FUNCTION_CODE_PDO_ONERX_END)) {
    pdo_service_one(can_msg);
  }
  else if ((can_msg.can_id >= FUNCTION_CODE_PDO_TWORX_START) && (can_msg.can_id <= FUNCTION_CODE_PDO_TWORX_END)) {
    pdo_service_two(can_msg);
  }
}
