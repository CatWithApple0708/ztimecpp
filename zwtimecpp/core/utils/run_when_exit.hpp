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
namespace zwsd {
using namespace std;

class RunWhenExit {
  function<void()> autoRun;

 public:
  RunWhenExit(function<void()> autoRun) : autoRun(autoRun) {}
  ~RunWhenExit() {
    if (autoRun) autoRun();
  }

 private:
};
/**
 * @Usage
 * AUTORUN(what you what to do)
 */
#define RUN_WHEN_EXIT(exec) \
  RunWhenExit runWhenExit##__FILE__##__LINE__([&]() { exec; });

#define RUN_WHEN_EXIT_MUTI \
RunWhenExit runWhenExit##__FILE__##__LINE__([&]() {
}  // namespace zwsd