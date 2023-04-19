#include "../src/ctf.h"

#include <gtest/gtest.h>

TEST(ctf_run, scenario1) {
  CTFGame game;
  CTFGame_Init(&game);
  CTFGame_Start(&game);

  // User captures flag

  // observe user is currently flag holder and time since held
  // observe high score table reflecting current user (if time held is high enough)

  // someone else captures flag
  // observe user is currently flag holder and time held
  // observe high score table reflecting prev user and current user (if time held is high enough)
}