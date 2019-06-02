//
// Created by zhaohe on 19-6-2.
//

#pragma once
#include <memory>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <chrono>

namespace zwsd {
namespace core {
using namespace std;
using namespace chrono;
class TimeUtils {
 public:
  static int64_t getMicroseconds() {
	return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
  }

  static int64_t getSeconds() {
	return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
  }
  static int64_t getMilliseconds() {
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

  }
  static int64_t getHours() {
	return duration_cast<hours>(system_clock::now().time_since_epoch()).count();
  }
};
};

}


