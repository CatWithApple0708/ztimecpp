//
// Created by zhaohe on 19-5-21.
//

#pragma once
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "zwtimecpp/core/base/interlog/simple_logger.hpp"
#include "zwtimecpp/core/base/object.hpp"
#include "zwtimecpp/core/exception/base_exception.hpp"
namespace zwsd {
namespace core {
using namespace std;
using namespace chrono;

class BaseEvent {
  shared_ptr<Object> object;
  time_point<system_clock> timePoint = system_clock::now();

 public:
  /**
   * @param object object != null 如果等于null 则抛出Null异常
   */
  BaseEvent(shared_ptr<Object> object) { this->object = object; }
  BaseEvent() {}

  /**
   * @tparam T {chrono::milliseconds,chrono::seconds,chrono::microseconds,chrono::hours}
   * @return
   */
  template<class T>
  int64_t getCreateTime() {
	return duration_cast<T>(timePoint.time_since_epoch()).count();
  }
  /**
   *
   * @tparam T {chrono::milliseconds,chrono::seconds,chrono::microseconds,chrono::hours}
   * @return
   */
  template<class T>
  int64_t getHasPassTime() {
	return duration_cast<T>(system_clock::now() - timePoint).count();
  }

  virtual ~BaseEvent() {};
};
}  // namespace core
}  // namespace zwsd
