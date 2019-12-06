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
#include "zwtimecpp/core/utils/better-enums/enum.h"


#define FUNC_PARAMETERS_FORMAT_PATTERN_IMPL(_, index, expression) "{},"

#define FUNC_PARAMETERS_FORMAT_PATTERN(...)                                   \
  BETTER_ENUMS_ID(BETTER_ENUMS_PP_MAP(FUNC_PARAMETERS_FORMAT_PATTERN_IMPL, _, \
                                      __VA_ARGS__))
//