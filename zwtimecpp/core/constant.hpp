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
  //同一个benchmark最多创建的文件数
  static constexpr int MaxBenckmarkFileNum = 100;

  //最大cxv创建的日志文件数量
  static constexpr int MaxCxvLoggerFileNum = 100;
  static constexpr const char* CxvLoggerRootDir = "cvxLog";

  template <class T>
  static T value(T value) {
    return value;
  }
};
}  // namespace core

#define DEFAULT_EVENT_PRIORITY (EventPriority_t::Medium)

}  // namespace zwsd
