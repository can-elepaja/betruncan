#include "pdo_services.h"
#include "eeprom.h"

void analog_out(const struct can_frame can_msg) {
  uint8_t value = can_msg.data[0];
  //EEPROM_write(MULTIPLEXER_ANALOGOUTPUT, value); TBD check if even needed
  if (EEPROM_read(MULTIPLEXER_ERRORREGISTER) != 0) {
    analogWrite(PIN_ANALOGOUT, 0);
    // TBD if failed do what?
  }
  else {
    analogWrite(PIN_ANALOGOUT, value);
  }
}

void analog_in(struct can_frame can_msg) {
  uint32_t value = analogRead(PIN_ANALOGIN);
  //EEPROM_write(MULTIPLEXER_ANALOGINPUT, value); TBD check if even needed
  uint16_t tpdo_canid = (0x7FF & EEPROM_read(MULTIPLEXER_TPDO));
  for (uint8_t i=0; i<8; i++) {
    can_msg.data[i] = 0x00;
  }
  can_msg.data[0] = value;
  can_msg.data[1] = (value >> 8);
  can_msg.can_id = tpdo_canid;
  can_msg.can_dlc = 0x08;
  while (mcp.sendMessage(&can_msg) != MCP2515::ERROR_OK);
}

void pdo_start(struct can_frame can_msg) {
  can_msg.data[0] = EEPROM_read(MULTIPLEXER_ANALOGOUTPUT);
  analog_out(can_msg);
}

void pdo_exit(struct can_frame can_msg) {
  can_msg.data[0] = 0x00;
  analog_out(can_msg);
}

void parse_pdo_service(struct can_frame can_msg) {
  const uint16_t node_id = (device_id & MASK_NODEID);
  const uint16_t comp_id = (can_msg.can_id & MASK_NODEID) - node_id;
  switch (comp_id){
    case (MASK_AO_COBID):
      analog_out(can_msg);
    case (MASK_AI_COBID):
      analog_in(can_msg);
  }
}
