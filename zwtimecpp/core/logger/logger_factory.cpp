//
// Created by zhaohe on 19-5-31.
//

#include "logger_factory.hpp"
#include <fstream>
#include <iostream>
#include <mutex>
#include "zwtimecpp/core/utils/nlohmann/json.hpp"

#include <mutex>
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "zwtimecpp/core/utils/compliler.h"
#include "default_logger_config.hpp"
using namespace std;
using namespace zwsd;
using namespace core;
using namespace nlohmann;
using namespace spdlog;

const static string kRootLogerName = "root";
const static char* kSpdDefaultConfigPaths[] = {"spd_logger_cfg.json"};

// const string WEAK spdLoggerConfig() { return ""; }

// const static string kDefaultLoggerBeforeConfig = "DefaultLoggerBeforeConfig";

//     {
//         "name": "LoggerName",
//         "level": 2,
//         "type":"daily_logger_mt",
//         "filename":"fileName",
//         "hour":0,
//         "minute":0,
//         "truncate":false
//     }

// 1. 没设置type,统统被当做logger处理
// 2. 所有的logger,sink loggerAndSink,name都不能重复
// 3.

/**
 * @brief
 *loggerSupportList:
 *
 *-->: daily_logger_mt
 *-->: basic_logger_mt
 *-->: logger
 *-->: daily_file_sink_mt
 *-->: stderr_color_sink_mt
 *
 */

