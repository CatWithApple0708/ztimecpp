//
// Created by zhaohe on 19-7-4.
//

#pragma once
#include <atomic>
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
namespace zwsd {
namespace core {
using namespace std;
template <class T>
class Instance {
 public:
  Instance() {
    static atomic<int> createNum = {0};
    if (createNum.fetch_add(1) >= 1) {
      spdlog::critical("Class T:{} is a instance but create more one time",
                       typeid(T).name());
      _exit(-1);
    }
  }

  virtual ~Instance() {}
};
}  // namespace core
}  // namespace zwsd
