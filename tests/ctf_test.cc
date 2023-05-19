#include "ctf.h"

#include <gtest/gtest.h>

#define STRLEN(x) (sizeof(x) / sizeof(char))
#define STRNCPY(dest, x) (strncpy(dest, x, STRLEN(x)))

TEST(ctf_run, initialization) {
  CTFGame game;
  CTFGame_Init(&game);
  EXPECT_EQ(game.is_running, false);
  EXPECT_EQ(game.holder.capture_uid, kUninitialisedUID);

  // start game
  CTFGame_Start(&game);

  // check capture uid as 0
  EXPECT_EQ(game.holder.capture_uid, 0);
  // User captures flag
  EXPECT_EQ(game.holder.time, 0);
  // check game is running
  EXPECT_EQ(game.is_running, true);
  // check default holder is VK6BSP
  EXPECT_EQ(memcmp(game.holder.name, "VK6BSP", sizeof("VK6BSP") / sizeof(char)), 0);

  (void)CTFGame_Tick(&game);
  EXPECT_EQ(game.holder.time, 1);

  // try ticking while stopped
  CTFGame_Stop(&game);

  // should not increment and return error
  EXPECT_EQ(CTFGame_Tick(&game), err_ctf_not_running);
  // should be 0
  EXPECT_EQ(game.is_running, false);
  EXPECT_EQ(game.holder.time, 0);
  EXPECT_EQ(game.holder.capture_uid, kUninitialisedUID);
}

TEST(ctf_run, capture_and_increment) {
  CTFGame game;
  CTFGame_Init(&game);
  CTFGame_Start(&game);
  // User captures flag
  ASSERT_EQ(CTFGame_Capture(&game, "VK6BUS", STRLEN("VK6BUS")), all_ok);
  EXPECT_EQ(game.holder.capture_uid, 1);

  // observe user is currently flag holder and time since held
  char callsign[20] = {0x00};
  memcpy(callsign, game.holder.name, sizeof(game.holder.name) / sizeof(char));

  EXPECT_EQ(memcmp(callsign, "VK6BUS", STRLEN("VK6BUS")), 0);
  // increment time
  (void)CTFGame_Tick(&game);
  EXPECT_EQ(game.holder.time, 1);
  (void)CTFGame_Tick(&game);
  (void)CTFGame_Tick(&game);
  EXPECT_EQ(game.holder.time, 3);
}

TEST(ctf_run, repeated_capture) {
  CTFGame game;
  CTFGame_Init(&game);
  CTFGame_Start(&game);
  // User captures flag
  ASSERT_EQ(CTFGame_Capture(&game, "VK6BUS", STRLEN("VK6BUS")), all_ok);
  for (uint8_t i = 0; i < 5; i++) {
    (void)CTFGame_Tick(&game);
  }

  EXPECT_EQ(game.holder.time, 5);
  EXPECT_EQ(game.holder.capture_uid, 1);
  // someone else captures flag
  (void)CTFGame_Capture(&game, "VK6CHARLIE", STRLEN("VK6CHARLIE"));
  EXPECT_EQ(game.holder.time, 0);
  EXPECT_EQ(game.holder.capture_uid, 2);
  // observe user is currently flag holder and time since held
  char callsign[20] = {0x00};
  memcpy(callsign, game.holder.name, sizeof(game.holder.name) / sizeof(char));

  // observe user is currently flag holder and time held
  EXPECT_EQ(memcmp(callsign, "VK6CHARLIE", sizeof("VK6CHARLIE") / sizeof(char)), 0);
  EXPECT_NE(memcmp(callsign, "VK6BUS", sizeof("VK6BUS") / sizeof(char)), 0);
  // observe capture time is reset to 0
  EXPECT_EQ(game.holder.time, 0) << "Hold time not reset when flag newly captured.";

  for (uint16_t i = 0; i < 100; i++) {
    (void)CTFGame_Tick(&game);
    EXPECT_EQ(game.holder.time, i + 1) << "Game not ticking as expected.";
  }

  // observe high score table reflecting prev user and current user (if time held is high enough)
}

TEST(ctf_run, printhighscores) {
  CTFGame game;
  CTFGame_Init(&game);
  CTFGame_Start(&game);

  // User captures flag
  (void)CTFGame_Capture(&game, "VK6BUS", STRLEN("VK6BUS"));
  for (uint16_t i = 0; i < 5600; i++) {
    (void)CTFGame_Tick(&game);
  }

  (void)CTFGame_Capture(&game, "VK6CHARLIE", STRLEN("VK6CHARLIE"));
  for (uint16_t i = 0; i < 3200; i++) {
    (void)CTFGame_Tick(&game);
  }

  // CTFGame_Highscores(&game);
}

TEST(ctf, input_sanitization) {
  CTFGame game;
  CTFGame_Init(&game);
  CTFGame_Start(&game);

  // minimum length of 3
  EXPECT_EQ(CTFGame_Capture(&game, "1", STRLEN("1")), err_callsign_invalid);
  EXPECT_EQ(CTFGame_Capture(&game, "", STRLEN("")), err_callsign_invalid);
  // max length of 8 characters - trims to kMaxlength
  char name[20] = "VK1231231231231";
  EXPECT_EQ(CTFGame_Capture(&game, "VK1231231231231", STRLEN("VK1231231231231")), all_ok);
  EXPECT_EQ(memcmp(name, game.holder.name, kMaxCallsignLength), 0);
  // only alphanumeric and ascii 0 (ascii 0 only after the minimum length of characters)
  EXPECT_EQ(CTFGame_Capture(&game, "VK6BUS!", STRLEN("VK6BUS!")), err_callsign_invalid);

  // convert lower to upper
}

// some form of module integration test

TEST(ctf_run, highscores) {
  CTFGame game;
  CTFGame_Init(&game);
  CTFGame_Start(&game);

  // User captures flag
  (void)CTFGame_Capture(&game, "VK6BUS", STRLEN("VK6BUS"));
  for (uint16_t i = 0; i < 5600; i++) {
    (void)CTFGame_Tick(&game);
  }

  EXPECT_EQ(game.holder.time, 5600) << "Current holder time not set correctly";
  EXPECT_EQ(game._table.entries[0].time, 5600) << "Current holder time not set correctly";
  // observe highscore change - top should be VK6BUS

  (void)CTFGame_Capture(&game, "VK6CHARLIE", STRLEN("VK6CHARLIE"));
  for (uint16_t i = 0; i < 3200; i++) {
    (void)CTFGame_Tick(&game);
  }

  EXPECT_EQ(game.holder.time, 3200) << "Current holder time not set correctly";
  EXPECT_EQ(game._table.entries[1].time, 3200) << "Current holder time not set correctly";

  // Highscores_Print(&(game._table));
}