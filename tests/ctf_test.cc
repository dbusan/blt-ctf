#include "../src/ctf.h"

#include <gtest/gtest.h>

TEST(ctf_run, initialization) {
  CTFGame game;
  CTFGame_Init(&game);
  EXPECT_EQ(game.is_running, false);
  CTFGame_Start(&game);
  // User captures flag
  EXPECT_EQ(game.time_held, 0);
  EXPECT_EQ(game.is_running, true);

  // set default holder to VK6BSP
  EXPECT_EQ(memcmp(game.captured_by, "VK6BSP", sizeof("VK6BSP") / sizeof(char)), 0);

  (void)CTFGame_Tick(&game);
  EXPECT_EQ(game.time_held, 1);

  // try ticking while stopped
  CTFGame_Stop(&game);

  // should not increment
  EXPECT_EQ(CTFGame_Tick(&game), err_ctf_not_running);
  // should be 0
  EXPECT_EQ(game.is_running, false);
  EXPECT_EQ(game.time_held, 0);
}

TEST(ctf_run, capture_and_increment) {
  CTFGame game;
  CTFGame_Init(&game);
  CTFGame_Start(&game);
  // User captures flag
  ASSERT_EQ(CTFGame_Capture(&game, "VK6BUS"), all_ok);

  // observe user is currently flag holder and time since held
  char callsign[20] = {0x00};
  CTFGame_CurrentHolder(&game, callsign);

  EXPECT_EQ(memcmp(callsign, "VK6BUS", sizeof("VK6BUS") / sizeof(char)), 0);
  // increment time
  (void)CTFGame_Tick(&game);
  uint32_t current_time_held = game.time_held;
  EXPECT_EQ(current_time_held, 1);
  (void)CTFGame_Tick(&game);
  (void)CTFGame_Tick(&game);
  current_time_held = game.time_held;
  EXPECT_EQ(current_time_held, 3);
  // observe high score table reflecting current user (if time held is high enough)
}

TEST(ctf_run, repeated_capture) {
  CTFGame game;
  CTFGame_Init(&game);
  CTFGame_Start(&game);
  // User captures flag
  ASSERT_EQ(CTFGame_Capture(&game, "VK6BUS"), all_ok);
  for (uint8_t i = 0; i < 5; i++) {
    (void)CTFGame_Tick(&game);
  }
  EXPECT_EQ(game.time_held, 5);
  // someone else captures flag
  (void)CTFGame_Capture(&game, "VK6CHARLIE");
  EXPECT_EQ(game.time_held, 0);

  // observe user is currently flag holder and time since held
  char callsign[20] = {0x00};
  CTFGame_CurrentHolder(&game, callsign);

  // observe user is currently flag holder and time held
  EXPECT_EQ(memcmp(callsign, "VK6CHARLIE", sizeof("VK6CHARLIE") / sizeof(char)), 0);
  EXPECT_NE(memcmp(callsign, "VK6BUS", sizeof("VK6BUS") / sizeof(char)), 0);
  // observe capture time is reset to 0
  EXPECT_EQ(game.time_held, 0) << "Hold time not reset when flag newly captured.";

  for (uint16_t i = 0; i < 100; i++) {
    (void)CTFGame_Tick(&game);
    EXPECT_EQ(game.time_held, i + 1) << "Game not ticking as expected.";
  }

  // observe high score table reflecting prev user and current user (if time held is high enough)
}

// some form of module integration test
#include "../src/highscores.h"
TEST(ctf_run, highscores) {
  Highscores scoreboard;
  Highscores_Init(&scoreboard);

  CTFGame game;
  CTFGame_Init(&game);
  CTFGame_Start(&game);

  // User captures flag
  (void)CTFGame_Capture(&game, "VK6BUS");
  for (uint16_t i = 0; i < 5600; i++) {
    (void)CTFGame_Tick(&game);
  }

  (void)CTFGame_Capture(&game, "VK6CHARLIE");
  for (uint16_t i = 0; i < 3200; i++) {
    (void)CTFGame_Tick(&game);
  }
}