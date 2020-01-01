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
  virtual void onCall(const string& msg){};
};

class TestAble {
  bool inTest = false;
  shared_ptr<TestListener> listener;

 public:
  void enableTest(shared_ptr<TestListener> listener = nullptr) {
    inTest = true;
    this->listener = listener;
  }
  bool isInTest() { return inTest; }

  void testMark(const string& msg) {
    if (listener) listener->onCall(msg);
  };

 private:
};
}
}  // namespace zwsd