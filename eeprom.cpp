#include <SPI.h>
#include "eeprom.h"

typedef struct block{
  const uint16_t addr;
  const uint8_t subs;
};

block device_type =                  { .addr = 0x0000, .subs = 1 }; //content: u32
block error_register =               { .addr = 0x0004, .subs = 1 }; //content: u32
block cob_id_sync_message =          { .addr = 0x0016, .subs = 1 }; //content: u32
block communication_cycle_perioid =  { .addr = 0x001A, .subs = 1 }; //content: u32
block producer_heartbeat_time =      { .addr = 0x001E, .subs = 1 }; //content: u32
block sdo_server_parameters =        { .addr = 0x0022, .subs = 9 }; //content: Highest_subindex(u32), COB-ID_client_to_server(rx)(u32), COB-ID_server_to_client(tx)(u32)
block sdo_client_parameters =        { .addr = 0x0042, .subs = 9 }; //content: Highest_subindex(u8), COB-ID_client_to_server(rx)(u32), COB-ID_server_to_client(tx)(u32), Node-ID_SDO_server(u8)
block rpdo_communication_parameters ={ .addr = 0x0066, .subs = 9 }; //content: Highest_subindex(u8), COB-ID_used_by_RPDO(u32), Transmission_type(u8), Event-timer(u16)
block rpdo_mapping_parameters =      { .addr = 0x008A, .subs = 9 }; //content: Number_of_application_objects_in_PDO(u8), Application_objects(1-8)(8 x u32)
block tpdo_communication_parameters ={ .addr = 0x00AE, .subs = 9 }; //content: Highest_subindex_supported(u8), COB-ID_used_by_TPDO(u32), Transmission_type(u8), Inhibit_timer(u16), Event_timer(16), SYNC_start_value(u8)
block tpdo_mapping_parameters =      { .addr = 0x00D2, .subs = 9 }; //content: Number_of_application_objects_in_PDO(u8), Application_objects(1-8)(8 x u32)
block identity =                     { .addr = 0x00F6, .subs = 9 }; //content: Highest sub index(u8), Vendor-ID(u32), Product-code(u32), Revision-number(u32), Serial-number(u32)
block failure =                      { .addr = 0xFFFF, .subs = 0 }; //"Something is wrong"


block multiplexer_to_block(const uint32_t multiplexer) {
  const uint16_t address = multiplexer;
  const uint16_t node_id = (device_id & MASK_NODEID);
  if (address == 0x1000) {
    return device_type;
  }
  else if (address == 0x1001) {
    return error_register;
  }
  else if (address == 0x1005) {
    return cob_id_sync_message;
  }
  else if (address == 0x1006) {
    return communication_cycle_perioid;
  }
  else if (address == 0x1017) {
    return producer_heartbeat_time;
  }
  else if (address == 0x1018) {
    return identity;
  }
  else if (address == 0x1200 + node_id) {
    return sdo_server_parameters;
  }
  else if (address == 0x1280 + node_id) {
    return sdo_client_parameters;
  }
  else if (address == 0x1401) {
    return rpdo_communication_parameters;
  }
  else if (address == 0x1601) {
    return rpdo_mapping_parameters;
  }
  else if (address == 0x1801) {
    return tpdo_communication_parameters;
  }
  else if (address == 0x1A01) {
    return tpdo_mapping_parameters;
  }
  else {
    return failure;
  }
}


void conf_eeprom() {
  EEPROM_write(0x1000, DEFAULT_DEVICETYPE);
  EEPROM_write(0x1401, DEFAULT_TPDO_HIGHEST_SUBINDEX);
  EEPROM_write(0x1801, DEFAULT_RPDO_HIGHEST_SUBINDEX);
  EEPROM_write(0x1001, DEFAULT_ERROR_REGISTER);
}


bool EEPROM_status() {
  digitalWrite(EEPROM_CS, LOW);
  SPI.transfer(INS_EEPROM_WRDI);
  digitalWrite(EEPROM_CS, HIGH);
  digitalWrite(EEPROM_CS, LOW);
  SPI.transfer(INS_EEPROM_RDSR);
  byte E_status = SPI.transfer(0x00);
  if((0x01 == E_status) | (0x03 == E_status)) {
    digitalWrite(EEPROM_CS, HIGH);
    return false;
  }
  else {
    digitalWrite(EEPROM_CS, HIGH);
    return true;
  }
}


//DONT CALL THIS FUNCTION!!! USE EERPOM_write INSTEAD!!!
void EEPROM_write_byte(const uint16_t addr, const uint8_t data) {
  digitalWrite(EEPROM_CS, LOW);
  SPI.transfer(INS_EEPROM_WREN);
  digitalWrite(EEPROM_CS, HIGH);
  digitalWrite(EEPROM_CS, LOW);
  SPI.transfer(INS_EEPROM_WRITE);
  SPI.transfer16(addr);
  SPI.transfer(data);
  digitalWrite(EEPROM_CS, HIGH);
}


void EEPROM_write(const uint32_t multiplexer, const uint32_t data) {
  const struct block ablock = multiplexer_to_block(multiplexer);
  if (ablock.subs == 0) {
    return;
  }
  uint16_t subindex = 4*(multiplexer >> 16);
  for (uint8_t i = 0; i<4; i++){
    EEPROM_write_byte(ablock.addr + subindex + i, data >> (8*i));
    while (!EEPROM_status());
  }
  digitalWrite(EEPROM_CS, LOW);
  SPI.transfer(INS_EEPROM_WRDI);
  digitalWrite(EEPROM_CS, HIGH);
}


//DONT CALL THIS FUNCTION!!! USE EERPOM_read INSTEAD!!!
uint8_t EEPROM_read_byte(const uint16_t addr) {
  digitalWrite(EEPROM_CS, LOW);
  SPI.transfer(INS_EEPROM_READ);
  SPI.transfer16(addr);
  byte data = SPI.transfer(0x00);
  digitalWrite(EEPROM_CS, HIGH);
  return data;
}


uint32_t EEPROM_read(const uint32_t multiplexer) {
  const struct block ablock = multiplexer_to_block(multiplexer);
  if (ablock.subs == 0) {
    return;
  }
  uint32_t data;
  uint32_t bitshifter;
  uint16_t subindex = 4*(multiplexer >> 16);
  for (uint8_t i = 0; i<4; i++){
    bitshifter = EEPROM_read_byte(ablock.addr + subindex + i);
    data += (bitshifter << (8*i));
  }
  return data;
}
