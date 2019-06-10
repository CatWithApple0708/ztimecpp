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
  static int64_t durationToNs(nanoseconds ns) { return ns.count(); }

  /**
   * @brief 时间操作
   */

  static inline time_point<system_clock> addHours(
      time_point<system_clock> point, int value) {
    return point + hours(value);
  }
  static inline time_point<system_clock> addSeconds(
      time_point<system_clock> point, int value) {
    return point + seconds(value);
  }
  static inline time_point<system_clock> addMilliseconds(
      time_point<system_clock> point, int value) {
    return point + milliseconds(value);
  }
  static inline time_point<system_clock> addMicroseconds(
      time_point<system_clock> point, int value) {
    return point + microseconds(value);
  }

  static inline time_point<system_clock> addHours(int value) {
    time_point<system_clock> now = system_clock::now();
    return addHours(now, value);
  }
  static inline time_point<system_clock> addSeconds(int value) {
    time_point<system_clock> now = system_clock::now();
    return addHours(now, value);
  }
  static inline time_point<system_clock> addMilliseconds(int value) {
    time_point<system_clock> now = system_clock::now();
    return addHours(now, value);
  }
  static inline time_point<system_clock> addMicroseconds(int value) {
    time_point<system_clock> now = system_clock::now();
    return addHours(now, value);
  }
  /**
   * @brief 计算流逝时间
   */

  static int64_t elapsedTimeS(time_point<system_clock> begin) {
    return durationToS(system_clock::now() - begin);
  }
  static int64_t elapsedTimeMs(time_point<system_clock> begin) {
    return durationToMs(system_clock::now() - begin);
  }
  static int64_t elapsedTimeUs(time_point<system_clock> begin) {
    return durationToUs(system_clock::now() - begin);
  }

  static int64_t elapsedTimeS(int64_t ms) {
    return (getMilliseconds() - ms) / 1000;
  }
  static int64_t elapsedTimeMs(int64_t ms) { return (getMilliseconds() - ms); }
  static int64_t elapsedTimeUs(int64_t ms) {
    return (getMilliseconds() - ms) / 1000 / 1000;
  }

  /**
   * @brief 倒计时　还剩多久
   *
   */
  static int64_t countdownTimeS(time_point<system_clock> endtime) {
    return durationToS(endtime - system_clock::now());
  }
  static int64_t countdownTimeMs(time_point<system_clock> endtime) {
    return durationToMs(endtime - system_clock::now());
  }
  static int64_t countdownTimeUs(time_point<system_clock> endtime) {
    return durationToUs(endtime - system_clock::now());
  }
  static int64_t countdownTimeNs(time_point<system_clock> endtime) {
    return durationToNs(endtime - system_clock::now());
  }
};
};  // namespace core
}  // namespace zwsd
