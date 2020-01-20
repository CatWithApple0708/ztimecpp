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
#define LOG_CONFIG_BEGIN(name) \
  {                            \
    string __logger_config__ = "\n-------------" #name "-----------\n";
#define LOG_CONFIG(value) \
  __logger_config__ += fmt::format("- " #value ":{}\n", value);
#define LOG_CONFIG_END()                                                \
  logger->info("{}\n-----------------------------", __logger_config__); \
  }
//