#include "../src/ctf.h"

#include <gtest/gtest.h>

TEST(ctf_run, scenario1) {
  CTFGame game;
  CTFGame_Init(&game);
  CTFGame_Start(&game);

  // User captures flag
  CTFGame_Capture(&game, "VK6BUS");

  // observe user is currently flag holder and time since held
  char callsign[20] = {0x00};
  CTFGame_CurrentHolder(&game, callsign);

  EXPECT_EQ(memcmp(callsign, "VK6BUS", sizeof("VK6BUS") / sizeof(char)), 0);
  // increment time
  CTFGame_Tick(&game);
  uint32_t current_time_held = CTFGame_GetHoldTime(&game);
  EXPECT_EQ(current_time_held, 1);
  CTFGame_Tick(&game);
  CTFGame_Tick(&game);
  current_time_held = CTFGame_GetHoldTime(&game);
  EXPECT_EQ(current_time_held, 3);
  // observe high score table reflecting current user (if time held is high enough)

  // someone else captures flag
  CTFGame_Capture(&game, "VK6CHARLIE");
  CTFGame_CurrentHolder(&game, callsign);

  // observe user is currently flag holder and time held
  EXPECT_EQ(memcmp(callsign, "VK6CHARLIE", sizeof("VK6CHARLIE") / sizeof(char)), 0);

  // observe high score table reflecting prev user and current user (if time held is high enough)
}