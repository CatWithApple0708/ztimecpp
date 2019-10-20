//
// Created by zhaohe on 19-5-31.
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
#include "zwtimecpp/core/logger/logger_factory.hpp"
#include "zwtimecpp/core/utils/nlohmann/json.hpp"

#include "spdlog/fmt/ostr.h"
extern "C" {
#include <linux/input.h>
#include "linux/input-event-codes.h"
}

namespace zwsd {}  // namespace zwsd

#define ENABLE_BASIC_TYPE_LOGGER(type)                                         \
  template <typename OStream>                                                  \
  static inline OStream &operator<<(OStream &os, const std::list<type> &c) {   \
    nlohmann::json j = c;                                                      \
    return os << j.dump();                                                     \
  }                                                                            \
  template <typename OStream>                                                  \
  static inline OStream &operator<<(OStream &os, const std::vector<type> &c) { \
    nlohmann::json j = c;                                                      \
    return os << j.dump();                                                     \
  }                                                                            \
  template <typename OStream>                                                  \
  static inline OStream &operator<<(OStream &os, const std::set<type> &c) {    \
    nlohmann::json j = c;                                                      \
    return os << j.dump();                                                     \
  }

ENABLE_BASIC_TYPE_LOGGER(std::string)
ENABLE_BASIC_TYPE_LOGGER(bool)
ENABLE_BASIC_TYPE_LOGGER(uint8_t)
ENABLE_BASIC_TYPE_LOGGER(uint16_t)
ENABLE_BASIC_TYPE_LOGGER(uint32_t)
ENABLE_BASIC_TYPE_LOGGER(uint64_t)
ENABLE_BASIC_TYPE_LOGGER(int8_t)
ENABLE_BASIC_TYPE_LOGGER(int16_t)
ENABLE_BASIC_TYPE_LOGGER(int32_t)
ENABLE_BASIC_TYPE_LOGGER(int64_t)
ENABLE_BASIC_TYPE_LOGGER(float)
ENABLE_BASIC_TYPE_LOGGER(double)

#undef ENABLE_BASIC_TYPE_LOGGER

// dump input event
template <typename OStream>
static inline OStream &operator<<(OStream &os, struct input_event &event) {
  return os << fmt::format("input-event {} {} {}", event.type, event.code,
                           event.value);
}
