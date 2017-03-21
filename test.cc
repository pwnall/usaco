/*
PROG: test
LANG: C++11
*/

#include <fstream>

int main() {
  std::ofstream cout("test.out");
  std::ifstream cin("test.in");

  int a, b;
  cin >> a >> b;
  cout << a + b << std::endl;
  return 0;
}
