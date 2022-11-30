#include "sdo_services.h"
#include "eeprom.h"
/*
struct {
  uint32_t byte_size;
  uint8_t iteration;
  uint8_t addr[3];
} segment_ctrl;

void initiate_normal_transfer(const uint32_t size_of_transfer) {
  segment_ctrl.byte_size = size_of_transfer;
  segment_ctrl.iteration = 0;
  segment_ctrl.addr;
}

void sdo_download_initiate(const uint8_t data[]) {
  const uint8_t n = ((data[0] & 0x0C) >> 2);
  const uint8_t e = (data[0] & 0x02);
  const uint8_t s = (data[0] & 0x01);
  const uint8_t m[3] = {data[1],data[2],data[3]};
  if ((e==0x00) && (s==0x01)) {
    //do normal transfer
    uint32_t download_size = (data[7] << 24) + (data[6] << 16) + (data[5] << 8) + data[4];
    initiate_normal_transfer(download_size);
  }
  else if (e==0x01) {
    //do expedited transfer
    uint8_t N = n;
    if (s==0x00) {
      N = 0x00;
    }
    uint8_t d[4-N];
    for (uint8_t i=0; i<(4-N); i++) {
      d[i] = data[i];
    }
    EEPROM_write(m, d);
  }
  uint8_t response[8] = {0x60, data[1], data[2], data[3], 0x00, 0x00, 0x00, 0x00};
  send_can_msg(response);
}

void sdo_download_segment(const uint8_t data[]) {
  const uint8_t n = ((data[0] & 0x0E) >> 1);
  const uint8_t m[3] = segment_ctrl.addr;
  uint8_t d[4-n];
    for (uint8_t i=0; i<(4-n); i++) {
      d[i] = data[i];
    }
  EEPROM_write(m, d);
}

void sdo_upload_initiate(const uint8_t data[]) {
  
}

void sdo_upload_segment(const uint8_t data[]) {
  
}

void sdo_abort(const uint8_t data[]) {
  
}

uint8_t parse_ccs_scs(const uint8_t hex) {
  if ((hex & 0xE0) == 0x00)  {
    return 0x00
  }
  else if ((hex & 0xE0) == 0x20) {
    return 0x01
  }
  else if ((hex & 0xE0) == 0x40) {
    return 0x02
  }
  else if ((hex & 0xE0) == 0x60) {
    return 0x03
  }
  else if ((hex & 0xE0) == 0x80) {
    return 0x04
  }
  else if ((hex & 0xE0) == 0xA0) {
    return 0x05
  }
  else if ((hex & 0xE0) == 0xC0) {
    return 0x06
  }
  else:
    return 0x07
}

void parse_sdo_service(struct can_frame can_msg) {
  uint8_t ccs = parse_ccs_scs(can_msg.data[0]);
  switch(css) {
    case (CCS_DOWNINIT):
      sdo_download_initiate(can_msg.data);
    case (CCS_DOWNSEG):
      sdo_download_segment(can_msg.data);
    case (CCS_UPINIT):
      sdo_upload_initiate(can_msg.data);
    case (CCS_UPSEG):
      sdo_upload_segment(can_msg.data);
    case (CCS_ABORT):
      sdo_abort(can_msg.data);
  }
}
*/
