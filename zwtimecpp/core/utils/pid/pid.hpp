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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mutex>

extern "C" {
#include "zwtimecpp/core/utils/pid/pid.h"
}
namespace zwsd {
using namespace std;

class Pid {
  pid_inc_t pid_handle;
  std::mutex lock_;
  bool inited = false;

 public:
  Pid() { memset(&pid_handle, 0, sizeof(pid_inc_t)); }
  float process(float target, float actual) {
    std::lock_guard<std::mutex> lock(lock_);
    return pid_inc_process(&pid_handle, target, actual);
  }

  void set(float kp, float ki, float kd) {
    std::lock_guard<std::mutex> lock(lock_);
    pid_handle.kp = kp;
    pid_handle.ki = ki;
    pid_handle.kd = kd;
    inited = true;
  };
  bool isInited() { return inited; }

 private:
};

}  // namespace zwsd