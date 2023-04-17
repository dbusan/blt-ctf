#include "highscores.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int Descending(const void *first, const void *second) {

  int *f = &(((HighscoreEntry *)first)->time);
  int *s = &(((HighscoreEntry *)second)->time);

  return *s - *f;
}

void HighscoresSort(Highscores *self) {
  qsort(self->entries, self->current_nr_entries, sizeof(self->entries[0]),
        Descending);
}

// only call after sort as this assumes lowest score is at index NR_ENTRIES-1
bool HighscoreValid(Highscores *self, HighscoreEntry *e) {
  // returns true if proposed high score entry time is larger than current
  // minimum
  printf("%d > %d %d \n", e->time, self->entries[NR_ENTRIES - 1].time,
         self->current_nr_entries);
  return ((e->time) > (self->entries[NR_ENTRIES - 1].time));
}

void HighscoresInsertAndSort(Highscores *self, HighscoreEntry *e) {

  if (self->current_nr_entries == NR_ENTRIES - 1) {
    // if array capacity reached
    // sort descending
    // drop lowest ranking
    HighscoresSort(self);

    if (HighscoreValid(self, e)) {
      self->entries[self->current_nr_entries] = *e;
    }
  } else {
    self->entries[self->current_nr_entries] = *e;
    self->current_nr_entries++;
  }

  HighscoresSort(self);
}

void HighscoresPrint(const Highscores *self) {

  printf("High Scores\n");
  printf("Name\tTime held\n");

  if (self->current_nr_entries == 0) {
    printf("No current entries\n");
  } else {
    for (uint16_t i = 0; i < self->current_nr_entries; i++) {
      printf("%s\t%d\n", self->entries[i].name, self->entries[i].time);
    }
  }

  printf("\n");
}
