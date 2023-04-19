#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct CTFGame_t {
  bool is_running;

} CTFGame;

void CTFGame_Init(CTFGame *self);

void CTFGame_Start(CTFGame *self);

#ifdef __cplusplus
}
#endif
