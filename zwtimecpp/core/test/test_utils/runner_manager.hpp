//
// Created by zhaohe on 19-5-24.
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
#include "zwtimecpp/core/utils/container_utils.hpp"
#include "zwtimecpp/core/logger/logger.hpp"

namespace {
class Initializer {
 public:
  Initializer(std::function<void()> init) { init(); }
};
}  // namespace
namespace zwsd {
using namespace std;
using namespace core;
class RunnerManager;
class Runner {
  string name;
  friend RunnerManager;

 public:
  string getName() { return name; }
  virtual void run(int argc, char const *argv[]) = 0;

  virtual string introduction(logger_t logForHelp) = 0;

  virtual string briefIntroduction() { return ""; };
};

class RunnerManager {
  map<string, shared_ptr<Runner>> RunnersMap;
  RunnerManager(){};

 public:
  static RunnerManager &Instance() {
    static RunnerManager value;
    return value;
  }

  list<shared_ptr<Runner>> runners() {
    return move(ContainerUtils::ConstructList(RunnersMap));
  };

  template <class T>
  void pushRunner(string name) {
    shared_ptr<Runner> value(new T());
    RunnersMap[name] = value;
    value->name = name;
  }

  void run(string module, int argc, char const *argv[]) {
    if (RunnersMap.find(module) != RunnersMap.end()) {
      RunnersMap[module]->run(argc, argv);
    }
  }
};
}  // namespace zwsd
#define ENABLE_TEST(className)                                         \
  static Initializer className##Initializer([]() {                     \
    zwsd::RunnerManager::Instance().pushRunner<className>(#className); \
  });
