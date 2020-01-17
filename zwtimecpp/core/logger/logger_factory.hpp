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

#define ENABLE_LOGGER(loggerName)                                         \
 public:                                                                  \
  zwsd::core::logger_t logger =                                           \
      zwsd::core::SpdLoggerFactory::Instance().createLogger(#loggerName); \
                                                                          \
 private:

#define CREATE_LOGGER(loggerName) \
  zwsd::core::SpdLoggerFactory::Instance().createLogger(#loggerName)

#define GET_LOGGER(loggerName) \
  zwsd::core::SpdLoggerFactory::Instance().createLogger(#loggerName)

#define ENABLE_LOGGER_STATIC(loggerName) \
  static zwsd::core::logger_t logger =   \
      zwsd::core::SpdLoggerFactory::Instance().createLogger(#loggerName);

class SpdLoggerFactory {
  SpdLoggerFactory(){};
   std::mutex createLogger_lock;
   atomic_bool initializeLogger = {false};
   set<string> s_loggerNames;

  public:
   static SpdLoggerFactory& Instance() {
     static SpdLoggerFactory factory;
     return factory;
  }
  shared_ptr<logger> createLogger(string loggerName);
  set<string> loggerNames();

 private:
  void parseSphLogConfig(string path);
};
}  // namespace core
}  // namespace zwsd