/*
PROG: crypt1
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>

// Doesn't work for number = 0, we don't care.
bool digit_check(const std::vector<bool>& digit_set, int number) {
  while (number > 0) {
    int digit = number % 10;
    number /= 10;
    if (!digit_set[digit])
      return false;
  }
  return true;
}

int main() {
  std::ofstream cout("crypt1.out");
  std::ifstream cin("crypt1.in");

  size_t n;
  cin >> n;

  std::vector<int> digits;
  std::vector<bool> digit_set(10, false);
  for (size_t i = 0; i < n; ++i) {
    int digit;
    cin >> digit;
    if (digit_set[digit])
      continue;
    digit_set[digit] = true;
    digits.push_back(digit);
  }

  size_t solutions = 0;
  for (size_t x1 = 0; x1 < digits.size(); ++x1) {
    for (size_t x2 = 0; x2 < digits.size(); ++x2) {
      for (size_t x3 = 0; x3 < digits.size(); ++x3) {
        int top = digits[x1] * 100 + digits[x2] * 10 + digits[x3];

        std::vector<int> partials;
        for (size_t y = 0; y < digits.size(); ++y) {
          int partial = top * digits[y];
          if (partial >= 1000)
            continue;

          if (digit_check(digit_set, partial))
            partials.push_back(partial);
        }

        for (const auto& partial1 : partials) {
          for (const auto& partial2 : partials) {
            int total = partial1 * 10 + partial2;
            if (total >= 10000)
              continue;

            if(digit_check(digit_set, total))
              solutions += 1;
          }
        }
      }
    }
  }


  cout << solutions << std::endl;
  return 0;
}
