/*
PROG: barn1
LANG: C++11
*/

#include <algorithm>
#include <fstream>
#include <vector>

int main() {
  std::ofstream cout("barn1.out");
  std::ifstream cin("barn1.in");

  int boards, stalls, cows;
  cin >> boards >> stalls >> cows;

  std::vector<int> cow_stalls;
  for (int i = 0; i < cows; ++i) {
    int cow_stall;
    cin >> cow_stall;
    cow_stalls.push_back(cow_stall);
  }
  std::sort(cow_stalls.begin(), cow_stalls.end());

  std::vector<int> gaps;
  for (int i = 1; i < cows; ++i)
    gaps.push_back(cow_stalls[i] - cow_stalls[i - 1] - 1);
  std::sort(gaps.begin(), gaps.end());

  int covered = cows;
  for (int i = 0; i < cows - boards; ++i)
    covered += gaps[i];

  cout << covered << std::endl;
  return 0;
}
