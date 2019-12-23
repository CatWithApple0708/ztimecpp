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
#include "zwtimecpp/core/utils/better-enums/enum.h"

/**
 * @export_marco:
 *
 *  BEAN_UTILS_ENABLE_JSON_AND_DUMP(className,proterty)
 *
 *
 *
 */
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

#define BEAN_UTILS_ENABLE_JSON_AND_DUMP(className, agrs...)                 \
  template <typename OStream>                                           \
  static inline OStream &operator<<(OStream &os,                        \
                                    const shared_ptr<className> &c) {   \
    if (!c) return os << "{}";                                          \
    nlohmann::json j;                                                   \
    j = *c;                                                             \
    return os << j.dump();                                              \
  }                                                                     \
  template <typename OStream>                                           \
  static inline OStream &operator<<(OStream &os, const className &c) {  \
    nlohmann::json j;                                                   \
    j = c;                                                              \
    return os << j.dump();                                              \
  }                                                                     \
  static inline void to_json(nlohmann::json &j, const className &p) {   \
    BEAN_UTILS_TO_JSON_PATTERN(agrs);                             \
  }                                                                     \
  static inline void from_json(const nlohmann::json &j, className &p) { \
    BEAN_UTILS_FROM_JSON_PATTERN(agrs);                           \
  }

/**
 * @export_marco:
 *  BEAN_UTILS_ENABLE_JSON_AND_DUMP
 *  BEAN_UTILS_DECLEAR_PROPERTY
 *  BEAN_UTILS_DEFINE_CLASS
 * @usage:
 */

#define BEAN_UTILS___DECLEAR_PROPERTY(type, name, higherFirstName, \
                                      defaultValue)                \
  type name = defaultValue;

#define BEAN_UTILS_DECLEAR_PROPERTY(className) \
  className##PropertyList(BEAN_UTILS___DECLEAR_PROPERTY)

#define BEAN_UTILS__JSON_DUMP(type, name, ...) j[#name] = p.name;
#define BEAN_UTILS__JSON_DUMP2(type, name, ...) j.at(#name).get_to(p.name);

#define BEAN_UTILS_ENABLE_JSON_AND_DUMP2(className)                     \
  template <typename OStream>                                           \
  static inline OStream &operator<<(OStream &os,                        \
                                    const shared_ptr<className> &c) {   \
    if (!c) return os << "{}";                                          \
    nlohmann::json j;                                                   \
    j = *c;                                                             \
    return os << j.dump();                                              \
  }                                                                     \
  template <typename OStream>                                           \
  static inline OStream &operator<<(OStream &os, const className &c) {  \
    nlohmann::json j;                                                   \
    j = c;                                                              \
    return os << j.dump();                                              \
  }                                                                     \
  static inline void to_json(nlohmann::json &j, const className &p) {   \
    className##PropertyList(BEAN_UTILS__JSON_DUMP);                     \
  }                                                                     \
  static inline void from_json(const nlohmann::json &j, className &p) { \
    className##PropertyList(BEAN_UTILS__JSON_DUMP2);                    \
  }

#define BEAN_UTILS_DEFINE_CLASS(className)  \
  class className {                         \
   public:                                  \
    BEAN_UTILS_DECLEAR_PROPERTY(className); \
  };                                        \
  BEAN_UTILS_ENABLE_JSON_AND_DUMP2(className);

//