#pragma once
#define __ENUM_HELPER_DEFINE_ENUM_ITERM(name, value) name = value,
#define ENUM_HELPER_DEFINE_ENUM_ITERM(list) list(__DEFINE_ENUM)

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
  static const char* INLINE funcname(type value) {           \
    switch (value) {                                         \
      ENUM_HELPER_SWITCH_CASE_ITERM(list)                    \
      default:                                               \
        return "unkownType";                                 \
    }                                                        \
  }
