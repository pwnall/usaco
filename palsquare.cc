/*
PROG: palsquare
LANG: C++11
*/

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// Doesn't handle the n=0 case, because we don't need it here.
std::string itoa(int number, int base) {
  std::vector<char> result;
  while (number > 0) {
    result.push_back(digits[number % base]);
    number /= base;
  }

  std::reverse(result.begin(), result.end());
  return std::string(result.begin(), result.end());
}

int main() {
  std::ofstream cout("palsquare.out");
  std::ifstream cin("palsquare.in");

  int base;
  cin >> base;

  for (int i = 1; i < 300; ++i) {
    std::string squared = itoa(i * i, base);
    std::string reversed = squared;
    std::reverse(reversed.begin(), reversed.end());
    if (squared == reversed) {
      std::string number = itoa(i, base);
      cout << number << " " << squared << std::endl;
    }
  }
  return 0;
}
