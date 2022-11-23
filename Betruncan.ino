#include "function_code_parse.h"
#include "states.h"

struct can_frame can_msg;
MCP2515 mcp(10);
uint8_t new_state;

void setup() {
  new_state = STATE_INITIALISING;
  state_initialising();
}

void loop() {
  go_to_new_state(new_state);
}
