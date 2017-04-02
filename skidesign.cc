/*
PROG: skidesign
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>

int main() {
  std::ofstream cout("skidesign.out");
  std::ifstream cin("skidesign.in");

  size_t n;
  cin >> n;

  std::vector<int> heights;
  for (size_t i = 0; i < n; ++i) {
    int height;
    cin >> height;
    heights.push_back(height);
  }

  int max_height = heights.front();
  int min_height = heights.front();
  for (int height : heights) {
    if (min_height > height)
      min_height = height;
    if (max_height < height)
      max_height = height;
  }

  if (max_height - min_height <= 17) {
    cout << 0 << std::endl;
    return 0;
  }

  std::vector<int> histogram(max_height + 1, 0);
  for (int height : heights)
    histogram[height] += 1;

  int min_cost = 1000000000;
  for (int low = min_height; low + 17 < max_height; ++low) {
    int high = low + 17;

    int cost = 0;
    for (int height = min_height; height < low; ++height) {
      int squared = (low - height) * (low - height);
      cost += squared * histogram[height];
    }
    for (int height = high + 1; height <= max_height; ++height) {
      int squared = (height - high) * (height - high);
      cost += squared * histogram[height];
    }

    if (min_cost > cost)
      min_cost = cost;
  }

  cout << min_cost << std::endl;

  return 0;
}
