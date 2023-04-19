#ifdef __cplusplus
extern "C" {
#endif

#include "ctf.h"

#include <stdbool.h>

void CTFGame_Init(CTFGame *self) {
  self->is_running = false;
}

void CTFGame_Start(CTFGame *self) {
  self->is_running = true;
}

#ifdef __cplusplus
}
#endif
