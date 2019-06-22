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
#include "zwtimecpp/core/utils/time_utils.hpp"
namespace zwsd {
namespace core {
using namespace std;
using namespace chrono;
/**
 */
class Benchmark {
  class Mark {
   public:
    string name;
    int64_t hasPast;
  };

  string loggerFile;
  time_point<system_clock> startT;
  vector<Mark> marks;
  time_point<system_clock> lastSetMarkTime;
  unique_ptr<ofstream> ofile;
  bool isEnable = false;
  // std::ofstream tv_voice_file(outfile_name, std::ios::binary |
  // std::ios::out);
 public:
  class AutoCall {
    shared_ptr<Benchmark> b;

   public:
    AutoCall(shared_ptr<Benchmark> b) {
      this->b = b;
      if (b) b->start();
    }
    ~AutoCall() {
      if (b) b->end();
    }
  };

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

  static void setMark(shared_ptr<Benchmark> bm,string name) {
    if (bm) bm->setMark(name);
  }

 private:
  void start() {
    if (!isEnable) return;
    startT = system_clock::now();
    lastSetMarkTime = startT;
  };

  void end() {
    if (!isEnable) return;

    time_point<system_clock> now = system_clock::now();
    string result = fmt::format("{},{}", tpToMs(startT), tpToMs(now));
    for (auto& var : marks) {
      result.append(fmt::format(",[{}] {}", var.name, var.hasPast));
    }
    result.append(fmt::format(",[total] {}\n", durationToMs(now - startT)));
    marks.clear();
    ofile->write(result.data(), result.size());
  };

  void setMark(string mark_name){
    Mark mark;
    mark.name = mark_name;
    mark.hasPast = TimeUtils::elapsedTimeMs(lastSetMarkTime);
    lastSetMarkTime = TimeUtils::now();
    marks.push_back(move(mark));
  }

  static int64_t tpToMs(time_point<system_clock> t) {
    return duration_cast<milliseconds>(t.time_since_epoch()).count();
  }

  static int64_t durationToMs(nanoseconds ns) {
    return duration_cast<milliseconds>(ns).count();
  }
};

}  // namespace core
}  // namespace zwsd

#define BENCHMARK(benchmark) \
  zwsd::core::Benchmark::AutoCall __benchAutocall(benchmark);

#define BENCHSETMARK(benchmark, name) \
  zwsd::core::Benchmark::setMark(benchmark, #name);
