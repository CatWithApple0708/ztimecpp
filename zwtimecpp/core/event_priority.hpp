//
// Created by zhaohe on 19-6-9.
//

#pragma once
#include <memory>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include "zwtimecpp/core/utils/better-enums/enum.h"
namespace zwsd {
namespace core {
BETTER_ENUM(EventPriority_t, int, Minimum = -5, Low = -1, Medium = 0, Hight = 1,
            Highest = 5);
}
}  // namespace zwsd
