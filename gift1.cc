/*
PROG: gift1
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

int main() {
  std::ofstream cout("gift1.out");
  std::ifstream cin("gift1.in");

  int n;
  std::string line_string;
  std::getline(cin, line_string);

  std::stringstream line(line_string);
  line >> n;

  std::vector<std::string> names;
  std::unordered_map<std::string, int> balances;

  for (int i = 0; i < n; ++i) {
    std::string name;
    std::getline(cin, name);
    balances[name] = 0;
    names.push_back(name);
  }

  for (int i = 0; i < n; ++i) {
    std::string giver;
    std::getline(cin, giver);

    std::getline(cin, line_string);
    line = std::stringstream(line_string);

    int sum, receiver_count;
    line >> sum >> receiver_count;

    int transfer;
    if (receiver_count == 0) {
      transfer = 0;
      balances[giver] += sum;
    } else {
      transfer = (sum / receiver_count);
      balances[giver] += sum % receiver_count - sum;
    }

    for (int j = 0; j < receiver_count; ++j) {
      std::string receiver;
      std::getline(cin, receiver);

      balances[receiver] += transfer;
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << names[i] << " " << balances[names[i]] << std::endl;
  }

  return 0;
}
