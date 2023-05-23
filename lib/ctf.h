#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "highscores.h"

#define DEFAULT_CALLSIGN_HOLDER "VK6BSP"

/**
 * @brief CTFGame structure holding activity information.
 *
 * is_running gets set by Init/Start and is used for checks to return errors
 * holder is the current flag holder - check Highscores.h for internals
 * _table is an array of Highscores - containing Highscore entries sorted in descending order
 */
typedef struct CTFGame_t {
  bool is_running;
  HighscoreEntry holder;
  Highscores _table;
} CTFGame;

/**
 * @brief Different errors returned by functions within ctf.h
 *
 * all_ok is returned when function performed task successfully
 * err_ctf_not_running is returned when CTFGame_Capture or Tick() is called without Init/Start being called previously
 * err_callsign_invalid is called if CTFGame_Capture is called with an invalid capturer callsign.
 * Callsign can only have alphanumerics, a maximum length of 10, and a minimum length of 3.
 */
typedef enum CTFError_t {
  all_ok,
  err_ctf_not_running,
  err_callsign_invalid,
} CTFError;

/**
 * @brief Initialises the CTFGame structure. This is the first function that shall be called after CTFGame variable is
 * created
 *
 * @param self - reference to CTFGame variable.
 */
void CTFGame_Init(CTFGame *self);

/**
 * @brief Starts the CTFGame: sets the default callsign holder as defined above, and sets is_running to true, to allow
 * capture activities to occur and CTFGame_Tick() to be called.
 *
 * @param self
 */
void CTFGame_Start(CTFGame *self);

/**
 * @brief Calls Init.
 *
 * @param self
 */
void CTFGame_Stop(CTFGame *self);

/**
 * @brief Function is used after game is started to capture callsign.
 *
 * @param self is a reference to the CTFGame session variable.
 * @param capturer_callsign is a string of up to 10 characters representing the callsign of the holder. Callsign can
 * only have alphanumerics, a maximum length of 10, and a minimum length of 3.
 * @param len is the length of the callsign string.
 * @return CTFError
 */
CTFError CTFGame_Capture(CTFGame *self, const char *capturer_callsign, uint8_t len);

/**
 * @brief This function increments the time_held of the current holder and updates the high score table.
 *
 * @param self is a reference to the CTFGame session variable.
 */
CTFError CTFGame_Tick(CTFGame *self);

#ifdef __cplusplus
}
#endif
