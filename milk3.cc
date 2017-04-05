/*
PROG: milk3
LANG: C++11
*/

#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <set>
#include <unordered_set>

typedef std::array<int, 3> state;

namespace std {
  template <> struct hash<state> {
    size_t operator()(const state& current) const {
      return hash<int>()(current[0] * 10000 + current[1] * 100 + current[2]);
    }
  };
}

int main() {
  std::ofstream cout("milk3.out");
  std::ifstream cin("milk3.in");

  state capacity;
  cin >> capacity[0] >> capacity[1] >> capacity[2];

  state initial = {0, 0, capacity[2]};

  std::unordered_set<state> visited;
  visited.insert(initial);
  std::deque<state> queue;
  queue.push_back(initial);

  std::set<int> results;
  results.insert(capacity[2]);

  while (!queue.empty()) {
    state current = queue.front();
    queue.pop_front();

    /*
    for (int i = 0; i < 3; ++i) {
      std::cerr << current[0] << " " << current[1] << " " << current[2] <<
                   std::endl;
    }
    */

    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (i == j) continue;

        state next = current;
        int transfer = std::min(next[i], capacity[j] - next[j]);
        next[i] -= transfer;
        next[j] += transfer;

        if (visited.count(next))
          continue;

        visited.insert(next);
        queue.push_back(next);

        if (!next[0])
          results.insert(next[2]);
      }
    }
  }

  bool first = true;
  for (int result : results) {
    if (first) {
      first = false;
    } else {
      cout << " ";
    }
    cout << result;
  }
  cout << std::endl;

  return 0;
}
