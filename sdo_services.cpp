#include "sdo_services.h"

void sdo_download_initiate(const uint8_t data[]) {
  uint8_t
}

void sdo_download_segment(const uint8_t data[]) {
  
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

void parse_sdo_service(const struct can_frame can_msg) {
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
