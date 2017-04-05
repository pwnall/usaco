/*
PROG: ariprog
LANG: C++11
*/

#include <algorithm>
#include <cstring>
#include <fstream>
#include <utility>
#include <vector>

bool bisquares[131072];

int main() {
  std::ofstream cout("ariprog.out");
  std::ifstream cin("ariprog.in");

  int n, m;
  cin >> n >> m;

  std::memset(bisquares, 0, sizeof(bisquares));
  for (int i = 0; i <= m; ++i) {
    for (int j = i; j <= m; ++j) {
      bisquares[i * i + j * j] = true;
    }
  }
  int max_bisquare = m * m * 2;

  std::vector<std::pair<int, int>> sequences;
  int nminus1 = n - 1;
  for (int first = 0; first <= max_bisquare; ++first) {
    if (!bisquares[first])
      continue;
    for (int last = first + nminus1; last <= max_bisquare; last += nminus1) {
      if (!bisquares[last])
        continue;

      int delta = (last - first) / nminus1;
      bool broken = false;
      int next = last;
      for (int i = 1; i < nminus1; ++i) {
        next -= delta;
        if (!bisquares[next]) {
          broken = true;
          break;
        }
      }

      if (!broken)
        sequences.push_back(std::make_pair(delta, first));
    }
  }

  if (!sequences.size()) {
    cout << "NONE" << std::endl;
    return 0;
  }

  std::sort(sequences.begin(), sequences.end());
  for (const auto& sequence : sequences)
    cout << sequence.second << " " << sequence.first << std::endl;
  return 0;
}
