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
#include "zwtimecpp/core/base/interlog/simple_logger.hpp"
#include "zwtimecpp/core/base/object.hpp"

namespace {
class Initializer : public zwsd::core::Object {
 public:
  Initializer(std::function<void()> init) { init(); }
};
}  // namespace
namespace zwsd {
namespace core {
using namespace std;

class TestElement : public Object {
 public:
  virtual void run() = 0;
  virtual void run(int argc, char const *argv[]) = 0;
};

class TesterManager : public Object {
  map<string, shared_ptr<TestElement>> testElementsMap;
  TesterManager(){};

 public:
  static TesterManager &Instance() {
    static TesterManager value;
    return value;
  }

  template <class T>
  void pushTestElement(string name) {
    shared_ptr<TestElement> value(new T());
    testElementsMap[name] = value;
  }

  void run(string module, int argc, char const *argv[]) {
    if (testElementsMap.find(module) != testElementsMap.end()) {
      testElementsMap[module]->run(argc, argv);
    }
  }
};
}  // namespace core
}  // namespace zwsd
#define ENABLE_TEST(className)                                        \
  static Initializer className##Initializer([]() {                    \
    SimpleLogger::enableLog();                                        \
    SimpleLogger::info("Push test element:  " #className);            \
    zwsd::core::TesterManager::Instance().pushTestElement<className>( \
        #className);                                                  \
  });
