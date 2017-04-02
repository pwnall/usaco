/*
PROG: wormhole
LANG: C++11
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

struct state {
  enum class color {
    white = 0,
    gray = 1,
    black = 2,
  };

  size_t n;
  std::vector<std::pair<int, int>> wormholes;

  size_t count;
  std::vector<int> next_walk;
  std::vector<int> next_warp;
  std::vector<bool> assigned;
  std::vector<color> visited;

  void read(std::ifstream& cin) {
    cin >> n;

    for (size_t i = 0; i < n; ++i) {
      int x, y;

      cin >> x >> y;
      wormholes.push_back(std::make_pair(y, x));
    }
  }

  void solve() {
    std::sort(wormholes.begin(), wormholes.end());
    /*
    for (size_t i = 0; i < n; ++i) {
      std::cerr << "(" << wormholes[i].second << ", " << wormholes[i].first <<
                   ") ";
    }
    std::cerr << std::endl;
    */

    for (size_t i = 0; i < n; ++i) {
      if (i + 1 < n && wormholes[i].first == wormholes[i + 1].first) {
        // The 2nd wormhole has to be to the right of the first one, because of
        // how they are sorted.
        next_walk.push_back(i + 1);
      }
      else {
        next_walk.push_back(-1);
      }
    }

    /*
    for (size_t i = 0; i < n; ++i) {
      std::cerr << next_walk[i] << " ";
    }
    std::cerr << std::endl;
    */

    count = 0;
    next_warp.resize(n, false);
    assigned.resize(n, false);
    visited.resize(n, color::white);

    assign_warps(0);
  }

  void assign_warps(size_t i) {
    if (i == n) {
      /*
      for (size_t i = 0; i < n; ++i)
        std::cerr << next_warp[i] << " ";
      std::cerr << std::endl;
      */

      if (check_cycle()) {
        // std::cerr << "yes" << std::endl;
        count += 1;
      }
    }

    if (assigned[i])
      return assign_warps(i + 1);

    for (size_t j = i + 1; j < n; ++j) {
      if (!assigned[j]) {
        next_warp[i] = j;
        next_warp[j] = i;

        assigned[i] = true;
        assigned[j] = true;
        assign_warps(i + 1);
        assigned[i] = false;
        assigned[j] = false;
      }
    }
  }

  bool check_cycle() {
    std::fill(visited.begin(), visited.end(), color::white);

    for (size_t start = 0; start < n; ++start) {
      if (visited[start] != color::white)
        continue;

      if (cycle_dfs(start))
        return true;
    }
    return false;
  }

  bool cycle_dfs(int v) {
    visited[v] = color::gray;

    // We don't need to flip visited to black after returning true, because we
    // won't be checking the values anymore.

    size_t next = next_walk[next_warp[v]];
    color next_color = (next == -1) ? color::black : visited[next];
    if (next_color == color::white) {
      if (cycle_dfs(next))
        return true;
    } else if (next_color == color::gray) {
      return true;
    }
    // If the next vertex is black, we know it doesn't lead to any cycle.

    visited[v] = color::black;
    return false;
  }
};

int main() {
  std::ofstream cout("wormhole.out");
  std::ifstream cin("wormhole.in");
  state problem;

  problem.read(cin);
  problem.solve();
  cout << problem.count << std::endl;

  return 0;
}
