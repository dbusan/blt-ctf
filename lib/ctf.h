#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "highscores.h"

#define DEFAULT_CALLSIGN_HOLDER "VK6BSP"

typedef struct CTFGame_t {
  bool is_running;
  HighscoreEntry holder;
  Highscores _table;
} CTFGame;

typedef enum CTFError_t {
  all_ok,
  err_ctf_not_running,
  err_callsign_invalid,
} CTFError;

void CTFGame_Init(CTFGame *self);

void CTFGame_Start(CTFGame *self);

void CTFGame_Stop(CTFGame *self);

CTFError CTFGame_Capture(CTFGame *self, const char *capturer_callsign, uint8_t len);

void CTFGame_Highscores(CTFGame *self);

/**
 * @brief call once every second.
 *
 * @param self
 */
CTFError CTFGame_Tick(CTFGame *self);

#ifdef __cplusplus
}
#endif
