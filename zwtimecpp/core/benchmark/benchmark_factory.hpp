//
// Created by zhaohe on 19-6-6.
//

#pragma once
#include <dirent.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/time.h>
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
#include "zwtimecpp/core/benchmark/benchmark.hpp"
#include "zwtimecpp/core/constant.hpp"
#include "zwtimecpp/core/exception/null_expection.hpp"
#include "zwtimecpp/core/logger/logger.hpp"
#include "zwtimecpp/core/utils/file_utils.hpp"
namespace zwsd {
namespace core {
using namespace std;
typedef shared_ptr<Benchmark> benchmark_t;
class BenchmarkFactory {
  ENABLE_LOGGER(Benchmark);
  bool enable = false;
  // int maxFileSize = CoreConstant::MaxBenckmarkFileNum;
  string defaultDirPath = CoreConstant::BenckmarkRootDir;

 private:
  BenchmarkFactory(bool enable) : enable(enable) {}
  static shared_ptr<BenchmarkFactory> &instance() {
    static shared_ptr<BenchmarkFactory> value;
    return value;
  }

 public:
  shared_ptr<Benchmark> createBenchmark(string name) {
    if (!enable) return make_shared<Benchmark>(name, false);

    string logFileName = FileUtil::getRepetitionFileName(
        defaultDirPath +"/"+ name, "cxv", CoreConstant::MaxBenckmarkFileNum);
    if (logFileName.empty()) return make_shared<Benchmark>(logFileName, false);

    if (!FileUtil::makeDirIfNoExist(logFileName)) {
      logger->warn("create dir {} fail???", logFileName);
      return make_shared<Benchmark>(name, false);
    }
    return make_shared<Benchmark>(logFileName, true);
  }
 public:
  static shared_ptr<BenchmarkFactory> Instance() {
    if (instance() == nullptr)
      throw NullException(
          "BenchmarkFactory instance hasn't been initialized "
          "BenchmarkFactory::instance == nullptr");
    return instance();
  }
  static void initialize(bool enable) {
    if (instance() != nullptr)
      throw BaseException("BenchmarkFactory has been initialized");
    instance().reset(new BenchmarkFactory(enable));
  }

 private:
};
}  // namespace core
}  // namespace zwsd
