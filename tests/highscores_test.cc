#include "../src/highscores.h"

#include <gtest/gtest.h>

#define STRLEN(x) (sizeof(x) / sizeof(char))
#define STRNCPY(dest, x) (strncpy(dest, x, STRLEN(x)))

TEST(Highscores, Highscores_Init) {
  Highscores table;
  Highscores_Init(&table);

  // initialise check
  for (uint16_t i = 0; i < NR_ENTRIES; i++) {
    char name[20] = {0x00};
    EXPECT_EQ(memcmp(table.entries[i].name, name, sizeof(table.entries[i].name)), 0)
        << "Entry name not initialised " << i << "\n";
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
  strncpy(e.name, name, STRLEN(name));
  e.capture_uid = 0;
  e.time = 100;

  Highscores_HandleEntryAndSort(&table, &e);
  // confirm entry is at top of list after insert and sort
  EXPECT_EQ(memcmp(table.entries[0].name, name, STRLEN(name)), 0);

  // add another entry larger and see if it is at the top
  strncpy(name, "VK6BASS", sizeof("VK6BASS"));
  strncpy(e.name, name, sizeof(name));
  e.capture_uid++;
  e.time = 120;

  Highscores_HandleEntryAndSort(&table, &e);
  // confirm entry is at the top of list after insert and sort
  EXPECT_EQ(memcmp(table.entries[0].name, name, STRLEN(name)), 0) << "List not sorted correctly\n";

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
  e.capture_uid++;
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

  int16_t capture_index = 0;

  uint32_t time_held = 100;
  const char name[] = "VK6BUS";
  HighscoreEntry e;
  strncpy(e.name, name, sizeof(name));
  e.time = time_held;
  e.capture_uid = capture_index;

  // add new entry
  uint32_t ticks_elapsed = 50;
  Highscores_HandleEntryAndSort(&table, &e);
  EXPECT_EQ(table.entries[0].time, e.time);

  // update existing entry with new score
  e.time += ticks_elapsed;
  // HandleEntryAndSort should not add the same entry to the database if the capture_uid already exists in the database
  Highscores_HandleEntryAndSort(&table, &e);
  // check if top entry corresponds with updated entry
  EXPECT_EQ(table.entries[0].time, e.time);
  // check if top entry name matches
  EXPECT_EQ(memcmp(table.entries[0].name, name, STRLEN(name)), 0);
  // check that capture id matches the one entered
  EXPECT_EQ(table.entries[0].capture_uid, capture_index);

  // next entry should be unitialised since we did not add a new entry but update an existing one
  EXPECT_EQ(table.entries[1].time, 0);
  EXPECT_EQ(table.entries[1].name[0], 0x00);
  EXPECT_EQ(table.entries[1].capture_uid, kUninitialisedUID);
}

static uint32_t max(uint32_t *times, uint16_t len) {
  uint32_t maxval = times[0];
  for (uint16_t i = 1; i < len; i++) {
    if (times[i] > maxval) {
      maxval = times[i];
    }
  }
  return maxval;
}

static uint32_t min(uint32_t *times, uint16_t len) {
  uint32_t minval = times[0];
  for (uint16_t i = 1; i < len; i++) {
    if (times[i] < minval) {
      minval = times[i];
    }
  }
  return minval;
}

TEST(Highscores, Highscores_fill_table) {
  Highscores table;
  Highscores_Init(&table);

  char names[10][10] = {"VK6BUS", "VK6BASS", "K6NAD",  "DD3FAD", "VK1DAT",
                        "KN3SOB", "VK6BSP",  "FS1KRD", "VK6AAB", "KG8DOD"};

  time_held_t times[10] = {10000, 1600, 5400, 100, 5, 150, 35000, 2200, 20000, 2100};
  int16_t uid = 0;
  // generate 10 entries
  HighscoreEntry e;
  for (uint8_t i = 0; i < 10; i++) {
    strncpy(e.name, names[i], STRLEN(names[i]));
    e.time = times[i];
    e.capture_uid = uid++;

    Highscores_HandleEntryAndSort(&table, &e);
  }

  // check top entry
  EXPECT_EQ(table.entries[0].time, max(static_cast<uint32_t *>(times), sizeof(times) / sizeof(time_held_t)));
  EXPECT_EQ(memcmp(table.entries[0].name, "VK6BSP", STRLEN("VK6BSP")), 0);
  // check lowest scoreboard entry
  EXPECT_EQ(table.entries[9].time, min(static_cast<uint32_t *>(times), sizeof(times) / sizeof(time_held_t)));
  EXPECT_EQ(memcmp(table.entries[9].name, "VK1DAT", STRLEN("VK1DAT")), 0);

  // add another entry that will replace bottom one, VK1DAT
  // strncpy(e.name, "VK2PHAT", STRLEN("VK2PHAT"));
  STRNCPY(e.name, "VK2PHAT");
  e.time = 15;
  e.capture_uid = uid++;

  Highscores_HandleEntryAndSort(&table, &e);
  EXPECT_EQ(table.entries[9].time, e.time);
  EXPECT_EQ(memcmp(table.entries[9].name, e.name, STRLEN("VK2PHAT")), 0);
}
