/*
PROG: combo
LANG: C++11
*/

#include <fstream>
#include <unordered_set>

void add_combos(int n, int code[3], std::unordered_set<int>& accumulator) {
  for (int delta0 = -2; delta0 <= 2; ++delta0) {
    int x0 = (n + code[0] + delta0) % n;
    for (int delta1 = -2; delta1 <= 2; ++delta1) {
      int x1 = (n + code[1] + delta1) % n;
      for (int delta2 = -2; delta2 <= 2; ++delta2) {
        int x2 = (n + code[2] + delta2) % n;

        int number = x0 * 10000 + x1 * 100 + x2;
        accumulator.insert(number);
      }
    }
  }
}

int main() {
  std::ofstream cout("combo.out");
  std::ifstream cin("combo.in");

  int n;
  cin >> n;

  int user[3], master[3];
  cin >> user[0] >> user[1] >> user[2];
  cin >> master[0] >> master[1] >> master[2];

  std::unordered_set<int> combos;
  add_combos(n, user, combos);
  add_combos(n, master, combos);

  cout << combos.size() << std::endl;
  return 0;
}
