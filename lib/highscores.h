/**
 * @file highscores.h
 * @author Daniel (dbusan)
 * @brief A library useful to keep track of high scores in a memory-constrained
 * workspace. Maximum number of entries
 * @version 1.0
 * @date 2023-04-14
 *
 * @copyright Dbusan (c) 2023
 *
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define kNrEntries 10
#define kMaxCallsignLength 10
#define kUninitialisedUID -1

typedef int32_t time_held_t;

/**
 * @brief Highscore entry represents an entry in the highscore table.
 *
 * name - is the holder
 * time - represents for how long the holder "name" has held the flag
 * capture_uid - is the unique id of the entry, used for highscore sorting and insertion
 */
typedef struct HighscoreEntry_t {
  char name[kMaxCallsignLength];
  time_held_t time;
  int16_t capture_uid;
} HighscoreEntry;

/**
 * @brief Highscores table struct to allocate appropriate space in memory for the highscore table
 *
 */
typedef struct Highscores_t {
  HighscoreEntry entries[kNrEntries];
} Highscores;

/**
 * @brief Initialise highscores table.
 *
 * @param self pointer to to Highscores struct.
 */
void Highscores_Init(Highscores *self);

/**
 * @brief Highscores_HandleEntryAndSort handles an existing high score entry
 *
 * @param self pointer to to Highscores struct.
 * @param e
 */
void Highscores_HandleEntryAndSort(Highscores *self, HighscoreEntry *e);

#ifdef __cplusplus
}
#endif