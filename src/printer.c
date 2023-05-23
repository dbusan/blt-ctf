#include "printer.h"

#include <stdio.h>

void PrintHighscores(Highscores *h) {
  printf("High Scores\n");
  printf("Name\tTime held\n");
  for (uint16_t i = 0; i < kNrEntries; i++) {
    printf("%s\t%d\n", h->entries[i].name, h->entries[i].time);
  }
  printf("\n");
}