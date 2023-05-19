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
  for (uint8_t i = 0; i < kMaxCallsignLength; i++) {
    self->holder.name[i] = 0x00;
  }
  self->holder.capture_uid = kUninitialisedUID;
  Highscores_Init(&(self->_table));

  CTFGame_ResetTime(self);
}

void CTFGame_Start(CTFGame *self) {
  self->is_running = true;
  CTFGame_Capture(self, DEFAULT_CALLSIGN_HOLDER, (sizeof(DEFAULT_CALLSIGN_HOLDER) / sizeof(char)));
}

void CTFGame_Stop(CTFGame *self) {
  CTFGame_Init(self);
}

static void IncrementUid(CTFGame *self) {
  self->holder.capture_uid++;
}

/**
 * @brief Validates input for a max length of 8 characters, only alphanumeric
 *
 * @param capturer_callsign
 * @return CTFError
 */
static CTFError ValidateInput(const char *capturer_callsign, uint8_t len) {
  static const uint8_t kMinLength = 3;
  static const uint8_t kMaxLength = kMaxCallsignLength;

  CTFError err = all_ok;
  uint8_t currentNrChars = 0;

  if (len == 0) {
    return err_callsign_invalid;
  }

  if (len > kMaxLength) {
    // silently trim callsigns that are too long
    len = kMaxLength;
  }

  for (uint8_t i = 0; i < len; i++) {
    char c = capturer_callsign[i];
    if (currentNrChars > 0) {
      // stop if null character found
      if (c == 0x00) {
        break;
      }
    }

    if ((c >= '0' && c <= '9') || (c >= '@' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
      currentNrChars++;
    } else {
      err = err_callsign_invalid;
    }

    // printf("%d %c\n", currentNrChars, c);
  }

  if (currentNrChars < kMinLength) {
    err = err_callsign_invalid;
  }

  return err;
}

CTFError CTFGame_Capture(CTFGame *self, const char *capturer_callsign, uint8_t len) {
  CTFError err = all_ok;
  if (!(self->is_running)) {
    return err_ctf_not_running;
  }

  err = ValidateInput(capturer_callsign, len);
  if (err != all_ok) {
    return err;
  }

  // potentially unsafe: set callsign name
  strncpy(self->holder.name, capturer_callsign, sizeof(self->holder.name) / sizeof(char));
  // reset hold time
  CTFGame_ResetTime(self);
  // increment uid
  IncrementUid(self);

  Highscores_HandleEntryAndSort(&(self->_table), &(self->holder));
  return err;
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
