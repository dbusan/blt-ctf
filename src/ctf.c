#ifdef __cplusplus
extern "C" {
#endif

#include "ctf.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

void CTFGame_Init(CTFGame *self) {
  self->is_running = false;
  for (uint8_t i = 0; i < sizeof(self->captured_by) / sizeof(char); i++) {
    self->captured_by[i] = 0x00;
  }
  self->time_held = 0;
}

void CTFGame_Start(CTFGame *self) {
  self->is_running = true;
}

void CTFGame_Capture(CTFGame *self, const char *capturer_callsign) {
  strncpy(self->captured_by, capturer_callsign, sizeof(self->captured_by) / sizeof(char));
}

void CTFGame_CurrentHolder(CTFGame *self, char *captured_by) {
  // unsafe: ensure captured by has enough capacity to store callsign
  memcpy(captured_by, self->captured_by, sizeof(self->captured_by) / sizeof(char));
}

void CTFGame_Tick(CTFGame *self) {
  self->time_held++;
}

uint32_t CTFGame_GetHoldTime(CTFGame *self) {
  return self->time_held;
}

#ifdef __cplusplus
}
#endif
