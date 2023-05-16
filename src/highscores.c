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
    self->entries[i].capture_id = 0;
  }
  memset(self->current_holder.name, 0x00, len);
  self->current_holder.time = 0;
  self->current_holder.capture_id = 0;
}

static int Descending(const void *first, const void *second) {
  int *f = &(((HighscoreEntry *)first)->time);
  int *s = &(((HighscoreEntry *)second)->time);

  return *s - *f;
}

void Highscores_Sort(Highscores *self) {
  qsort(self->entries, NR_ENTRIES, sizeof(self->entries[0]),
        Descending);
}

// this calls sort and then checks if the time held is greater than the minimum score
bool Highscores_Validate(Highscores *self, HighscoreEntry *e) {
  Highscores_Sort(self);

  return ((e->time) > (self->entries[NR_ENTRIES - 1].time));
}

void Highscores_HandleEntryAndSort(Highscores *self, HighscoreEntry *e) {
  // sort entries descending

  // if entry.capture_id matches any of the capture IDs in the table, new entry will not be added

  Highscores_Sort(self);
  // validate new entry - see if it makes the high score
  if (Highscores_Validate(self, e)) {
    // if it does, eliminate last entry
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