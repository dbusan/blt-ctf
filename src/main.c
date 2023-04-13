#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int32_t time_held_t;

#define NR_ENTRIES 10

typedef struct {
  char name[255];
  time_held_t time;
} HighscoreEntry;

typedef struct {
  HighscoreEntry entries[NR_ENTRIES];
  uint8_t current_nr_entries;

  void (*sort)();
} Highscores;

int Descending(const void *first, const void *second) {

  HighscoreEntry f = *((HighscoreEntry *)first);
  HighscoreEntry s = *((HighscoreEntry *)second);

  if (f.time > s.time)
    return 1;
  if (f.time < s.time)
    return -1;
  return 0;
}

void SortHighscores(Highscores *self) {
  printf("\n current number entries %d, sizeof %ld, entry 0 name %10s\n",
         self->current_nr_entries, sizeof(self->entries[0]),
         self->entries[0].name);

  qsort(self->entries, self->current_nr_entries, sizeof(self->entries[0]),
        Descending);
}

void InitHighscores(Highscores *self) {
  self->current_nr_entries = 0;
  self->sort = &SortHighscores;
}

void PrintHighscore(const Highscores *table) {

  printf("High Scores\n\n");
  printf("Name\tTime held\n");

  for (uint16_t i = 0; i < table->current_nr_entries; i++) {
    printf("%s\t%d\n", table->entries[i].name, table->entries[i].time);
  }
  printf("\n");
}

int main(void) {

  Highscores table;
  // InitHighscores(&table);

  HighscoreEntry entry = {"VK6BUS", 2153};

  table.entries[0] = entry;
  table.current_nr_entries = 1;

  PrintHighscore(&table);
  // entry.name
  entry = (HighscoreEntry){"VK6KEK", 111};
  table.entries[table.current_nr_entries] = entry;
  table.current_nr_entries++;
  entry = (HighscoreEntry){"VK6ABK", 1321};
  table.entries[table.current_nr_entries] = entry;
  table.current_nr_entries++;
  entry = (HighscoreEntry){"VK6CAK", 111123};
  table.entries[table.current_nr_entries] = entry;
  table.current_nr_entries++;

  PrintHighscore(&table);

  printf("sorted\n");

  printf("curr nr entries %d \n", table.current_nr_entries);
  table.sort = &SortHighscores;
  table.sort();
  printf("curr nr entries %d \n", table.current_nr_entries);
  PrintHighscore(&table);

  return 0;
}
