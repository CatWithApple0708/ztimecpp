#pragma once
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "zwtimecpp/core/logger/logger.hpp"
#include "zwtimecpp/core/utils/run_when_exit.hpp"
#include "zwtimecpp/core/utils/time_utils.hpp"
namespace zwsd {
namespace core {
using namespace std;
using namespace chrono;
class ZbenchMark {
 public:
  ZbenchMark(string name) : name(name) { s = TimeUtilsSteadyClock::now(); }
  string name;
  chrono::time_point<steady_clock> s;
  int32_t delay;

 private:
};

#define ZBENCH_MARK_START(logger, level)                                \
  vector<core::ZbenchMark> ___markVectors;                              \
  RunWhenExit __bench_mark_start_run_when_exit([&]() {                  \
    string report;                                                      \
    for (auto& var : ___markVectors) {                                  \
      if (report.empty()) {                                             \
        report = fmt::format("{}:{}ms ", var.name, var.delay);            \
      } else {                                                          \
        report = fmt::format("{} {}:{}ms ", report, var.name, var.delay); \
      }                                                                 \
    }                                                                   \
    logger->log(level, "benchmarkReport: {}", report);                                   \
  });

#define ZBENCH_MARK(name)                                            \
  ZbenchMark mark(#name);                                            \
  RunWhenExit __bench_mark_run_when_exit([&___markVectors, &mark]() { \
    mark.delay = TimeUtilsSteadyClock::elapsedTimeMs(mark.s);        \
    ___markVectors.push_back(mark);                                  \
  });
}
}  // namespace zwsd