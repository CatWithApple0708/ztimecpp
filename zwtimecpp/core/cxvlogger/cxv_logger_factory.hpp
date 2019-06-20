//
// Created by zhaohe on 19-6-20.
//

#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "zwtimecpp/core/logger/logger.hpp"
// class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class
// T9,class T10

namespace zwsd {
using namespace std;
/**
 * @brief
 * usage
 *
 * CxvLoggerFactory::Instance().setEnable();
 * cxvLogger_t cxvlogger =
 * CxvLoggerFactory::Instance().createCxvLogger("loggername");
 *
 * cxvlogger->record(1,2,3,4,"hellp",value);
 *
 */
class CxvLogger {
  unique_ptr<ofstream> ofile;
  bool enable = false;

 public:
  CxvLogger(string name, bool enable);
  template <class T1>
  void record(T1 v1) {
    if (!enable) return;
    return record_internal(fmt::format("{}", v1));
  }
  template <class T1, class T2>
  void record(T1 v1, T2 v2) {
    if (!enable) return;
    return record_internal(fmt::format("{},{}", v1, v2));
  }
  template <class T1, class T2, class T3>
  void record(T1 v1, T2 v2, T3 v3) {
    if (!enable) return;
    return record_internal(fmt::format("{},{},{}", v1, v2, v3));
  }
  template <class T1, class T2, class T3, class T4>
  void record(T1 v1, T2 v2, T3 v3, T4 v4) {
    if (!enable) return;
    return record_internal(fmt::format("{},{},{},{}", v1, v2, v3, v4));
  }
  template <class T1, class T2, class T3, class T4, class T5>
  void record(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5) {
    if (!enable) return;
    return record_internal(fmt::format("{},{},{},{},{}", v1, v2, v3, v4, v5));
  }
  template <class T1, class T2, class T3, class T4, class T5, class T6>
  void record(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6) {
    if (!enable) return;
    return record_internal(
        fmt::format("{},{},{},{},{},{}", v1, v2, v3, v4, v5, v6));
  }
  template <class T1, class T2, class T3, class T4, class T5, class T6,
            class T7>
  void record(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7) {
    if (!enable) return;
    return record_internal(
        fmt::format("{},{},{},{},{},{},{}", v1, v2, v3, v4, v5, v6, v7));
  }
  template <class T1, class T2, class T3, class T4, class T5, class T6,
            class T7, class T8>
  void record(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8) {
    if (!enable) return;
    return record_internal(
        fmt::format("{},{},{},{},{},{},{},{}", v1, v2, v3, v4, v5, v6, v7, v8));
  }
  template <class T1, class T2, class T3, class T4, class T5, class T6,
            class T7, class T8, class T9>
  void record(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9) {
    if (!enable) return;
    return record_internal(fmt::format("{},{},{},{},{},{},{},{},{}", v1, v2, v3,
                                       v4, v5, v6, v7, v8, v9));
  }
  template <class T1, class T2, class T3, class T4, class T5, class T6,
            class T7, class T8, class T9, class T10>
  void record(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
              T10 v10) {
    if (!enable) return;
    return record_internal(fmt::format("{},{},{},{},{},{},{},{},{},{}", v1, v2,
                                       v3, v4, v5, v6, v7, v8, v9, v10));
  }

  template <class T1, class T2, class T3, class T4, class T5, class T6,
            class T7, class T8, class T9, class T10, class T11>
  void record(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
              T10 v10, T11 v11) {
    if (!enable) return;
    return record_internal(fmt::format("{},{},{},{},{},{},{},{},{},{},{}", v1, v2,
                                       v3, v4, v5, v6, v7, v8, v9, v10, v11));
  }

  template <class T1, class T2, class T3, class T4, class T5, class T6,
            class T7, class T8, class T9, class T10, class T11, class T12>
  void record(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
              T10 v10, T11 v11, T12 v12) {
    if (!enable) return;
    return record_internal(fmt::format("{},{},{},{},{},{},{},{},{},{},{},{}", v1,
                                       v2, v3, v4, v5, v6, v7, v8, v9, v10, v11,
                                       v12));
  }

 private:
  void record_internal(const string& oneRecord);
};

typedef shared_ptr<CxvLogger> cxvLogger_t;

class CxvLoggerFactory {
  ENABLE_LOGGER(CxvLoggerFactory);
  bool enable = false;
  string savePath;

 private:
  CxvLoggerFactory() {}

 public:
  static CxvLoggerFactory& Instance() {
    static CxvLoggerFactory value;
    return value;
  }
  void setEnable() { enable = true; }
  void setSavePath(string path) { savePath = path; }
  cxvLogger_t createCxvLogger(string name);
};
}  // namespace zwsd
