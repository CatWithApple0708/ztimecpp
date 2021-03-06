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
#include "zwtimecpp/core/utils/nod/nod.hpp"

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

#if 1
#define BEAN_UTILS_FROM_JSON_PATTER_EACH(_, index, expression) \
  try {                                                        \
    j.at(#expression).get_to(p.expression);                    \
  } catch (const std::exception &e) {                          \
  }
#define BEAN_UTILS_TO_JSON_PATTER_EACH(_, index, expression) \
  j[#expression] = p.expression;
#else
#define BEAN_UTILS_FROM_JSON_PATTER_EACH(_, index, expression)
#define BEAN_UTILS_TO_JSON_PATTER_EACH(_, index, expression)
#endif

#define BEAN_UTILS_FROM_JSON_PATTERN(...) \
  BETTER_ENUMS_ID(                        \
      BETTER_ENUMS_PP_MAP(BEAN_UTILS_FROM_JSON_PATTER_EACH, _, __VA_ARGS__))

#define BEAN_UTILS_TO_JSON_PATTERN(...) \
  BETTER_ENUMS_ID(                      \
      BETTER_ENUMS_PP_MAP(BEAN_UTILS_TO_JSON_PATTER_EACH, _, __VA_ARGS__))

#define BEAN_UTILS__CPY(_, index, expression) \
  expression(__zwsd_getValue(cpy.expression)),
#define BEAN_UTILS_CPY(...) \
  BETTER_ENUMS_ID(BETTER_ENUMS_PP_MAP(BEAN_UTILS__CPY, _, __VA_ARGS__))

#define BEAN_UTILS__EQ_CPY(_, index, expression) \
  this->expression = __zwsd_getValue(cpy.expression);
#define BEAN_UTILS_EQ_CPY(...) \
  BETTER_ENUMS_ID(BETTER_ENUMS_PP_MAP(BEAN_UTILS__EQ_CPY, _, __VA_ARGS__))
/**
 * @brief 使能对象的复制，打印，序列化，反序列功能
 */
#define BEAN_UTILS_ENABLE_CPY_AND_DUMP(className, agrs...)                     \
                                                                               \
  friend inline std::ostream &operator<<(std::ostream &os,                     \
                                         const className &c) {                 \
    nlohmann::json j;                                                          \
    j = c;                                                                     \
    return os << j.dump();                                                     \
  }                                                                            \
  friend inline std::ostream &operator<<(std::ostream &os,                     \
                                         const shared_ptr<className> &c) {     \
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
  className operator=(const className &cpy) {                                  \
    BEAN_UTILS_EQ_CPY(agrs);                                                   \
    return *this;                                                              \
  }

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

#define BeanAttributeWithLockWithSignal(type, name, initialValue, lock)       \
 private:                                                                     \
  type name{initialValue};                                                    \
                                                                              \
 public:                                                                      \
  nod::signal<void(const type &oldValue, const type &toValue)> signal_##name; \
  void set_##name(const type &value) {                                        \
    type olevalue{initialValue};                                              \
    {                                                                         \
      std::lock_guard<std::recursive_mutex> __lock__(lock);                   \
      olevalue = {this->name};                                           \
      this->name = {value};                                                   \
    }                                                                         \
    signal_##name(olevalue, value);                                           \
  }                                                                           \
  const type &get_##name##Const() const {                                     \
    std::lock_guard<std::recursive_mutex> __lock__(lock);                     \
    return name;                                                              \
  }                                                                           \
  type &get_##name() {                                                        \
    std::lock_guard<std::recursive_mutex> __lock__(lock);                     \
    return name;                                                              \
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

#define BeanAttribute(type, name, initialValue)              \
 private:                                                    \
  type name{initialValue};                                   \
                                                             \
 public:                                                     \
  void set_##name(const type &value) { this->name = value; } \
  const type &get_##name##Const() const { return name; }     \
  type &get_##name() { return name; }

#define BeanAttributeAtomic(type, name, initialValue)                          \
 private:                                                                      \
  atomic<type> name{initialValue};                                             \
                                                                               \
 public:                                                                       \
  void set_##name(const type &value) { this->name = {value}; }                 \
  const type get_##name() const { return name; }                               \
  type add_##name(const type &addvalue) {                                      \
    type old = name.load(std::memory_order_consume);                           \
    type desired = old + addvalue;                                             \
    while (!name.compare_exchange_weak(                                        \
        old, desired, std::memory_order_release, std::memory_order_consume)) { \
      desired = old + addvalue;                                                \
    }                                                                          \
    return desired;                                                            \
  }

#define BeanAttributeAtomicWithSignal(type, name, initialValue)                \
 private:                                                                      \
  atomic<type> name{initialValue};                                             \
                                                                               \
 public:                                                                       \
  nod::signal<void(const type &oldValue, const type &toValue)> signal_##name;  \
                                                                               \
  void set_##name(const type &value) {                                         \
    type old = this->name;                                                     \
    this->name = value;                                                      \
    signal_##name(old, value);                                                 \
  }                                                                            \
  const type get_##name() const { return name; }                               \
  type add_##name(const type &addvalue) {                                      \
    type old = name.load(std::memory_order_consume);                           \
    type desired = old + addvalue;                                             \
    while (!name.compare_exchange_weak(                                        \
        old, desired, std::memory_order_release, std::memory_order_consume)) { \
      desired = old + addvalue;                                                \
    }                                                                          \
    signal_##name(old, desired);                                               \
    return desired;                                                            \
  }

#define BeanAttributeWithSignal(type, name, initialValue)                     \
 private:                                                                     \
  atomic<type> name{initialValue};                                            \
                                                                              \
 public:                                                                      \
  nod::signal<void(const type &oldValue, const type &toValue)> signal_##name; \
                                                                              \
  void set_##name(const type &value) {                                        \
    type old = this->name;                                                    \
    this->name = value;                                                       \
    signal_##name(old, value);                                                \
  }                                                                           \
  const type get_##name() const { return name; }

#define BeanAttributeAtomicGet(type, name, initialValue) \
 private:                                                \
  atomic<type> name{initialValue};                       \
                                                         \
 public:                                                 \
  const type get_##name() const { return name; }

#define BeanAttributeAtomicBool(name, initialValue)            \
 private:                                                      \
  atomic<bool> name{initialValue};                             \
                                                               \
 public:                                                       \
  void set_##name(const bool &value) { this->name = {value}; } \
  const bool get_##name() const { return name; }

#define BeanAttributeAtomicBoolWithSignal(name, initialValue)                 \
 private:                                                                     \
  atomic<bool> name{initialValue};                                            \
                                                                              \
 public:                                                                      \
  nod::signal<void(const bool &oldValue, const bool &toValue)> signal_##name; \
  void set_##name(const bool &value) {                                        \
    bool oldValue = this->name;                                               \
    this->name = {value};                                                     \
    if (oldValue != value) signal_##name(oldValue, value);                    \
  }                                                                           \
  const bool get_##name() const { return name; }

#define BeanAttributeAtomicBoolGet(name, initialValue) \
 private:                                              \
  atomic<bool> name{initialValue};                     \
                                                       \
 public:                                               \
  const bool get_##name() const { return name; }

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
