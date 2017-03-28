/*
PROG: beads
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct streak {
  size_t count;
  char type;

  streak(size_t count, char type) {
    this->count = count;
    this->type = type;
  }
};

int main() {
  std::ofstream cout("beads.out");
  std::ifstream cin("beads.in");

  size_t raw_size;
  std::string raw;
  cin >> raw_size >> raw;

  // compress beads with same color
  std::vector<streak> lace;
  for (size_t i = 0; i < raw_size; ++i) {
    if (!lace.empty() && lace.back().type == raw[i]) {
      lace.back().count++;
    } else {
      lace.push_back(streak(1, raw[i]));
    }
  }

  /*
  for (const streak& s : lace) {
    std::cerr << "(" << s.type << ", " << s.count << ") ";
  }
  std::cerr << std::endl;
  */

  // compress bwb and rwr
  std::vector<streak> shrunk;
  const size_t stop = lace.size() - 2;
  for (size_t i = 0; i < lace.size(); ++i) {
    char type = lace[i].type;
    if (type == 'w') {
      shrunk.push_back(lace[i]);
      continue;
    }

    size_t count = 0;
    while (i < stop && lace[i + 1].type == 'w' && lace[i + 2].type == type) {
      count += lace[i].count + lace[i + 1].count;
      i += 2;
    }
    count += lace[i].count;

    shrunk.push_back(streak(count, type));
  }
  lace.swap(shrunk);

  /*
  for (const streak& s : lace) {
    std::cerr << "(" << s.type << ", " << s.count << ") ";
  }
  std::cerr << std::endl;
  */

  if (lace.size() == 1) {  // early check needed because of pop_back()
    cout << lace.front().count << std::endl;
    return 0;
  }

  // compress same color wrapped around
  if (lace.back().type == lace.front().type) {
    lace.front().count += lace.back().count;
    lace.pop_back();
  }

  if (lace.size() == 1) {  // early check needed because of pop_back()
    cout << lace.front().count << std::endl;
    return 0;
  }

  // compress bwb and rwr wrapped around
  size_t size = lace.size();
  if (size > 2) {
    if (lace.front().type == 'w') {
      if (lace[1].type == lace.back().type) {
        lace[1].count += lace.front().count + lace.back().count;
        lace.pop_back();
        lace.erase(lace.begin());
      }
    } else if (lace.back().type == 'w') {
      if (lace.front().type == lace[size - 2].type) {
        lace.front().count += lace.back().count + lace[size - 2].count;
        lace.pop_back();
        lace.pop_back();
      }
    }
  }

  /*
  for (const streak& s : lace) {
    std::cerr << "(" << s.type << ", " << s.count << ") ";
  }
  std::cerr << std::endl;
  */

  // find the best cut
  size = lace.size();
  size_t max = 0;
  for (size_t i = 0; i < size; ++i) {
    size_t count = 0;
    bool saw[2] = {false, false};

    size_t j = i;
    while (count < raw_size) {
      if (lace[j].type != 'w') {
        size_t type = lace[j].type == 'r';
        if (saw[type])
          break;
        saw[type] = true;
      }
      count += lace[j].count;
      j = (j + 1) % size;
    }

    if (max < count)
      max = count;
  }

  cout << max << std::endl;
  return 0;
}
