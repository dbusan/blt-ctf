#include "../src/highscores.h"

#include <gtest/gtest.h>

TEST(Highscores, Highscores_Init) {
  Highscores table;
  Highscores_Init(&table);

  // initialise check
  for (uint16_t i = 0; i < NR_ENTRIES; i++) {
    char name[20] = {0x00};
    EXPECT_EQ(memcmp(table.entries[i].name, name, sizeof(table.entries[i].name)), 0) << "Entry name not initialised " << i << "\n";
    EXPECT_EQ(table.entries[i].time, 0) << "Time not initialised for entry " << i;
  }
}

// insert new entry
TEST(Highscores, Highscores_Insert) {
  Highscores table;
  Highscores_Init(&table);

  // insert new entry
  char name[10] = "VK6BUS";
  HighscoreEntry e;
  strncpy(e.name, name, sizeof(name));
  e.time = 100;

  Highscores_HandleEntryAndSort(&table, &e);
  // confirm entry is at top of list after insert and sort
  EXPECT_EQ(memcmp(table.entries[0].name, name, sizeof(name)), 0);

  // add another entry larger and see if it is at the top
  strncpy(name, "VK6BASS", sizeof("VK6BASS"));
  strncpy(e.name, name, sizeof(name));
  e.time = 120;

  Highscores_HandleEntryAndSort(&table, &e);
  // confirm entry is at the top of list after insert and sort
  EXPECT_EQ(memcmp(table.entries[0].name, name, sizeof(name)), 0) << "List not sorted correctly\n";

  // ensure only a maximum of 10 items are stored in list
  Highscores_Init(&table);

  time_held_t entries[] = {10, 20, 100, 120, 140, 160, 180, 200, 220, 240, 280, 300};
  for (uint8_t i = 0; i < sizeof(entries) / sizeof(time_held_t); i++) {
    e.time = entries[i];
    Highscores_HandleEntryAndSort(&table, &e);
  }

  // insert new high score entry at the top
  strncpy(name, "NA3BAS", sizeof("NA3BAS"));
  strncpy(e.name, name, sizeof(e.name));
  e.time = 360;

  time_held_t second_last_entry_time = table.entries[NR_ENTRIES - 2].time;

  Highscores_HandleEntryAndSort(&table, &e);
  // check that it is first in the table
  EXPECT_EQ(memcmp(table.entries[0].name, name, sizeof(name)), 0);
  // check that second last entry is now last entry (same time)
  EXPECT_EQ(second_last_entry_time, table.entries[NR_ENTRIES - 1].time);
}

// update existing entry
TEST(Highscores, Highscores_Update) {
  Highscores table;
  Highscores_Init(&table);

  uint16_t capture_index = 1;

  uint32_t time_held = 100;
  const char name[] = "VK6BUS";
  HighscoreEntry e;
  strncpy(e.name, name, sizeof(name));
  e.time = time_held;
  e.capture_id = capture_index;

  // add new entry
  uint32_t ticks_elapsed = 50;
  Highscores_HandleEntryAndSort(&table, &e);

  // update existing entry with new score
  e.time += ticks_elapsed;
  // HandleEntryAndSort should not add the same entry to the database if the capture_id already exists in the database
  Highscores_HandleEntryAndSort(&table, &e);
  EXPECT_EQ(table.entries[0].time, e.time + ticks_elapsed);
  EXPECT_EQ(memcmp(table.entries[0].name, name, sizeof(name) / sizeof(char)), 0);

  EXPECT_EQ(table.entries[1].time, 0);  // continue here
  EXPECT_EQ(table.entries[1].name[0], 0x00);
}