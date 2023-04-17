#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "highscores.h"

void test_ctf() {
  // someone captures flag

  // they are now leaders
  // timer increments
  // highscore table updated

  // someone else captures flag

  // they are now leaders
  // set new leader

  return;
}

int main(void) {

  // create highscores table with 10 entries total
  Highscores table;
  table.current_nr_entries = 0;

  HighscoresPrint(&table);

  // test insert entry
  HighscoresInsertAndSort(&table, &((HighscoreEntry){"VK6ABB", 111}));
  assert(table.current_nr_entries == 1);

  HighscoreEntry entry = (HighscoreEntry){"VK6BUS", 12345};
  HighscoresInsertAndSort(&table, &entry);
  HighscoresPrint(&table);

  assert(table.current_nr_entries == 2);

  for (uint8_t i = 0; i < NR_ENTRIES + 5; i++) {
    entry = (HighscoreEntry){"VK1KEK", (i * 10)};
    HighscoresInsertAndSort(&table, &entry);
  }
  assert(table.current_nr_entries <= NR_ENTRIES);

  HighscoresPrint(&table);
  // check that lower than last score do not make it on the list
  entry = (HighscoreEntry){"VK1KEK", 30};
  HighscoresInsertAndSort(&table, &entry);

  HighscoresPrint(&table);

  // set new

  return 0;
}
