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
#include "zwtimecpp/core/logger/logger.hpp"
namespace zwsd {
namespace core {
using namespace std;
/**
 * @brief　对类内部不容易被mock的地方进行打桩
 *
 */
class TestListener {
 public:
  virtual ~TestListener() {}
  virtual void onCall(string mark) = 0;
};

class TestAble {
  bool inTest = false;
  shared_ptr<TestListener> listener;

 public:
  void enableTest(shared_ptr<TestListener> listener = nullptr) {
    inTest = true;
    listener = listener;
  }
  bool isInTest() { return inTest; }

  template <class... T>
  string makeMarkStr(string funcName, T... args) {
    // return fmt::format("call:{}", funcName);
    string ret = "mark:" + funcName + "-";
    makrMarkStrInter(ret, args...);
    return ret;
  };

  template <class... T>
  inline void makrMark(string funcName, T... args) {
    if (listener) {
      listener->onCall(funcName, args...);
    }
  }

 private:
  template <typename T, typename... Targs>
  void makrMarkStrInter(string& buf, T value, Targs... values) {
    makrMarkStrInter(buf, value);
    makrMarkStrInter(buf, values...);
  }
  void makrMarkStrInter(string& buf) {}
  template <typename T>
  void makrMarkStrInter(string& buf, T value) {
    buf = fmt::format("{}-{}", buf, value);
  }

 private:
};
}
}  // namespace zwsd