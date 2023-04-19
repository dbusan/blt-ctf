#ifdef __cplusplus
extern "C"
{
#endif

#include "highscores.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void Highscores_Init(Highscores *self)
{

  uint8_t len = sizeof(self->entries[0].name);

  for (uint8_t i = 0; i < NR_ENTRIES; i++)
  {
    memset(self->entries[i].name, 0x00, len);
    self->entries[i].time = 0;
  }

  self->current_nr_entries = 0;
}

int Descending(const void *first, const void *second)
{

  int *f = &(((HighscoreEntry *)first)->time);
  int *s = &(((HighscoreEntry *)second)->time);

  return *s - *f;
}

void Highscores_Sort(Highscores *self)
{
  qsort(self->entries, NR_ENTRIES, sizeof(self->entries[0]),
        Descending);
}

// only call after sort as this assumes lowest score is at index NR_ENTRIES-1
bool Highscores_Validate(Highscores *self, HighscoreEntry *e)
{
  // returns true if proposed high score entry time is larger than current
  // minimum
  // printf("%d > %d %d \n", e->time, self->entries[NR_ENTRIES - 1].time,
  //        self->current_nr_entries);
  Highscores_Sort(self);

  return ((e->time) > (self->entries[NR_ENTRIES - 1].time));
}

void Highscores_increment_nr_entries(Highscores *self)
{
  if (self->current_nr_entries < NR_ENTRIES)
  {
    self->current_nr_entries++;
  }
}

void Highscores_InsertAndSort(Highscores *self, HighscoreEntry *e)
{
  // sort entries descending
  Highscores_Sort(self);

  // validate new entry - see if it makes the high score
  if (Highscores_Validate(self, e))
  {
    // if it does, eliminate last entry
    self->entries[NR_ENTRIES - 1] = *e;
  }
  // run increment entry logic
  Highscores_increment_nr_entries(self);

  // sort 
  Highscores_Sort(self);
}

void Highscores_Print(const Highscores *self)
{

  printf("High Scores\n");
  printf("Name\tTime held\n");

  if (self->current_nr_entries == 0)
  {
    printf("No current entries\n");
  }
  else
  {
    for (uint16_t i = 0; i < NR_ENTRIES; i++)
    {
      printf("%s\t%d\n", self->entries[i].name, self->entries[i].time);
    }
  }

  printf("\n");
}

#ifdef __cplusplus
}
#endif