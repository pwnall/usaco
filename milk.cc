/*
PROG: milk
LANG: C++11
*/

#include <algorithm>
#include <fstream>
#include <vector>

struct farmer {
  int price;
  int quantity;

  farmer(int price, int quantity) {
    this->price = price;
    this->quantity = quantity;
  }

  bool operator <(const farmer& other) const {
    if (price != other.price)
      return price < other.price;
    return quantity < other.quantity;
  }
};

int main() {
  std::ofstream cout("milk.out");
  std::ifstream cin("milk.in");

  int milk, farmer_count;
  cin >> milk >> farmer_count;

  std::vector<farmer> farmers;
  for (int i = 0; i < farmer_count; ++i) {
    int price, quantity;
    cin >> price >> quantity;
    farmers.push_back(farmer(price, quantity));
  }
  std::sort(farmers.begin(), farmers.end());

  int cost = 0;
  int milk_left = milk;
  for (const auto& farmer : farmers) {
    int milk_bought =
        (farmer.quantity < milk_left) ? farmer.quantity : milk_left;
    cost += farmer.price * milk_bought;
    milk_left -= milk_bought;
  }

  cout << cost << std::endl;
  return 0;
}
