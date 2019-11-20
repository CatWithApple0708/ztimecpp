#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "zwtimecpp/core/logger/logger.hpp"
#include "zwtimecpp/core/utils/string_utils.hpp"
namespace zwsd {
using namespace std;

class UaraProtocolV1Parameter {
  vector<uint8_t> bufValue;
  bool boolValue;
  int32_t int32Value;

 public:
  UaraProtocolV1Parameter(const vector<uint8_t>& bufValue, bool boolValue,
                          int32_t int32Value)
      : bufValue(bufValue), boolValue(boolValue), int32Value(int32Value){};
  const vector<uint8_t>& asBuf() const { return bufValue; };
  const bool asBool() const { return boolValue; };
  const int32_t asInt32() const { return int32Value; };
};

template <typename OStream>
static inline OStream& operator<<(OStream& os,
                                  vector<UaraProtocolV1Parameter> packetType) {
  bool first = false;
  for (auto& var : packetType) {
    if (!first) {
      os << "[";
    }
    if (&var != &packetType.back()) {
      os << fmt::format("{},", core::StringUtils::bytesToString(var.asBuf()));
    } else {
      os << fmt::format("{}]", core::StringUtils::bytesToString(var.asBuf()));
    }
    first = true;
  }
  return os;
}
}  // zwsd
