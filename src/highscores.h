/**
 * @file highscores.h
 * @author Daniel (daniel@sstc)
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
#include <string.h>

#define NR_ENTRIES 10
#define kUninitialisedUID -1

typedef uint32_t time_held_t;

typedef struct HighscoreEntry_t {
  char name[20];
  time_held_t time;
  int16_t capture_uid;
} HighscoreEntry;

typedef struct Highscores_t {
  HighscoreEntry entries[NR_ENTRIES];
  // HighscoreEntry current_holder;
} Highscores;

void Highscores_Init(Highscores *self);

/**
 * @brief HighscoresInsertAndSort inserts a new entry into the list
 *
 * @param self
 * @param e
 */
void Highscores_HandleEntryAndSort(Highscores *self, HighscoreEntry *e);

void Highscores_Print(const Highscores *self);

#ifdef __cplusplus
}
#endif