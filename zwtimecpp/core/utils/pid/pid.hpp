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

extern "C" {
#include "zwtimecpp/core/utils/pid/pid.h"
}
namespace zwsd {
using namespace std;

class Pid {
  pid_inc_t pid_handle;

 public:
  Pid() { memset(&pid_handle, 0, sizeof(pid_inc_t)); }
  float process(float target, float actual) {
    return pid_inc_process(&pid_handle, target, actual);
  }

 private:
};

}  // namespace zwsd