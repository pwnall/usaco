/*
PROG: dualpal
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

bool is_palindrome(const std::string& str) {
  if (str.size() <= 1)
    return true;

  for(size_t i = 0, j = str.size() - 1; i < j; i++, j--) {
    if (str[i] != str[j])
      return false;
  }
  return true;
}

int main() {
  std::ofstream cout("dualpal.out");
  std::ifstream cin("dualpal.in");

  int n, s;
  cin >> n >> s;

  ++s;
  while (n > 0) {
    int pal_count = 0;
    for (int base = 2; base <= 10; ++base) {
      std::string number = itoa(s, base);
      if (!is_palindrome(number))
        continue;

      pal_count += 1;
      if (pal_count >= 2)
        break;
    }

    if (pal_count >= 2) {
      cout << s << std::endl;
      --n;
    }
    ++s;
  }
  return 0;
}
