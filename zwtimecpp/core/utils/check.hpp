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

#define ZCHECK(ptr)                                                          \
  if (!(ptr)) {                                                              \
    logger->error("func: {} line: {} check fail {}", __FUNCTION__, __LINE__, \
                  #ptr);                                                     \
    exit(-1);                                                                \
  }
