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
#include "zwtimecpp/core/utils/macros.hpp"

#define ENABLE_ENUM_TO_STRING_ID(x) x

/**
 * @brief 注意目前参数最大支持10个,如果需要增加数量需要修改两个地方
 * ENABLE_ENUM_TO_STRINGMx ----> 增加其最大支持的数量
 * ZWSD_PARAMETER_COUNT ---> 增加其最大支持的数量
 *
 * DEFINE_ENUM
 * 这个宏主要作用,计算宏参数的数量,
 * 将其解析成ENABLE_ENUM_TO_STRINGM(??)(Type,v1,v2,v3,v4....)
 *
 *
 * @Usage
 *
 * DEFINE_ENUM(enum_t, value1, value2, value3)
 * 完成上面两个声明后,调用下面的方法,即可实现宏到字符串的转换
 * eToString(value1)
 *
 * @TODO:
 *  目前缺陷,无法对指令变量枚举赋初值,
 * 如果有这方面需求,请使用better_enum(better_enum无法在类的内部定义枚举类型)
 */

#define DEFINE_ENUM(Type, ...) ENABLE_ENUM_TO_STRING(Type, __VA_ARGS__)

#define ENABLE_ENUM_TO_STRING(Type, ...)                \
  ENABLE_ENUM_TO_STRING_ID(ENABLE_ENUM_TO_STRING_APPLY( \
      ENABLE_ENUM_TO_STRING_PP_MAP_VAR_COUNT,           \
      ZWSD_PARAMETER_COUNT(__VA_ARGS__))(Type, __VA_ARGS__))

#define ENABLE_ENUM_TO_STRING_PP_MAP_VAR_COUNT(count) \
  ENABLE_ENUM_TO_STRINGM##count

#define ENABLE_ENUM_TO_STRING_APPLY(macro, ...) \
  ENABLE_ENUM_TO_STRING_ID(macro(__VA_ARGS__))

#define ENABLE_ENUM_TO_STRINGM1(Type, v1)          \
  enum Type { v1 = 0 };                            \
  static inline std::string eToString(Type type) { \
    switch (type) {                                \
      case Type::v1:                               \
        return #v1;                                \
      default:                                     \
        return "Unkown";                           \
    }                                              \
  }

#define ENABLE_ENUM_TO_STRINGM2(Type, v1, v2)      \
  enum Type { v1 = 0, v2 };                        \
  static inline std::string eToString(Type type) { \
    switch (type) {                                \
      case Type::v1:                               \
        return #v1;                                \
      case Type::v2:                               \
        return #v2;                                \
      default:                                     \
        return "Unkown";                           \
    }                                              \
  }

#define ENABLE_ENUM_TO_STRINGM3(Type, v1, v2, v3)  \
  enum Type { v1 = 0, v2, v3 };                    \
  static inline std::string eToString(Type type) { \
    switch (type) {                                \
      case Type::v1:                               \
        return #v1;                                \
      case Type::v2:                               \
        return #v2;                                \
      case Type::v3:                               \
        return #v3;                                \
      default:                                     \
        return "Unkown";                           \
    }                                              \
  }

#define ENABLE_ENUM_TO_STRINGM4(Type, v1, v2, v3, v4) \
  enum Type { v1 = 0, v2, v3, v4 };                   \
  static inline std::string eToString(Type type) {    \
    switch (type) {                                   \
      case Type::v1:                                  \
        return #v1;                                   \
      case Type::v2:                                  \
        return #v2;                                   \
      case Type::v3:                                  \
        return #v3;                                   \
      case Type::v4:                                  \
        return #v4;                                   \
      default:                                        \
        return "Unkown";                              \
    }                                                 \
  }

#define ENABLE_ENUM_TO_STRINGM5(Type, v1, v2, v3, v4, v5) \
  enum Type { v1 = 0, v2, v3, v4, v5 };                   \
  static inline std::string eToString(Type type) {        \
    switch (type) {                                       \
      case Type::v1:                                      \
        return #v1;                                       \
      case Type::v2:                                      \
        return #v2;                                       \
      case Type::v3:                                      \
        return #v3;                                       \
      case Type::v4:                                      \
        return #v4;                                       \
      case Type::v5:                                      \
        return #v5;                                       \
      default:                                            \
        return "Unkown";                                  \
    }                                                     \
  }

