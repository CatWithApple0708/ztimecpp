//
// Created by zhaohe on 19-6-6.
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
#include "zwtimecpp/core/event_priority.hpp"

namespace zwsd {
namespace core {
using namespace std;
class CoreConstant {
 public:
  static constexpr const char* BenckmarkRootDir = "benchmarkLog";
  static constexpr int MaxBenckmarkFileNum =
      100;  //同一个benchmark最多创建的文件数

  template <class T>
  static T value(T value) {
    return value;
  }
};
}  // namespace core

#define DEFAULT_EVENT_PRIORITY (EventPriority_t::Medium)

}  // namespace zwsd
