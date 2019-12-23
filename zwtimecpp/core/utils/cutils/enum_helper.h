#pragma once
#include "zwtimecpp/core/utils/cutils/compiler_config.h"
#define __ENUM_HELPER_DEFINE_ENUM_ITERM(name, value) name = value,
#define ENUM_HELPER_DEFINE_ENUM_ITERM(list) \
  list(__ENUM_HELPER_DEFINE_ENUM_ITERM)

#define __ENUM_HELPER_SWITCH_CASE_ITERM(value, _) \
  case value:                                     \
    return #value;
#define ENUM_HELPER_SWITCH_CASE_ITERM(list) \
  list(__ENUM_HELPER_SWITCH_CASE_ITERM)

/**
 * @Usage
 *
 * 参考 error.h mobile_wrapping_machines.h
 *
 */

#define ENUM_HELPER_DEFINE_ENUM(type, list) \
  typedef enum { ENUM_HELPER_DEFINE_ENUM_ITERM(list) } type;

#define ENUM_HELPER_ENABLE_ENUM_TO_STR(funcname, type, list) \
  static INLINE const char* funcname(type value) {           \
    switch (value) {                                         \
      ENUM_HELPER_SWITCH_CASE_ITERM(list)                    \
      default:                                               \
        return "unkownType";                                 \
    }                                                        \
  }
