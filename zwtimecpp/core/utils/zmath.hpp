#pragma once
#include <cmath>
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
namespace zwsd {
using namespace std;

static inline int zcmp(float va1, float va2) {
  if (fabs(va1 - va2) <= 1e-6) {
    return 0;
  }

  if (va1 > va2) {
    return 1;
  } else {
    return -1;
  }
}

static inline bool zeq(float va1, float va2) { return zcmp(va1, va2) == 0; }

static inline float limitPi1(float value) {
  if (value > M_PI) {
    int nPi = int((value+M_PI) / (2 * M_PI));
    return value - (nPi) * 2 * M_PI;
  } else if (value < -M_PI) {
    int nPi = -int((value -M_PI)/ (2 * M_PI));
    return value + (nPi)*2 * M_PI;
  }
  return value;
}

static inline float limitPiRecursion(float value) {
  if (value > M_PI) {
    return limitPiRecursion(value - 2 * M_PI);
  } else if (value < -M_PI) {
    return limitPiRecursion(value + 2 * M_PI);
  } else {
    return value;
  }
};

}  // namespace zwsd