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
#define ENABLE_ENUM_TO_STRING1(Type, v1)           \
  static inline std::string eToString(Type type) { \
    switch (type) {                                \
      case Type::v1: \
        return #v1;                                \
      default:                                     \
        return "Unkown";                           \
    }                                              \
  }

#define ENABLE_ENUM_TO_STRING2(Type, v1, v2)       \
  static inline std::string eToString(Type type) { \
    switch (type) {                                \
      case Type::v1: \
        return #v1;                                \
      case Type::v2: \
        return #v2;                                \
      default:                                     \
        return "Unkown";                           \
    }                                              \
  }

#define ENABLE_ENUM_TO_STRING3(Type, v1, v2, v3)   \
  static inline std::string eToString(Type type) { \
    switch (type) {                                \
      case Type::v1: \
        return #v1;                                \
      case Type::v2: \
        return #v2;                                \
      case Type::v3: \
        return #v3;                                \
      default:                                     \
        return "Unkown";                           \
    }                                              \
  }

#define ENABLE_ENUM_TO_STRING4(Type, v1, v2, v3, v4) \
  static inline std::string eToString(Type type) {   \
    switch (type) {                                  \
      case Type::v1:   \
        return #v1;                                  \
      case Type::v2:   \
        return #v2;                                  \
      case Type::v3:   \
        return #v3;                                  \
      case Type::v4:   \
        return #v4;                                  \
      default:                                       \
        return "Unkown";                             \
    }                                                \
  }

#define ENABLE_ENUM_TO_STRING5(Type, v1, v2, v3, v4, v5) \
  static inline std::string eToString(Type type) {       \
    switch (type) {                                      \
      case Type::v1:       \
        return #v1;                                      \
      case Type::v2:       \
        return #v2;                                      \
      case Type::v3:       \
        return #v3;                                      \
      case Type::v4:       \
        return #v4;                                      \
      case Type::v5:       \
        return #v5;                                      \
      default:                                           \
        return "Unkown";                                 \
    }                                                    \
  }

#define ENABLE_ENUM_TO_STRING6(Type, v1, v2, v3, v4, v5, v6) \
  static inline std::string eToString(Type type) {           \
    switch (type) {                                          \
      case Type::v1:           \
        return #v1;                                          \
      case Type::v2:           \
        return #v2;                                          \
      case Type::v3:           \
        return #v3;                                          \
      case Type::v4:           \
        return #v4;                                          \
      case Type::v5:           \
        return #v5;                                          \
      case Type::v6:           \
        return #v6;                                          \
      default:                                               \
        return "Unkown";                                     \
    }                                                        \
  }

#define ENABLE_ENUM_TO_STRING7(Type, v1, v2, v3, v4, v5, v6, v7) \
  static inline std::string eToString(Type type) {               \
    switch (type) {                                              \
      case Type::v1:               \
        return #v1;                                              \
      case Type::v2:               \
        return #v2;                                              \
      case Type::v3:               \
        return #v3;                                              \
      case Type::v4:               \
        return #v4;                                              \
      case Type::v5:               \
        return #v5;                                              \
      case Type::v6:               \
        return #v6;                                              \
      case Type::v7:               \
        return #v7;                                              \
      default:                                                   \
        return "Unkown";                                         \
    }                                                            \
  }

#define ENABLE_ENUM_TO_STRING8(Type, v1, v2, v3, v4, v5, v6, v7, v8) \
  static inline std::string eToString(Type type) {                   \
    switch (type) {                                                  \
      case Type::v1:                   \
        return #v1;                                                  \
      case Type::v2:                   \
        return #v2;                                                  \
      case Type::v3:                   \
        return #v3;                                                  \
      case Type::v4:                   \
        return #v4;                                                  \
      case Type::v5:                   \
        return #v5;                                                  \
      case Type::v6:                   \
        return #v6;                                                  \
      case Type::v7:                   \
        return #v7;                                                  \
      case Type::v8:                   \
        return #v8;                                                  \
      default:                                                       \
        return "Unkown";                                             \
    }                                                                \
  }

#define ENABLE_ENUM_TO_STRING9(Type, v1, v2, v3, v4, v5, v6, v7, v8, v9) \
  static inline std::string eToString(Type type) {                       \
    switch (type) {                                                      \
      case Type::v1:                       \
        return #v1;                                                      \
      case Type::v2:                       \
        return #v2;                                                      \
      case Type::v3:                       \
        return #v3;                                                      \
      case Type::v4:                       \
        return #v4;                                                      \
      case Type::v5:                       \
        return #v5;                                                      \
      case Type::v6:                       \
        return #v6;                                                      \
      case Type::v7:                       \
        return #v7;                                                      \
      case Type::v8:                       \
        return #v8;                                                      \
      case Type::v9:                       \
        return #v9;                                                      \
      default:                                                           \
        return "Unkown";                                                 \
    }                                                                    \
  }

#define ENABLE_ENUM_TO_STRING10(Type, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) \
  static inline std::string eToString(Type type) {                             \
    switch (type) {                                                            \
      case Type::v1:                             \
        return #v1;                                                            \
      case Type::v2:                             \
        return #v2;                                                            \
      case Type::v3:                             \
        return #v3;                                                            \
      case Type::v4:                             \
        return #v4;                                                            \
      case Type::v5:                             \
        return #v5;                                                            \
      case Type::v6:                             \
        return #v6;                                                            \
      case Type::v7:                             \
        return #v7;                                                            \
      case Type::v8:                             \
        return #v8;                                                            \
      case Type::v9:                             \
        return #v9;                                                            \
      case Type::v10:                            \
        return #v10;                                                           \
      default:                                                                 \
        return "Unkown";                                                       \
    }                                                                          \
  }
