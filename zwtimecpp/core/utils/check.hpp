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

#define ZCHECK(ptr)                                                     \
  if (!(ptr)) {                                                         \
    logger->error("file: {} func: {} line: {} check fail {}", __FILE__, \
                  __FUNCTION__, __LINE__, #ptr);                        \
    exit(-1);                                                           \
  }

#define CHECK_AND_RETURN1(exptr, explain)                                   \
  if (!(exptr)) {                                                           \
    logger->error("{}:{} check {} fail.explain:{}", __FUNCTION__, __LINE__, \
                  #exptr, explain);                                         \
    return;                                                                 \
  }

#define CHECK_AND_RETURN(exptr)                                            \
  if (!(exptr)) {                                                          \
    logger->error("{}:{} check {} fail.", __FUNCTION__, __LINE__, #exptr); \
    return;                                                                \
  }
