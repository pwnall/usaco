/*
PROG: ride
LANG: C++11
*/

#include <fstream>
#include <string>

int pmod(const std::string& name) {
  int value = 1;
  for (char letter : name) {
    value = (value * (letter - 'A' + 1)) % 47;
  }

  for (std::string::const_iterator it = name.begin(); it != name.end(); it++) {
    char letter = *it;

  }
  return value;
}

int main() {
  std::ofstream cout("ride.out");
  std::ifstream cin("ride.in");

  std::string group, comet;
  cin >> comet >> group;
  cout << ((pmod(comet) == pmod(group)) ? "GO" : "STAY") << std::endl;

  return 0;
}
