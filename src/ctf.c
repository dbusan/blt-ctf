#ifdef __cplusplus
extern "C" {
#endif

#include "ctf.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static void CTFGame_ResetTime(CTFGame *self) {
  self->holder.time = 0;
}

void CTFGame_Init(CTFGame *self) {
  self->is_running = false;
  for (uint8_t i = 0; i < sizeof(self->holder.name) / sizeof(char); i++) {
    self->holder.name[i] = 0x00;
  }
  self->holder.capture_uid = kUninitialisedUID;
  Highscores_Init(&(self->_table));

  CTFGame_ResetTime(self);
}

void CTFGame_Start(CTFGame *self) {
  self->is_running = true;
  CTFGame_Capture(self, DEFAULT_CALLSIGN_HOLDER);
}

void CTFGame_Stop(CTFGame *self) {
  CTFGame_Init(self);
}

static void IncrementUid(CTFGame *self) {
  self->holder.capture_uid++;
}

CTFError CTFGame_Capture(CTFGame *self, const char *capturer_callsign) {
  if (!(self->is_running)) {
    return err_ctf_not_running;
  }

  // potentially unsafe: set callsign name
  strncpy(self->holder.name, capturer_callsign, sizeof(self->holder.name) / sizeof(char));
  // reset hold time
  CTFGame_ResetTime(self);
  // increment uid
  IncrementUid(self);

  Highscores_HandleEntryAndSort(&(self->_table), &(self->holder));
  return all_ok;
}

void CTFGame_Highscores(CTFGame *self) {
  Highscores_Print(&(self->_table));
}

CTFError CTFGame_Tick(CTFGame *self) {
  if (!self->is_running) {
    return err_ctf_not_running;
  }

  self->holder.time++;
  Highscores_HandleEntryAndSort(&(self->_table), &(self->holder));
  return all_ok;
}

#ifdef __cplusplus
}
#endif
