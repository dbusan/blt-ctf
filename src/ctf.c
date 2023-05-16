#ifdef __cplusplus
extern "C" {
#endif

#include "ctf.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static void
CTFGame_ResetTime(CTFGame *self) {
  self->time_held = 0;
}

void CTFGame_Init(CTFGame *self) {
  self->is_running = false;
  for (uint8_t i = 0; i < sizeof(self->captured_by) / sizeof(char); i++) {
    self->captured_by[i] = 0x00;
  }
  CTFGame_ResetTime(self);
}

void CTFGame_Start(CTFGame *self) {
  self->is_running = true;
  CTFGame_Capture(self, DEFAULT_CALLSIGN_HOLDER);
}

void CTFGame_Stop(CTFGame *self) {
  CTFGame_Init(self);
}

CTFError CTFGame_Capture(CTFGame *self, const char *capturer_callsign) {
  if (!(self->is_running)) {
    return err_ctf_not_running;
  }

  // potentially unsafe:
  strncpy(self->captured_by, capturer_callsign, sizeof(self->captured_by) / sizeof(char));
  // reset time
  CTFGame_ResetTime(self);
  return all_ok;
}

void CTFGame_CurrentHolder(CTFGame *self, char *captured_by) {
  // unsafe: ensure captured by has enough capacity to store callsign
  memcpy(captured_by, self->captured_by, sizeof(self->captured_by) / sizeof(char));
}

CTFError CTFGame_Tick(CTFGame *self) {
  if (!self->is_running) {
    return err_ctf_not_running;
  }

  self->time_held++;
  return all_ok;
}

#ifdef __cplusplus
}
#endif
