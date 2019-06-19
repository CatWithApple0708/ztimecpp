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
  static time_point<system_clock> zero() {
    return time_point<system_clock>(nanoseconds(0));
  }

  static time_point<system_clock> now() { return move(system_clock::now()); }

  static int64_t getus() {
    return duration_cast<microseconds>(system_clock::now().time_since_epoch())
        .count();
  }

  static int64_t gets() {
    return duration_cast<seconds>(system_clock::now().time_since_epoch())
        .count();
  }
  static int64_t getms() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
        .count();
  }
  static int64_t geth() {
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

  static int64_t dToMs(nanoseconds ns) {
    return duration_cast<milliseconds>(ns).count();
  }
  static int64_t dToUs(nanoseconds ns) {
    return duration_cast<microseconds>(ns).count();
  }
  static int64_t dToS(nanoseconds ns) {
    return duration_cast<seconds>(ns).count();
  }
  static int64_t dToNs(nanoseconds ns) { return ns.count(); }

  static inline time_point<system_clock> msToTp(int64_t ms) {
    time_point<system_clock> tp = time_point<system_clock>(milliseconds(ms));
    return move(tp);
  }

  

  /**
   * @brief 时间操作
   */
  static inline time_point<system_clock> addh(
      time_point<system_clock> point, int value) {
    return point + hours(value);
  }
  static inline time_point<system_clock> adds(
      time_point<system_clock> point, int value) {
    return point + seconds(value);
  }
  static inline time_point<system_clock> addms(
      time_point<system_clock> point, int value) {
    return point + milliseconds(value);
  }
  static inline time_point<system_clock> addus(
      time_point<system_clock> point, int value) {
    return point + microseconds(value);
  }

  static inline time_point<system_clock> addh(int value) {
    time_point<system_clock> now = system_clock::now();
    return addh(now, value);
  }
  static inline time_point<system_clock> adds(int value) {
    time_point<system_clock> now = system_clock::now();
    return adds(now, value);
  }
  static inline time_point<system_clock> addms(int value) {
    time_point<system_clock> now = system_clock::now();
    return addms(now, value);
  }
  static inline time_point<system_clock> addus(int value) {
    time_point<system_clock> now = system_clock::now();
    return addus(now, value);
  }

  static inline int64_t ms2us(int64_t ms) { return ms * 1000; }

  /**
   * @brief 计算流逝时间
   */

  static int64_t elapsedTimeS(time_point<system_clock> begin) {
    return dToS(system_clock::now() - begin);
  }
  static int64_t elapsedTimeMs(time_point<system_clock> begin) {
    return dToMs(system_clock::now() - begin);
  }
  static int64_t elapsedTimeUs(time_point<system_clock> begin) {
    return dToUs(system_clock::now() - begin);
  }

  static int64_t elapsedTimeS(int64_t ms) {
    return (getms() - ms) / 1000;
  }
  static int64_t inline elapsedTimeMs(int64_t ms) { return (getms() - ms); }
  static int64_t inline elapsedTimeMs(int64_t now, int64_t ms) {
    return (now - ms);
  }
  static int64_t inline elapsedTimeUs(int64_t ms) {
    return (getms() - ms) / 1000 / 1000;
  }

  /**
   * @brief 倒计时　还剩多久
   *
   */
  static int64_t countdownTimeS(time_point<system_clock> endtime) {
    return dToS(endtime - system_clock::now());
  }
  static int64_t countdownTimeMs(time_point<system_clock> endtime) {
    return dToMs(endtime - system_clock::now());
  }
  static int64_t countdownTimeUs(time_point<system_clock> endtime) {
    return dToUs(endtime - system_clock::now());
  }
  static int64_t countdownTimeNs(time_point<system_clock> endtime) {
    return dToNs(endtime - system_clock::now());
  }
};
};  // namespace core
}  // namespace zwsd
