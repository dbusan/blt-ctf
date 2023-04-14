#pragma once

#include <stdint.h>

typedef int32_t time_held_t;

#define NR_ENTRIES 10

typedef struct HighscoreEntry_t {
  char name[255];
  time_held_t time;
} HighscoreEntry;

typedef struct Highscores_t {
  HighscoreEntry entries[NR_ENTRIES];
  uint8_t current_nr_entries;
} Highscores;

void HighscoresInsertAndSort(Highscores *self, HighscoreEntry *e);

void HighscoresSort(Highscores *self);

void HighscoresPrint(const Highscores *self);
