/*
PROG: transform
LANG: C++11
*/

#include <cstring>
#include <fstream>
#include <memory>

struct board {
  char data[16][16];
  size_t size;

  board() {
    std::memset(data, 0, sizeof(data));
    size = 0;
  }

  bool operator ==(const board& other) const {
    return size == other.size &&
        std::memcmp(data, other.data, sizeof(data)) == 0;
  }

  board& operator=(const board& other) {
    size = other.size;
    std::memcpy(data, other.data, sizeof(data));
    return *this;
  }

  void read(std::ifstream& cin, size_t size) {
    this->size = size;
    for (size_t i = 0; i < size; ++i) {
      std::string line;
      cin >> line;
      for (size_t j = 0; j < size; ++j)
        this->data[j][i] = line[j];
    }
  }

  void rotate() {
    char temp[16][16];
    std::memset(temp, 0, sizeof(temp));

    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0; j < size; ++j) {
        temp[size - 1 - j][i] = data[i][j];
      }
    }
    std::memcpy(data, temp, sizeof(data));
  }

  void reflect() {
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0, k = size - 1; j < k; ++j, --k) {
        std::swap(data[j][i], data[k][i]);
      }
    }
  }
};

board source, target;

int main() {
  std::ofstream cout("transform.out");
  std::ifstream cin("transform.in");

  int n;
  cin >> n;
  source.read(cin, n);
  target.read(cin, n);

  board rotated = source;
  for (int i = 1; i <= 3; ++i) {
    rotated.rotate();
    if (rotated == target) {
      cout << i << "\n";
      return 0;
    }
  }

  board reflected = source;
  reflected.reflect();
  if (reflected == target) {
    cout << "4\n";
    return 0;
  }
  for (int i = 1; i <= 3; ++i) {
    reflected.rotate();
    if (reflected == target) {
      cout << "5\n";
      return 0;
    }
  }

  if (source == target) {
    cout << "6\n";
    return 0;
  }

  cout << "7\n";
  return 0;
}
