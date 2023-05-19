#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "ctf.h"

int main(void) {
  CTFGame session;
  CTFGame_Init(&session);
  CTFGame_Start(&session);
  char name[20] = {0x00};

  int16_t i = 10;
  while (i--) {
    snprintf(name, 20, "VK%1dBA%c", i, (80 - i));
    (void)CTFGame_Capture(&session, name, strlen(name));
    for (uint16_t ii = 0; ii < (6000 - i * 100); ii++) {
      (void)CTFGame_Tick(&session);
    }
  }

  CTFGame_Highscores(&session);
  CTFError err = CTFGame_Capture(&session, "VK6BuSSIN<>?!", sizeof("VK6BuSSIN<>?!") / sizeof(char));
  if (err != all_ok) {
    printf("Error: %d. Didn't capture callsign by %s\n", err, "VK6BuSSIN<>?!");
  }
  for (uint32_t i = 0; i < 62000; i++) {
    (void)CTFGame_Tick(&session);
  }

  CTFGame_Highscores(&session);
  return 0;
}
