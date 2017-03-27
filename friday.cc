/*
PROG: friday
LANG: C++11
*/

#include <array>
#include <fstream>

bool is_leap_year(int year) {
  if (year % 4 != 0)
    return false;

  if (year % 100 != 0)
    return true;

  return year % 400 == 0;
}

int month_sizes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int month_days(int month, int year) {
  if (month == 1 && is_leap_year(year)) {
    return 29;
  }
  return month_sizes[month];
}

void compute_13(int n, std::array<int, 7>& histogram) {
  int year = 1900;
  int week_day = 0;  // January 13, 1900 is a Saturday.

  histogram.fill(0);

  for (int i = 0; i < n; ++i, ++year) {
    for (int month = 0; month < 12; ++month) {
      histogram[week_day] += 1;
      week_day = (week_day + month_days(month, year)) % 7;
    }
  }
}

int main() {
  std::ofstream cout("friday.out");
  std::ifstream cin("friday.in");

  int n;
  cin >> n;

  std::array<int, 7> histogram;
  compute_13(n, histogram);

  cout << histogram[0];
  for (int i = 1; i < 7; ++i)
    cout << " " << histogram[i];
  cout << std::endl;
  return 0;
}
