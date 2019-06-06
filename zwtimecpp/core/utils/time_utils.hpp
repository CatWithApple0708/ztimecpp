//
// Created by zhaohe on 19-6-2.
//

#pragma once
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace zwsd {
namespace core {
using namespace std;
using namespace chrono;
class TimeUtils {
 public:
  static int64_t getMicroseconds() {
    return duration_cast<microseconds>(system_clock::now().time_since_epoch())
        .count();
  }

  static int64_t getSeconds() {
    return duration_cast<seconds>(system_clock::now().time_since_epoch())
        .count();
  }
  static int64_t getMilliseconds() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
        .count();
  }
  static int64_t getHours() {
    return duration_cast<hours>(system_clock::now().time_since_epoch()).count();
  }

  static int64_t tpToMs(time_point<system_clock> t) {
    return duration_cast<milliseconds>(t.time_since_epoch()).count();
  }

  static int64_t tpToUs(time_point<system_clock> t) {
    return duration_cast<microseconds>(t.time_since_epoch()).count();
  }

  static int64_t tpToS(time_point<system_clock> t) {
    return duration_cast<seconds>(t.time_since_epoch()).count();
  }

  static int64_t tpToMs(time_point<steady_clock> t) {
    return duration_cast<milliseconds>(t.time_since_epoch()).count();
  }

  static int64_t tpToUs(time_point<steady_clock> t) {
    return duration_cast<microseconds>(t.time_since_epoch()).count();
  }

  static int64_t tpToS(time_point<steady_clock> t) {
    return duration_cast<seconds>(t.time_since_epoch()).count();
  }

  static int64_t durationToMs(nanoseconds ns) {
    return duration_cast<milliseconds>(ns).count();
  }
  static int64_t durationToUs(nanoseconds ns) {
    return duration_cast<microseconds>(ns).count();
  }
  static int64_t durationToS(nanoseconds ns) {
    return duration_cast<seconds>(ns).count();
  }
};
};  // namespace core
}  // namespace zwsd
