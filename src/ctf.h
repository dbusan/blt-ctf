#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef struct CTFGame_t {
  bool is_running;
  char captured_by[20];
  uint32_t time_held;

} CTFGame;

void CTFGame_Init(CTFGame *self);

void CTFGame_Start(CTFGame *self);

void CTFGame_Capture(CTFGame *self, const char *capturer_callsign);

void CTFGame_CurrentHolder(CTFGame *self, char *captured_by);

/**
 * @brief call once every second.
 *
 * @param self
 */
void CTFGame_Tick(CTFGame *self);

uint32_t CTFGame_GetHoldTime(CTFGame *self);

#ifdef __cplusplus
}
#endif
