/*
PROG: namenum
LANG: C++11
*/

#include <fstream>
#include <vector>
#include <unordered_set>

const char* name_keys[] =
    {"", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PRS", "TUV", "WXY"};

int main() {
  std::ifstream cdict("dict.txt");
  std::unordered_set<std::string> names;
  while (!cdict.eof()) {
    std::string name;
    cdict >> name;
    names.insert(name);
  }

  std::ofstream cout("namenum.out");
  std::ifstream cin("namenum.in");
  std::string name_string;
  cin >> name_string;

  std::vector<const char*> keys;
  for (char key_char : name_string) {
    int key = key_char - '0';
    if (key < 0 || key > 9 || name_keys[key] == 0)
      break;
    keys.push_back(name_keys[key]);
  }

  if (keys.size() != name_string.size()) {
    cout << "NONE" << std::endl;
    return 0;
  }

  size_t max_i = 1;
  for (size_t i = 0; i < keys.size(); ++i)
    max_i *= 3;

  bool found_name = false;
  for (size_t i = 0; i < max_i; ++i) {
    size_t index = i;

    std::vector<char> name_chars(keys.size());
    for (int j = keys.size() - 1; j >= 0; --j) {
      name_chars[j] = keys[j][index % 3];
      index /= 3;
    }

    std::string name(name_chars.begin(), name_chars.end());
    if (names.count(name)) {
      cout << name << std::endl;
      found_name = true;
    }
  }

  if (!found_name)
    cout << "NONE" << std::endl;
  return 0;
}
