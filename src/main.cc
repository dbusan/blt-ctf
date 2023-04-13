#include <iostream>
#include <list>

using namespace std;

typedef string name_t;
typedef int32_t time_held_t;

typedef struct {
  name_t name;
  time_held_t time;
} HighscoreEntry;

typedef struct {
  std::list<HighscoreEntry> entries;
} Highscores;

void PrintHighscore(const Highscores *table) {

  cout << "High Scores\n\n";
  cout << "Name\tTime held\n";

  for (auto e : table->entries) {
    cout << e.name << "\t" << e.time << "\n";
  }
  cout << "\n";
}

bool Descending(HighscoreEntry first, HighscoreEntry second) {
  return (first.time > second.time);
}

int main(void) {

  Highscores table;

  auto entry = HighscoreEntry{"VK6BUS", 2153};

  table.entries.push_back(entry);
  table.entries.push_back(HighscoreEntry{"VK6BAD", 111});
  table.entries.push_back(HighscoreEntry{"VK6AAB", 553});

  cout << "pre sorting:\n";
  PrintHighscore(&table);

  cout << "post sorting:\n";

  table.entries.sort(Descending);

  PrintHighscore(&table);

  return 0;
}