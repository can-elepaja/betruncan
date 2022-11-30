#ifndef SDO_SERVICES_H
#define SDO_SERVICES_H

#include <stdint.h>
#include <can.h>

extern struct can_frame can_msg;

void parse_sdo_service(struct can_frame can_msg);
uint8_t parse_ccs_scs(const uint8_t hex);
void sdo_abort(const uint8_t data[]);
void sdo_upload_segment(const uint8_t data[]);
void sdo_upload_initiate(const uint8_t data[]);
void sdo_download_segment(const uint8_t data[]);
void sdo_download_initiate(const uint8_t data[]);
void initiate_normal_transfer(const uint32_t size_of_transfer);

#define CCS_DOWNINIT 0x01
#define CCS_DOWNSEG 0x00
#define CCS_UPINIT 0x02
#define CCS_UPSEG 0x03
#define CCS_ABORT 0x04

#endif
