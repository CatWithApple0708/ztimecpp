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
#include "zwtimecpp/core/utils/utc/utctime.hpp"

namespace zwsd {
namespace core {
using namespace std;
using namespace chrono;


template <class T>
class __TimeUtils {
 public:
  static time_point<T> zero() {
    return time_point<T>(nanoseconds(0));
  }

  static time_point<T> now() { return move(T::now()); }

  static int64_t getus() {
    return duration_cast<microseconds>(T::now().time_since_epoch())
        .count();
  }

  static int64_t gets() {
    return duration_cast<seconds>(T::now().time_since_epoch())
        .count();
  }
  static int64_t getms() {
    return duration_cast<milliseconds>(T::now().time_since_epoch())
        .count();
  }
  static int64_t geth() {
    return duration_cast<hours>(T::now().time_since_epoch()).count();
  }

  static int64_t tpToMs(time_point<T> t) {
    return duration_cast<milliseconds>(t.time_since_epoch()).count();
  }

  static int64_t tpToUs(time_point<T> t) {
    return duration_cast<microseconds>(t.time_since_epoch()).count();
  }

  static int64_t tpToS(time_point<T> t) {
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

  static inline time_point<T> msToTp(int64_t ms) {
    time_point<T> tp = time_point<T>(milliseconds(ms));
    return move(tp);
  }

  /**
   * @brief 时间操作
   */
  static inline time_point<T> addh(time_point<T> point,
                                              int value) {
    return point + hours(value);
  }
  static inline time_point<T> adds(time_point<T> point,
                                              int value) {
    return point + seconds(value);
  }
  static inline time_point<T> addms(time_point<T> point,
                                               int value) {
    return point + milliseconds(value);
  }
  static inline time_point<T> addus(time_point<T> point,
                                               int value) {
    return point + microseconds(value);
  }

  static inline time_point<T> addh(int value) {
    time_point<T> now = T::now();
    return addh(now, value);
  }
  static inline time_point<T> adds(int value) {
    time_point<T> now = T::now();
    return adds(now, value);
  }
  static inline time_point<T> addms(int value) {
    time_point<T> now = T::now();
    return addms(now, value);
  }
  static inline time_point<T> addus(int value) {
    time_point<T> now = T::now();
    return addus(now, value);
  }

  static inline int64_t ms2us(int64_t ms) { return ms * 1000; }

  /**
   * @brief 计算流逝时间
   */

  static int64_t elapsedTimeS(time_point<T> begin) {
    return dToS(T::now() - begin);
  }
  static int64_t elapsedTimeMs(time_point<T> begin) {
    return dToMs(T::now() - begin);
  }
  static int64_t elapsedTimeUs(time_point<T> begin) {
    return dToUs(T::now() - begin);
  }

  static int64_t elapsedTimeS(int64_t ms) { return (getms() - ms) / 1000; }
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
  static int64_t countdownTimeS(time_point<T> endtime) {
    return dToS(endtime - T::now());
  }
  static int64_t countdownTimeMs(time_point<T> endtime) {
    return dToMs(endtime - T::now());
  }
  static int64_t countdownTimeUs(time_point<T> endtime) {
    return dToUs(endtime - T::now());
  }
  static int64_t countdownTimeNs(time_point<T> endtime) {
    return dToNs(endtime - T::now());
  }

 public:
  static UTCTime getBeijingTime() {
    std::tm now = UTCTime().get_tm();
    std::tm* beijingTime = utctime::tm_increment_hour(&now, 8);
    return UTCTime(*beijingTime);
  };
  static UTCTime getUTCTime() { return UTCTime(); };
  static UTCTime getLocalTime() {
    time_t tt =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm cur;
    struct tm* ptminfo = localtime_r(&tt, &cur);
    return UTCTime(*ptminfo);
  }
};

typedef __TimeUtils<system_clock> TimeUtils;
typedef __TimeUtils<steady_clock> TimeUtilsSteadyClock;

};  // namespace core
}  // namespace zwsd
