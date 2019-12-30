#pragma once
#include <atomic>
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
#include "zwtimecpp/core/utils/better-enums/enum.h"

/**
 * @export_marco:
 *
 *  BEAN_UTILS_ENABLE_JSON_AND_DUMP(className,proterty)
 *
 *
 *
 */
namespace nlohmann {
template <typename T>
struct adl_serializer<std::atomic<T>> {
  static void to_json(json &j, const std::atomic<T> &p) { j = p.load(); }

  static void from_json(const json &j, std::atomic<T> &p) {
    T value{};
    j.get_to(value);
    p.store(value);
  }
};
}

template <class T>
const T &__zwsd_getValue(const T &v) {
  return v;
}

template <class T>
T __zwsd_getValue(const std::atomic<T> &v) {
  return v.load();
}

/**
 * @brief 使能对象的复制，打印，序列化，反序列功能
 */
#define BEAN_UTILS_ENABLE_CPY_AND_DUMP(className, agrs...)                     \
\
  template <typename OStream>                                                  \
  friend inline OStream &operator<<(OStream &os, const className &c) {         \
    nlohmann::json j;                                                          \
    j = c;                                                                     \
    return os << j.dump();                                                     \
  }                                                                            \
  friend inline void to_json(nlohmann::json &j, const className &p) {          \
    BEAN_UTILS_TO_JSON_PATTERN(agrs);                                          \
  }                                                                            \
  friend inline void from_json(const nlohmann::json &j, className &p) {        \
    BEAN_UTILS_FROM_JSON_PATTERN(agrs);                                        \
  }                                                                            \
  friend inline void to_json(nlohmann::json &j,                                \
                             const shared_ptr<className> &pp) {                \
    if (!pp) return;                                                           \
    className &p = *pp;                                                        \
    BEAN_UTILS_TO_JSON_PATTERN(agrs);                                          \
  }                                                                            \
  friend inline void from_json(const nlohmann::json &j,                        \
                               shared_ptr<className> &pp) {                    \
    if (!pp) pp.reset(new className());                                        \
    className &p = *pp;                                                        \
    BEAN_UTILS_FROM_JSON_PATTERN(agrs);                                        \
  }                                                                            \
  friend inline void to_json(nlohmann::json &j,                                \
                             const unique_ptr<className> &pp) {                \
    if (!pp) return;                                                           \
    className &p = *pp;                                                        \
    BEAN_UTILS_TO_JSON_PATTERN(agrs);                                          \
  }                                                                            \
  friend inline void from_json(const nlohmann::json &j,                        \
                               unique_ptr<className> &pp) {                    \
    if (!pp) pp.reset(new className());                                        \
    className &p = *pp;                                                        \
    BEAN_UTILS_FROM_JSON_PATTERN(agrs);                                        \
  }                                                                            \
                                                                               \
 private:                                                                      \
  bool ____pad____;                                                            \
                                                                               \
 public:                                                                       \
  className(const className &cpy) : BEAN_UTILS_CPY(agrs) ____pad____(false) {} \
  className &operator=(const className &other) { return *this; }

#define BeanDeclearLock(name) \
 private:                     \
  mutable recursive_mutex name;

#define BeanAttributeWithLock(type, name, initialValue, lock) \
 private:                                                     \
  type name{initialValue};                                    \
                                                              \
 public:                                                      \
  void set_##name(const type &value) {                        \
    std::lock_guard<std::recursive_mutex> __lock__(lock);     \
    this->name = {value};                                     \
  }                                                           \
  const type &get_##name##Const() const {                     \
    std::lock_guard<std::recursive_mutex> __lock__(lock);     \
    return name;                                              \
  }                                                           \
  type &get_##name() {                                        \
    std::lock_guard<std::recursive_mutex> __lock__(lock);     \
    return name;                                              \
  }

#define BeanAttributeWithLockGet(type, name, initialValue, lock) \
 private:                                                        \
  type name{initialValue};                                       \
                                                                 \
 public:                                                         \
  const type &get_##name##Const() const {                        \
    std::lock_guard<std::recursive_mutex> __lock__(lock);        \
    return name;                                                 \
  }                                                              \
  type &get_##name() {                                           \
    std::lock_guard<std::recursive_mutex> __lock__(lock);        \
    return name;                                                 \
  }

#define BeanAttributeWithLockSet(type, name, initialValue, lock) \
 private:                                                        \
  type name{initialValue};                                       \
                                                                 \
 public:                                                         \
  void set_##name(const type &value) {                           \
    std::lock_guard<std::recursive_mutex> __lock__(lock);        \
    this->name = {value};                                        \
  }

#define BeanAttribute(type, name, initialValue)                \
 private:                                                      \
  type name{initialValue};                                     \
                                                               \
 public:                                                       \
  void set_##name(const type &value) { this->name = {value}; } \
  const type &get_##name##Const() const { return name; }       \
  type &get_##name() { return name; }

#define BeanAttributeAtomic(type, name, initialValue)          \
 private:                                                      \
  atomic<type> name{initialValue};                             \
                                                               \
 public:                                                       \
  void set_##name(const type &value) { this->name = {value}; } \
  const type get_##name() const { return name; }

#define BeanAttributeGet(type, name, initialValue)       \
 private:                                                \
  type name{initialValue};                               \
                                                         \
 public:                                                 \
  const type &get_##name##Const() const { return name; } \
  type &get_##name() { return name; }

#define BeanAttributeSet(type, name, initialValue) \
 private:                                          \
  type name{initialValue};                         \
                                                   \
 public:                                           \
  void set_##name(const type &value) { this->name = {value}; }

#define BeanAttributeDeclear(type, name, initialValue) \
 private:                                              \
  type name{initialValue};

#define BeanAttributeDeclearAtomic(type, name, initialValue) \
 private:                                                    \
  atomic<type> name{initialValue};
