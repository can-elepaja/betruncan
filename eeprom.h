#ifndef EEPROM_HEADER
#define EEPROM_HEADER

struct block multiplexer_to_block(const uint32_t multiplexer);
void conf_eeprom();
bool EEPROM_status();
void EEPROM_write_byte(const uint16_t addr, const uint8_t data);
void EEPROM_write(const uint32_t multiplexer, const uint32_t data);
uint8_t EEPROM_read_byte(const uint16_t addr);
uint32_t EEPROM_read(const uint32_t multiplexer);


extern uint32_t device_id;

#define INS_EEPROM_READ 0x03 //Read data from memory array beginning at selected address
#define INS_EEPROM_WRITE 0x02 //Write data to memory array beginning at selected address
#define INS_EEPROM_WRDI 0x04 //Reset the write enable latch (disable write operations)
#define INS_EEPROM_WREN 0x06 //Set the write enable latch (enable write operations)
#define INS_EEPROM_RDSR 0x05 //Read STATUS register
#define INS_EEPROM_WRSR 0x01 //Write STATUS register

#define EEPROM_CS 4

#define MASK_NODEID 0x7F

#define DEFAULT_DEVICETYPE 0x000C0191
#define DEFAULT_TPDO_HIGHEST_SUBINDEX 0x00000005
#define DEFAULT_RPDO_HIGHEST_SUBINDEX 0x00000002
#define DEFAULT_ERROR_REGISTER 0x00000000

#endif
