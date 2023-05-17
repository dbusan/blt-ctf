#ifdef __cplusplus
extern "C" {
#endif

#include "highscores.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void Highscores_Init(Highscores *self) {
  uint8_t len = sizeof(self->entries[0].name);

  for (uint8_t i = 0; i < NR_ENTRIES; i++) {
    memset(self->entries[i].name, 0x00, len);
    self->entries[i].time = 0;
    self->entries[i].capture_uid = kUninitialisedUID;
  }
}

static uint32_t Descending(const void *first, const void *second) {
  uint32_t *f = &(((HighscoreEntry *)first)->time);
  uint32_t *s = &(((HighscoreEntry *)second)->time);

  return *s - *f;
}

static void Highscores_Sort(Highscores *self) {
  qsort(self->entries, NR_ENTRIES, sizeof(self->entries[0]), Descending);
}

// this checks if the time held is greater than the minimum score
// CALL SORT FIRST
static bool Highscores_Validate(Highscores *self, HighscoreEntry *e) {
  //

  return ((e->time) > (self->entries[NR_ENTRIES - 1].time));
}

void Highscores_HandleEntryAndSort(Highscores *self, HighscoreEntry *e) {
  // if entry.capture_uid matches any of the capture IDs in the table, new entry will not be added
  // Highscores_Sort(self);

  // existing entry - fn exit point here
  for (uint8_t i = 0; i < NR_ENTRIES; i++) {
    if (self->entries[i].capture_uid == e->capture_uid) {
      self->entries[i].time = e->time;
      Highscores_Sort(self);
      return;
    }
  }

  // if no existing uid was matched, this is a new entry.
  // validate against existing high scores, and add at the bottom of
  Highscores_Sort(self);
  if (Highscores_Validate(self, e)) {
    // if it does, replace last entry
    self->entries[NR_ENTRIES - 1] = *e;
  }
  // and then sort to bring to correct position
  Highscores_Sort(self);
}

void Highscores_Print(const Highscores *self) {
  printf("High Scores\n");
  printf("Name\tTime held\n");
  for (uint16_t i = 0; i < NR_ENTRIES; i++) {
    printf("%s\t%d\n", self->entries[i].name, self->entries[i].time);
  }
  printf("\n");
}

#ifdef __cplusplus
}
#endif