#define ASSININ_VALUE(value) \
  if (config_item.key() == #value) item.at(#value).get_to(config.value);

template <class type>
type tryGet(json j, string value_name, type defaultValue) {
  try {
    type value = j.at(value_name).get<type>();
    return value;
  } catch (const std::exception& e) {
    return defaultValue;
  }
}

static bool exist(const string& path) {
  struct stat statInfo;
  if (stat(path.c_str(), &statInfo) == 0) {
    return true;
  }
  return false;
}
static bool mkdirIfNotExist(const string& path) {
  string::size_type sepPos = path.find_last_of("/");
  if (sepPos == string::npos) {
    return false;
  }
  string dirPath = path.substr(0, sepPos);
  if (exist(dirPath)) {
    return true;
  }
  int ret =
      mkdir(dirPath.c_str(), S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

  return 0 == ret ? true : false;
}

class LoggerAndSinks {
 public:
  string loggerName;
  set<string> sinkNames;
};

static map<string, sink_ptr> s_sinks = {};
static map<string, shared_ptr<logger>> s_loggers = {};
static set<shared_ptr<LoggerAndSinks>> s_loggerAndSinks = {};

static void insertLogger(shared_ptr<logger> var_logger) {
  if (s_loggers.find(var_logger->name()) == s_loggers.end()) {
    s_loggers[var_logger->name()] = var_logger;
  } else {
    spdlog::critical("Add the logger {} fail", var_logger->name());
    exit(-1);
  }
};

static void insertSink(string name, sink_ptr sink) {
  if (s_sinks.find(name) == s_sinks.end()) {
    s_sinks[name] = sink;
  } else {
    spdlog::critical("Add the sink {} fail", name);
    exit(-1);
  }
};

static level::level_enum to_level(int value) {
  switch (value) {
    case SPDLOG_LEVEL_TRACE:
      return level::trace;
    case SPDLOG_LEVEL_DEBUG:
      return level::debug;
    case SPDLOG_LEVEL_INFO:
      return level::info;
    case SPDLOG_LEVEL_WARN:
      return level::warn;
    case SPDLOG_LEVEL_ERROR:
      return level::err;
    case SPDLOG_LEVEL_CRITICAL:
      return level::critical;
    default:
      spdlog::critical("level is out of range {} level must in [{},{}]", value,
                       SPDLOG_LEVEL_TRACE, SPDLOG_LEVEL_CRITICAL);
      exit(-1);
      break;
  }
  return level::info;
}

// #define GET(type,value,error_msg,...)
#define TRY_GET(type, value_name, default_value) \
  type value_name = tryGet<type>(j, #value_name, default_value)
#define GET(T, value_name) T value_name = j.at(#value_name).get<T>();

static void logger_common_config(logger_t var_logger, json j) {
  TRY_GET(int, level, 2);
  TRY_GET(string, pattern, "");
  TRY_GET(set<string>, sinks, {});

  var_logger->set_level(to_level(level));
  if (!pattern.empty()) var_logger->set_pattern(pattern);
  if (!sinks.empty()) {
    shared_ptr<LoggerAndSinks> las(new LoggerAndSinks());
    las->loggerName = var_logger->name();
    las->sinkNames = sinks;
    s_loggerAndSinks.insert(las);
  }
}

static void sink_common_config(sink_ptr sink, json j) {
  TRY_GET(int, level, 0);
  TRY_GET(string, pattern, "");
  TRY_GET(set<string>, sinks, {});
  sink->set_level(to_level(level));
  if (!pattern.empty()) sink->set_pattern(pattern);
}

/**
 * logger-----------------------------------------------------------------------------------------------------
 */
static bool c_daily_logger_mt(json j) {
  try {
    string type = j.at("type").get<string>();
    if (type == "daily_logger_mt") {
      GET(string, name);
      GET(string, filename);
      mkdirIfNotExist(filename);

      TRY_GET(int, hour, 0);
      TRY_GET(int, minute, 0);
      TRY_GET(bool, truncate, false);

      auto var_logger =
          spdlog::daily_logger_mt(name, filename, hour, minute, truncate);
      logger_common_config(var_logger, j);
      insertLogger(var_logger);
      return true;
    } else {
      return false;
    }
  } catch (const std::exception& e) {
    spdlog::critical("c_daily_logger_mt fail {}  reason {}", j.dump(1),
                     e.what());
    exit(-1);
  }
};

static bool c_basic_logger_mt(json j) {
  try {
    string type = j.at("type").get<string>();
    if (type == "basic_logger_mt") {
      GET(string, name);
      GET(string, filename);
      mkdirIfNotExist(filename);
      auto var_logger = spdlog::basic_logger_mt(name, filename);
      logger_common_config(var_logger, j);
      insertLogger(var_logger);
      return true;
    } else {
      return false;
    }
  } catch (const std::exception& e) {
    spdlog::critical("c_basic_logger_mt fail {}  reason {}", j.dump(1),
                     e.what());
    exit(-1);
  }
};

static bool c_logger(json j) {
  try {
    string type = j.at("type").get<string>();
    if (type == "logger") {
      GET(string, name);
      GET(set<string>, sinks);
      auto var_logger = make_shared<logger>(name, sinks_init_list{});
      if (sinks.empty()) {
        spdlog::critical("c_logger fail {}  reason {}", j.dump(1),
                         "Not set sink");
        exit(-1);
      }

      logger_common_config(var_logger, j);
      insertLogger(var_logger);
      return true;
    } else {
      return false;
    }
  } catch (const std::exception& e) {
    spdlog::critical("c_logger fail {}  reason {}", j.dump(1), e.what());
    exit(-1);
  }
};

/**
 * sinks-----------------------------------------------------------------------------------------------------
 */
static bool c_daily_file_sink_mt(json j) {
  try {
    string type = j.at("type").get<string>();
    if (type == "daily_file_sink_mt") {
      GET(string, name);
      GET(string, filename);
      mkdirIfNotExist(filename);
      TRY_GET(int, hour, 0);
      TRY_GET(int, minute, 0);
      TRY_GET(bool, truncate, false);

      auto sink = make_shared<sinks::daily_file_sink_mt>(filename, hour, minute,
                                                         truncate);

      sink_common_config(sink, j);
      insertSink(name, sink);
      return true;
    } else {
      return false;
    }
  } catch (const std::exception& e) {
    spdlog::critical("c_daily_file_sink_mt fail {}  reason {}", j.dump(1),
                     e.what());
    exit(-1);
  }
};

static bool c_stderr_color_sink_mt(json j) {
  try {
    string type = j.at("type").get<string>();
    if (type == "stderr_color_sink_mt") {
      GET(string, name);
      auto sink = make_shared<sinks::stderr_color_sink_mt>();
      sink_common_config(sink, j);
      insertSink(name, sink);
      return true;
    } else {
      return false;
    }
  } catch (const std::exception& e) {
    spdlog::critical("c stderr_color_sink_mt fail {}  reason {}", j.dump(1),
                     e.what());
    exit(-1);
  }
};

/**
 * default_root_logger-----------------------------------------------------------------------------------------------------
 */
static logger_t createRootLogger() {
  auto stdoutsink = make_shared<sinks::stderr_color_sink_mt>();
  stdoutsink->set_level(level::debug);
  auto rootLogger =
      make_shared<logger>(kRootLogerName, sinks_init_list{stdoutsink});
  rootLogger->set_level(level::info);
  return rootLogger;
}
/**
 * @brief
 */
/**
 * @brief 当使用 daily_logger_mt时候会自动注册logger, 而使用make_shared<logger>
 * 则不会自动注册logger
 * @param var_logger
 */
static void myRegLogger(logger_t var_logger) {
  if (var_logger->name() == kRootLogerName) {
    spdlog::set_default_logger(var_logger);
  }

  if (!get(var_logger->name())) {
    register_logger(var_logger);
  }
  if (!get(var_logger->name())) {
    spdlog::critical("reg root logger fail {}");
    exit(-1);
  }

}

static void __parseSphLogConfig(json var) {
  if (c_daily_logger_mt(var)) {
  } else if (c_basic_logger_mt(var)) {
  } else if (c_daily_file_sink_mt(var)) {
  } else if (c_logger(var)) {
  } else if (c_stderr_color_sink_mt(var)) {
  } else {
    spdlog::critical("no such type {}", var.dump());
    exit(-1);
  }
}

static logger_t createLoggerWithoutType(json j){
  TRY_GET(int, level, 2);
  GET(string, name);
  TRY_GET(string, pattern, "");
  auto rootLogger = get(kRootLogerName);
  if (!rootLogger) {
    spdlog::critical("func: createLoggerWithoutType,can't find rootLogger");
    exit(-1);
  }
  auto newLogger = rootLogger->clone(name);
  newLogger->set_level(to_level(level));
  if (!pattern.empty()) newLogger->set_pattern(pattern);
  return newLogger;
}

/**
 * @brief
 *
 * 构造logger思路
 * 1. 首先找到所有定义了type了的logger和sink
 * 2. 绑定所有的logger和对应的sink
 * 3. 查看是否创建rootLogger,没有则创建rootLogger
 * 4. 遍历所有没有定义type的logger,继承于rootLogger,并为其设置level
 * @param path
 */
void core::SpdLoggerFactory::parseSphLogConfig(string path) {
  try {
    //这里必须清空，因为这个方法可能在main函数之前启动，所以数量可能未初始化
    s_sinks.clear();
    s_loggers.clear();
    s_loggerAndSinks.clear();

    fstream infile(path, ios::binary | ios::in);
    stringstream sstream;
    sstream << infile.rdbuf();
    infile.close();

    string jsonStr(sstream.str());
    sstream.clear();

    json configjson = json::parse(jsonStr);
    for (auto& j : configjson) {
      TRY_GET(string, type, "");
      if (!type.empty()) {
        __parseSphLogConfig(j);
      }
    }

    //组装logger and sink
    for (auto& las : s_loggerAndSinks) {
      logger_t logger = s_loggers[las->loggerName];
      if (logger == nullptr) {
        spdlog::critical("can't find  logger", las->loggerName);
        exit(-1);
      }
      set<sink_ptr> sinks;
      for (auto& sinkname : las->sinkNames) {
        auto result = s_sinks.find(sinkname);
        if (result == s_sinks.end()) {
          spdlog::critical("can't find  sink {} ??", sinkname);
          exit(-1);
        }
        sinks.insert(result->second);
      }
      for (auto& sink : sinks) logger->sinks().push_back(sink);
    }
    for (auto& var : s_loggers) myRegLogger(var.second);

    //如果没有rootLogger,构造rootLogger
    if (!get(kRootLogerName)) {
      for (auto& j : configjson) {
        GET(string, name);
        TRY_GET(string, type, "");
        if (name == kRootLogerName) {
          if (type.empty()) {
            TRY_GET(int, level, 2);
            TRY_GET(string, pattern, "");
            auto rootLogger = createRootLogger();
            rootLogger->set_level(to_level(level));
            if (!pattern.empty()) rootLogger->set_pattern(pattern);
            myRegLogger(rootLogger);
          } else {
            spdlog::critical("shouldn't go here");
            exit(-1);
          }
          break;
        }
      }
    }
    //如果依然没有构造rootLogger则构造默认logger
    if (!get(kRootLogerName)) myRegLogger(createRootLogger());

    //构造没有type的logger
    for (auto& j : configjson) {
      TRY_GET(string, type, "");
      GET(string, name);
      if (type.empty() && name != kRootLogerName) {
        auto newlogger = createLoggerWithoutType(j);
        myRegLogger(newlogger);
      }
    }

    spdlog::info("Logger initialize ok");
  } catch (const exception& e) {
    spdlog::critical("parse logger config fail {}", e.what());
    exit(-1);
  }
}


static string getConfigFilePath() {
  if (spdLoggerConfig) {
    if (exist(spdLoggerConfig())) {
      return spdLoggerConfig();
    } else {
      spdlog::warn("can't find spdLoggerConfig file {}", spdLoggerConfig());
    }
  }
  for (auto var : kSpdDefaultConfigPaths) {
    if (exist(var)) {
      return var;
    }
  }
  return "";
}

class MonitoringSpdLoggerConfigTask {
  unique_ptr<thread> wthread;

 public:
  MonitoringSpdLoggerConfigTask() {
    wthread.reset(new thread([]() {

    }));
  }
  ~MonitoringSpdLoggerConfigTask() { wthread->join(); }
};

static unique_ptr<MonitoringSpdLoggerConfigTask> spdMonitoringtask;

void SpdLoggerFactory::startMonitoringConfigFile() {
  if (!spdMonitoringtask) {
    spdMonitoringtask.reset(new MonitoringSpdLoggerConfigTask());
  }
}

shared_ptr<logger> SpdLoggerFactory::createLogger(string loggerName) {
  static std::mutex lock;
  static atomic_bool initializeLogger = {false};
  lock_guard<mutex> lock_gu(lock);

  // TODO:当使用gtest进行单元测试的时候，logger似乎会被清空，原因未知
  if (!get(kRootLogerName)) {
    initializeLogger = false;
  }

  if (!initializeLogger) {
    string configFilePath = getConfigFilePath();
    if (!configFilePath.empty() && exist(configFilePath)) {
      parseSphLogConfig(configFilePath);
    } else {
      spdlog::warn("can't find logger config file use default config");
      myRegLogger(createRootLogger());
    }
    initializeLogger = true;
  }

  logger_t ret_logger = get(loggerName);
  if (ret_logger) {
    return ret_logger;
  } else {
    logger_t rootLogger = get(kRootLogerName);
    if (!rootLogger) {
      spdlog::critical("can't find root logger ?????");
      exit(-1);
    }
    logger_t newLogger = rootLogger->clone(loggerName);
    myRegLogger(newLogger);
    return newLogger;
  }
  return nullptr;
}