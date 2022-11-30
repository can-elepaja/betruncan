#ifndef EEPROM_HEADER
#define EEPROM_HEADER

struct block multiplexer_to_block(const uint8_t mplx[]);
bool EEPROM_status();
void EEPROM_write_byte(const uint16_t addr, const uint8_t data);
void EEPROM_write(const uint8_t multiplexer[], const uint8_t data[]);
uint8_t EEPROM_read_byte(const uint16_t addr);
uint8_t *EEPROM_read(const struct block ablock);
void conf_eeprom();


#define INS_EEPROM_READ 0x03 //Read data from memory array beginning at selected address
#define INS_EEPROM_WRITE 0x02 //Write data to memory array beginning at selected address
#define INS_EEPROM_WRDI 0x04 //Reset the write enable latch (disable write operations)
#define INS_EEPROM_WREN 0x06 //Set the write enable latch (enable write operations)
#define INS_EEPROM_RDSR 0x05 //Read STATUS register
#define INS_EEPROM_WRSR 0x01 //Write STATUS register

#define EEPROM_CS 4

#endif
