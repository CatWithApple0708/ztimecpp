//
// Created by zhaohe on 19-6-23.
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
#include "zwtimecpp/core/logger/logger.hpp"
#include "zwtimecpp/core/utils/backward_helper.hpp"
namespace zwsd {
namespace core {
using namespace std;
/*
 */
static void inline FatallError(logger_t logger, string info) {
  string stackInfo = getStackInfo();
  logger->critical("FatailError :{}\n{}", info, stackInfo);
  spdlog::drop_all();
  _exit(0);
};
}  // namespace core
}  // namespace zwsd
