/*
PROG: milk2
LANG: C++11
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

struct event {
  int time;
  bool start;

  event(int time, bool start) {
    this->time = time;
    this->start = start;
  }

  bool operator <(const event& other) const {
    if (this->time != other.time)
      return this->time < other.time;

    return other.start < this->start;
  }
};

int main() {
  std::ofstream cout("milk2.out");
  std::ifstream cin("milk2.in");

  size_t n;
  cin >> n;

  std::vector<event> events;
  for (size_t i = 0; i < n; ++i) {
    int start_time, end_time;
    cin >> start_time >> end_time;
    events.push_back(event(start_time, true));
    events.push_back(event(end_time, false));
  }
  std::sort(events.begin(), events.end());

  /*
  for (const auto& event : events) {
    std::cerr << "(" << event.time << ", " << event.start << ") ";
  }
  std::cerr << std::endl;
  */

  int max_times[2] = {0, 0};  // idle, active
  int times[2] = {0, 0};
  int last_time = events[0].time;
  size_t count = 0;
  for (const auto& event : events) {
    int delta = event.time - last_time;
    last_time = event.time;

    size_t index = (count > 0) ? 1 : 0;
    times[index] += delta;
    times[1 - index] = 0;
    if (max_times[index] < times[index])
      max_times[index] = times[index];

    if (event.start) {
      ++count;
    } else {
      --count;
    }
  }

  cout << max_times[1] << " " << max_times[0] << std::endl;
  return 0;
}
