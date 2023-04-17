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

#include <stdint.h>

#define NR_ENTRIES 10

typedef int32_t time_held_t;

typedef struct HighscoreEntry_t {
  char name[255];
  time_held_t time;
} HighscoreEntry;

typedef struct Highscores_t {
  HighscoreEntry entries[NR_ENTRIES];
  uint8_t current_nr_entries;
} Highscores;

/**
 * @brief HighscoresInsertAndSort inserts a new entry into the list
 *
 * @param self
 * @param e
 */
void Highscores_InsertAndSort(Highscores *self, HighscoreEntry *e);

HighscoreEntry Highscores_GetLowest(Highscores *self);

void Highscores_Sort(Highscores *self);

void Highscores_Print(const Highscores *self);
