//
// Created by zhaohe on 19-6-6.
//

#pragma once
#include <pthread.h>
#include <time.h>
#include <unistd.h>
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
#include "zwtimecpp/core/logger/logger.hpp"
namespace zwsd {
namespace core {
using namespace std;
using namespace chrono;
/**
 */
class Benchmark {
  string loggerFile;
  time_point<system_clock> startT;
  unique_ptr<ofstream> ofile;
  bool isEnable = false;
  // std::ofstream tv_voice_file(outfile_name, std::ios::binary |
  // std::ios::out);

 public:
  Benchmark(const string &loggerFile, bool enable = true)
      : loggerFile(loggerFile) {
    if (!enable) {
      return;
    }
    isEnable = enable;
    ofile.reset(new ofstream(loggerFile, std::ios::binary | std::ios::out));
    string result = fmt::format("start,end,duration\n");
    ofile->write(result.data(), result.size());
  }
  /**
   * 开始计时
   */
  static void start(shared_ptr<Benchmark> bm) {
    if (bm) bm->start();
  }
  /**
   * 计算时间长度，写入统计文件
   */
  static void end(shared_ptr<Benchmark> bm) {
    if (bm) bm->end();
  }

 private:
  void start() {
    if (!isEnable) return;
    startT = system_clock::now();
  };

  void end() {
    if (!isEnable) return;

    time_point<system_clock> now = system_clock::now();
    string result = fmt::format("{},{},{}\n", tpToMs(startT), tpToMs(now),
                                durationToMs(now - startT));
    ofile->write(result.data(), result.size());
  };

  static int64_t tpToMs(time_point<system_clock> t) {
    return duration_cast<milliseconds>(t.time_since_epoch()).count();
  }

  static int64_t durationToMs(nanoseconds ns) {
    return duration_cast<milliseconds>(ns).count();
  }
};
}  // namespace core
}  // namespace zwsd
