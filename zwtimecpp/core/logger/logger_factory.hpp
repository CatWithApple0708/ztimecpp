//
// Created by zhaohe on 19-5-31.
//

#pragma once
#include "spdlog/spdlog.h"

#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "zwtimecpp/core/logger/spdlog/spdlog.h"
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
using namespace spdlog;
class SpdLoggerFactory {
  public:

//   #define SPDLOG_LEVEL_TRACE 0
// #define SPDLOG_LEVEL_DEBUG 1
// #define SPDLOG_LEVEL_INFO 2
// #define SPDLOG_LEVEL_WARN 3
// #define SPDLOG_LEVEL_ERROR 4
// #define SPDLOG_LEVEL_CRITICAL 5
    static shared_ptr<logger> createLogger(string loggerName) {
        if (get("root")) {
            return get("root");
        } else {
            mkdirIfNotExist("logs/");
            auto error = make_shared<sinks::daily_file_sink_mt>("logs/error", 0, 1);
            error->set_level(level::err);
            auto info = make_shared<sinks::daily_file_sink_mt>("logs/info", 0, 1);
            info->set_level(level::info);
            auto debug = make_shared<sinks::daily_file_sink_mt>("logs/debug", 0, 1);
            debug->set_level(level::debug);
            auto trace = make_shared<sinks::daily_file_sink_mt>("logs/trace", 0, 1);
            trace->set_level(level::trace);

            auto rootLogger = make_shared<logger>("root", sinks_init_list{error, info, debug});
            register_logger(rootLogger);
            return rootLogger;
        }
    }

  private:
    static bool mkdirIfNotExist(const string &path) {
        string::size_type sepPos = path.find_last_of("/");
        if (sepPos == string::npos) {
            return false;
        }

        string dirPath = path.substr(0, sepPos);
        if (exist(dirPath)) {
            return true;
        }

        int ret = mkdir(dirPath.c_str(), S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

        return 0 == ret ? true : false;
    }
    static bool exist(const string &path) {
        struct stat statInfo;

        if (stat(path.c_str(), &statInfo) == 0) {
            return true;
        }

        return false;
    }
};
} // namespace core

} // namespace zwsd
