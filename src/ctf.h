#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#define DEFAULT_CALLSIGN_HOLDER "VK6BSP"

typedef struct CTFGame_t {
  bool is_running;
  char captured_by[20];
  uint32_t time_held;

} CTFGame;

typedef enum CTFError_t {
  all_ok,
  err_ctf_not_running,
} CTFError;

void CTFGame_Init(CTFGame *self);

void CTFGame_Start(CTFGame *self);

void CTFGame_Stop(CTFGame *self);

CTFError CTFGame_Capture(CTFGame *self, const char *capturer_callsign);

void CTFGame_CurrentHolder(CTFGame *self, char *captured_by);

/**
 * @brief call once every second.
 *
 * @param self
 */
CTFError CTFGame_Tick(CTFGame *self);

#ifdef __cplusplus
}
#endif
