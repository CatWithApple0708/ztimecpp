//
// Created by zhaohe on 19-5-31.
//

#pragma once
#include "spdlog/spdlog.h"

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "zwtimecpp/core/logger/spdlog/spdlog.h"

namespace zwsd {
namespace core {
using namespace std;
using namespace spdlog;
typedef shared_ptr<logger> logger_t;

#define ENABLE_LOGGER(loggerName) \
  zwsd::core::logger_t logger =   \
      zwsd::core::SpdLoggerFactory::createLogger(#loggerName);

#define CREATE_LOGGER(loggerName) \
  zwsd::core::SpdLoggerFactory::createLogger(#loggerName)

#define ENABLE_LOGGER_STATIC(loggerName) \
  static zwsd::core::logger_t logger =   \
      zwsd::core::SpdLoggerFactory::createLogger(#loggerName);

class SpdLoggerFactory {
 public:
  static shared_ptr<logger> createLogger(string loggerName);
 private:
  static void parseSphLogConfig(string path);
};
}  // namespace core
}  // namespace zwsd