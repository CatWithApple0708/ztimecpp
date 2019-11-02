#pragma once
#include <gmock/gmock.h>
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

#include "zwtimecpp/core/utils/testable.hpp"
#include "zwtimecpp/core/core.hpp"
#include "zwtimecpp/core/logger/logger.hpp"
#include "zwtimecpp/core/utils/cutils/marco_utils.h"
namespace zwsd {
namespace core {
using namespace std;
/**
 * @urtils
 */
class GtestLogger {
  ENABLE_LOGGER(GtestLogger)
 public:
  GtestLogger() {}
  static string b2s(const vector<uint8_t>& byteTable) {
    string ret;
    for (auto& var : byteTable) {
      uint8_t hight4 = var >> 4 & 0x0f;
      uint8_t low4 = var >> 0 & 0x0f;
      ret += byteToChar(hight4);
      ret += byteToChar(low4);
    }
    return ret;
  }

 private:
  static char byteToChar(uint8_t byte) {
    if (byte < 10) {
      return '0' + byte;
    } else {
      return 'A' + (byte - 10);
    }
    throw std::out_of_range("byteToChar out of range");
    return 'x';
  }
};
/**
 * @brief 宏工具
 */

#define EXPECT_TRUE_IN_MA(excepresion)                          \
  if (!(excepresion)) {                                         \
    GtestLogger().logger->error("check {} fail", #excepresion); \
    return false;                                               \
  }

/************************mock*************************** */
class MockEventListener : public EventHandler {
 public:
  MOCK_METHOD1(onEvent, void(shared_ptr<BaseEvent>));
};

class MockTestListener : public TestListener {
 public:
  MOCK_METHOD1(onCall, void(string mark));
};

class ISignalListener {
 public:
  virtual void onValue(string value) = 0;
  virtual ~ISignalListener(){};
};

class MockSignalListener : public ISignalListener {
 public:
  MOCK_METHOD1(onValue, void(string value));
};

/************************matcher*************************** */
MATCHER_P(SimpleMa, func, "") { return func(arg); }

MATCHER_P(CArraryU8Ma, expect, "U8数组未匹配") {
  if ((memcmp(expect.data(), arg, expect.size()) != 0)) {
    vector<uint8_t> real(arg, arg + expect.size());
    GtestLogger().logger->error("expect: {} != real: {}",
                                GtestLogger::b2s(expect),
                                GtestLogger::b2s(real));
    return false;
  }
  return true;
}
}
}
