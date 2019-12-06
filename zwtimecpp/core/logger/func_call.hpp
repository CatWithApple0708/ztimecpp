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
#include "zwtimecpp/core/utils/logger_func_parameter_format_utils.hpp"

#define ZFUNC_CALL_DEBUG(...)                                            \
  logger->debug("call {}: " FUNC_PARAMETERS_FORMAT_PATTERN(__VA_ARGS__), \
                __FUNCTION__, __VA_ARGS__);

#define ZFUNC_CALL_INFO(...)                                            \
  logger->info("call {}: " FUNC_PARAMETERS_FORMAT_PATTERN(__VA_ARGS__), \
               __FUNCTION__, __VA_ARGS__);

#define ZFUNC_CALL_ERROR(...)                                            \
  logger->error("call {}: " FUNC_PARAMETERS_FORMAT_PATTERN(__VA_ARGS__), \
                __FUNCTION__, __VA_ARGS__);

#define ZVOID "void"