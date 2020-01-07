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

}  // namespace zwsd