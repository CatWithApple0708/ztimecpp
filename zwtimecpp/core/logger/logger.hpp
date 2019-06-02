//
// Created by zhaohe on 19-5-31.
//

#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "zwtimecpp/core/logger/logger_factory.hpp"

namespace zwsd {
}  // namespace zwsd
#ifndef CHECK
#define CHECK(logger, exptr, ...)                              \
  if (!(exptr)) {                                              \
    logger->critical("check [" #exptr "] fail. " __VA_ARGS__); \
    exit(-1);                                                  \
  }

#endif

#ifndef DCHECK
#define DCHECK CHECK
#endif