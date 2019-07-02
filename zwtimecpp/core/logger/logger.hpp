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
namespace zwsd {}  // namespace zwsd
template <typename OStream>
static inline OStream &operator<<(OStream &os,
                                  const std::vector<std::string> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os,
                                  const std::vector<bool> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::vector<uint8_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::vector<uint16_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::vector<uint32_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::vector<uint64_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::vector<int8_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::vector<int16_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::vector<int32_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::vector<int64_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
//--------------------------------------------------------------------------------------
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::list<bool> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os,
                                  const std::list<std::string> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::list<uint8_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::list<uint16_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::list<uint32_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::list<uint64_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::list<int8_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::list<int16_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::list<int32_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::list<int64_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
//--------------------------------------------------------------------------------------

template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::set<bool> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os,
                                  const std::set<std::string> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::set<uint8_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::set<uint16_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::set<uint32_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::set<uint64_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::set<int8_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::set<int16_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::set<int32_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}
template <typename OStream>
static inline OStream &operator<<(OStream &os, const std::set<int64_t> &c) {
  nlohmann::json j = c;
  return os << j.dump();
}