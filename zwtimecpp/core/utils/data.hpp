//
// Created by zhaohe on 19-5-30.
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
#include "zwtimecpp/core/utils/macros.hpp"

#define DATA_ID(x) x
#define DATA(...)                           \
  DATA_ID(DATA_APPLY(DATA_PP_MAP_VAR_COUNT, \
                     ZWSD_PARAMETER_COUNT(__VA_ARGS__))(__VA_ARGS__))
#define DATA_PP_MAP_VAR_COUNT(count) DATAM##count
#define DATA_APPLY(macro, ...) DATA_ID(macro(__VA_ARGS__))

#define DATA1(v1) \
  __typeof__(v1) &v1Value() { return v1; }

#define DATA2(v1, v2)                      \
  __typeof__(v1) &v1Value() { return v1; } \
  __typeof__(v2) &v2Value() { return v2; }

#define DATA3(v1, v2, v3)                  \
  __typeof__(v1) &v1Value() { return v1; } \
  __typeof__(v2) &v2Value() { return v2; } \
  __typeof__(v3) &v3Value() { return v3; }

#define DATA4(v1, v2, v3, v4)              \
  __typeof__(v1) &v1Value() { return v1; } \
  __typeof__(v2) &v2Value() { return v2; } \
  __typeof__(v3) &v3Value() { return v3; } \
  __typeof__(v4) &v4Value() { return v4; }

#define DATA5(v1, v2, v3, v4, v5)          \
  __typeof__(v1) &v1Value() { return v1; } \
  __typeof__(v2) &v2Value() { return v2; } \
  __typeof__(v3) &v3Value() { return v3; } \
  __typeof__(v4) &v4Value() { return v4; } \
  __typeof__(v5) &v5Value() { return v5; }

#define DATA6(v1, v2, v3, v4, v5, v6)      \
  __typeof__(v1) &v1Value() { return v1; } \
  __typeof__(v2) &v2Value() { return v2; } \
  __typeof__(v3) &v3Value() { return v3; } \
  __typeof__(v4) &v4Value() { return v4; } \
  __typeof__(v5) &v5Value() { return v5; } \
  __typeof__(v6) &v6Value() { return v6; }

#define DATA7(v1, v2, v3, v4, v5, v6, v7)  \
  __typeof__(v1) &v1Value() { return v1; } \
  __typeof__(v2) &v2Value() { return v2; } \
  __typeof__(v3) &v3Value() { return v3; } \
  __typeof__(v4) &v4Value() { return v4; } \
  __typeof__(v5) &v5Value() { return v5; } \
  __typeof__(v6) &v6Value() { return v6; } \
  __typeof__(v7) &v7Value() { return v7; }

#define DATA8(v1, v2, v3, v4, v5, v6, v7, v8) \
  __typeof__(v1) &v1Value() { return v1; }    \
  __typeof__(v2) &v2Value() { return v2; }    \
  __typeof__(v3) &v3Value() { return v3; }    \
  __typeof__(v4) &v4Value() { return v4; }    \
  __typeof__(v5) &v5Value() { return v5; }    \
  __typeof__(v6) &v6Value() { return v6; }    \
  __typeof__(v7) &v7Value() { return v7; }    \
  __typeof__(v8) &v8Value() { return v8; }

#define DATA9(v1, v2, v3, v4, v5, v6, v7, v8, v9) \
  __typeof__(v1) &v1Value() { return v1; }        \
  __typeof__(v2) &v2Value() { return v2; }        \
  __typeof__(v3) &v3Value() { return v3; }        \
  __typeof__(v4) &v4Value() { return v4; }        \
  __typeof__(v5) &v5Value() { return v5; }        \
  __typeof__(v6) &v6Value() { return v6; }        \
  __typeof__(v7) &v7Value() { return v7; }        \
  __typeof__(v8) &v8Value() { return v8; }        \
  __typeof__(v9) &v9Value() { return v9; }

#define DATA10(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) \
  __typeof__(v1) &v1Value() { return v1; }              \
  __typeof__(v2) &v2Value() { return v2; }              \
  __typeof__(v3) &v3Value() { return v3; }              \
  __typeof__(v4) &v4Value() { return v4; }              \
  __typeof__(v5) &v5Value() { return v5; }              \
  __typeof__(v6) &v6Value() { return v6; }              \
  __typeof__(v7) &v7Value() { return v7; }              \
  __typeof__(v8) &v8Value() { return v8; }              \
  __typeof__(v9) &v9Value() { return v9; }              \
  __typeof__(v10) &v1Value0() { return v10; }
