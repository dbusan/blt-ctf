#include <gtest/gtest.h>

#include "../src/highscores.h"

TEST(Highscores, Highscores_Init)
{

  Highscores table;
  Highscores_Init(&table);
  EXPECT_EQ(table.current_nr_entries, 0)
      << "Not initialised properly. Curr entries are not 0 but "
      << table.current_nr_entries;

  // initialise check
  for (uint16_t i = 0; i < NR_ENTRIES; i++)
  {
    char name[20] = {0x00};
    EXPECT_EQ(memcmp(table.entries[i].name, name, sizeof(table.entries[i].name)), 0) << "Entry name not initialised " << i << "\n";
    EXPECT_EQ(table.entries[i].time, 0) << "Time not initialised for entry " << i;
  }
}

TEST(Highscores, Highscores_Insert)
{

  Highscores table;
  Highscores_Init(&table);

  // insert new entry
  char name[10] = "VK6BUS";
  HighscoreEntry e;
  strncpy(e.name, name, sizeof(name));
  e.time = 100;

  Highscores_InsertAndSort(&table, &e);
  // confirm nr of entries incremented
  EXPECT_EQ(table.current_nr_entries, 1);
  // confirm entry is at top of list after insert and sort
  EXPECT_EQ(memcmp(table.entries[0].name, name, sizeof(name)), 0);

  // add another entry larger and see if it is at the top
  strncpy(name, "VK6BASS", sizeof("VK6BASS"));
  strncpy(e.name, name, sizeof(name));
  e.time = 120;

  Highscores_InsertAndSort(&table, &e);
  // confirm nr of entries incremented
  EXPECT_EQ(table.current_nr_entries, 2);
  // confirm entry is at the top of list after insert and sort
  EXPECT_EQ(memcmp(table.entries[0].name, name, sizeof(name)), 0) << "List not sorted correctly\n";


  // ensure only a maximum of 10 items are stored in list
  Highscores_Init(&table);


  time_held_t entries[] = {10, 20, 100, 120, 140, 160, 180, 200, 220, 240, 280, 300 };
  for (uint8_t i =0 ; i < sizeof(entries)/sizeof(time_held_t); i++) {
    e.time = entries[i];
    Highscores_InsertAndSort(&table, &e);
    EXPECT_LE(table.current_nr_entries, 10);
  }
  
  // insert new high score entry at the top
  strncpy(name, "NA3BAS", sizeof("NA3BAS"));
  strncpy(e.name, name, sizeof(e.name));
  e.time = 360;


  time_held_t second_last_entry_time = table.entries[NR_ENTRIES-2].time;

  Highscores_InsertAndSort(&table, &e);
  // check that it is first in the table
  EXPECT_EQ(memcmp(table.entries[0].name, name,sizeof(name)),0);
  // check that second last entry is now last entry (same time)
  EXPECT_EQ(second_last_entry_time, table.entries[NR_ENTRIES-1].time);

  // Highscores_Print(&table);


}
