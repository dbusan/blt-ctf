#ifdef __cplusplus
extern "C" {
#endif

#include "highscores.h"

#include <stdbool.h>

void Highscores_Init(Highscores *self) {
  uint8_t len = sizeof(self->entries[0].name);

  for (uint8_t i = 0; i < kNrEntries; i++) {
    // replace memset
    for (uint8_t ii = 0; ii < len; ii++) {
      self->entries[i].name[ii] = 0x00;
    }
    self->entries[i].time = 0;
    self->entries[i].capture_uid = kUninitialisedUID;
  }
}

static time_held_t Descending(const void *first, const void *second) {
  time_held_t *f = &(((HighscoreEntry *)first)->time);
  time_held_t *s = &(((HighscoreEntry *)second)->time);

  return *s - *f;
}

static void Highscores_Sort(Highscores *self) {
  qsort(self->entries, kNrEntries, sizeof(self->entries[0]), Descending);
}

// this checks if the time held is greater than the minimum score
// CALL SORT FIRST
static bool Highscores_Validate(Highscores *self, HighscoreEntry *e) {
  return ((e->time) > (self->entries[kNrEntries - 1].time));
}

void Highscores_HandleEntryAndSort(Highscores *self, HighscoreEntry *e) {
  // if entry.capture_uid matches any of the capture IDs in the table, new entry will not be added
  // Highscores_Sort(self);

  // existing entry - fn exit point here
  for (uint8_t i = 0; i < kNrEntries; i++) {
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
    self->entries[kNrEntries - 1] = *e;
  }
  // and then sort to bring to correct position
  Highscores_Sort(self);
}

#ifdef __cplusplus
}
#endif