#define ENABLE_ENUM_TO_STRINGM6(Type, v1, v2, v3, v4, v5, v6) \
  enum Type { v1 = 0, v2, v3, v4, v5, v6 };                   \
  static inline std::string eToString(Type type) {            \
    switch (type) {                                           \
      case Type::v1:                                          \
        return #v1;                                           \
      case Type::v2:                                          \
        return #v2;                                           \
      case Type::v3:                                          \
        return #v3;                                           \
      case Type::v4:                                          \
        return #v4;                                           \
      case Type::v5:                                          \
        return #v5;                                           \
      case Type::v6:                                          \
        return #v6;                                           \
      default:                                                \
        return "Unkown";                                      \
    }                                                         \
  }

#define ENABLE_ENUM_TO_STRINGM7(Type, v1, v2, v3, v4, v5, v6, v7) \
  enum Type { v1 = 0, v2, v3, v4, v5, v6, v7 };                   \
  static inline std::string eToString(Type type) {                \
    switch (type) {                                               \
      case Type::v1:                                              \
        return #v1;                                               \
      case Type::v2:                                              \
        return #v2;                                               \
      case Type::v3:                                              \
        return #v3;                                               \
      case Type::v4:                                              \
        return #v4;                                               \
      case Type::v5:                                              \
        return #v5;                                               \
      case Type::v6:                                              \
        return #v6;                                               \
      case Type::v7:                                              \
        return #v7;                                               \
      default:                                                    \
        return "Unkown";                                          \
    }                                                             \
  }

#define ENABLE_ENUM_TO_STRINGM8(Type, v1, v2, v3, v4, v5, v6, v7, v8) \
  enum Type { v1 = 0, v2, v3, v4, v5, v6, v7, v8 };                   \
  static inline std::string eToString(Type type) {                    \
    switch (type) {                                                   \
      case Type::v1:                                                  \
        return #v1;                                                   \
      case Type::v2:                                                  \
        return #v2;                                                   \
      case Type::v3:                                                  \
        return #v3;                                                   \
      case Type::v4:                                                  \
        return #v4;                                                   \
      case Type::v5:                                                  \
        return #v5;                                                   \
      case Type::v6:                                                  \
        return #v6;                                                   \
      case Type::v7:                                                  \
        return #v7;                                                   \
      case Type::v8:                                                  \
        return #v8;                                                   \
      default:                                                        \
        return "Unkown";                                              \
    }                                                                 \
  }

#define ENABLE_ENUM_TO_STRINGM9(Type, v1, v2, v3, v4, v5, v6, v7, v8, v9) \
  enum Type { v1 = 0, v2, v3, v4, v5, v6, v7, v8, v9 };                   \
  static inline std::string eToString(Type type) {                        \
    switch (type) {                                                       \
      case Type::v1:                                                      \
        return #v1;                                                       \
      case Type::v2:                                                      \
        return #v2;                                                       \
      case Type::v3:                                                      \
        return #v3;                                                       \
      case Type::v4:                                                      \
        return #v4;                                                       \
      case Type::v5:                                                      \
        return #v5;                                                       \
      case Type::v6:                                                      \
        return #v6;                                                       \
      case Type::v7:                                                      \
        return #v7;                                                       \
      case Type::v8:                                                      \
        return #v8;                                                       \
      case Type::v9:                                                      \
        return #v9;                                                       \
      default:                                                            \
        return "Unkown";                                                  \
    }                                                                     \
  }

#define ENABLE_ENUM_TO_STRINGM10(Type, v1, v2, v3, v4, v5, v6, v7, v8, v9, \
                                 v10)                                      \
  enum Type { v1 = 0, v2, v3, v4, v5, v6, v7, v8, v9, v10 };               \
  static inline std::string eToString(Type type) {                         \
    switch (type) {                                                        \
      case Type::v1:                                                       \
        return #v1;                                                        \
      case Type::v2:                                                       \
        return #v2;                                                        \
      case Type::v3:                                                       \
        return #v3;                                                        \
      case Type::v4:                                                       \
        return #v4;                                                        \
      case Type::v5:                                                       \
        return #v5;                                                        \
      case Type::v6:                                                       \
        return #v6;                                                        \
      case Type::v7:                                                       \
        return #v7;                                                        \
      case Type::v8:                                                       \
        return #v8;                                                        \
      case Type::v9:                                                       \
        return #v9;                                                        \
      case Type::v10:                                                      \
        return #v10;                                                       \
      default:                                                             \
        return "Unkown";                                                   \
    }                                                                      \
  }
