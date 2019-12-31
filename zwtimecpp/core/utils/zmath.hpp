#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <functional>
#include <cmath>
namespace zwsd {
using namespace std;

static inline int zcmp(float va1, float va2) {
  if (fabs(va1 - va2) <= 1e-6) {
      return 0;
  }
  return va1 >= va2;
}

} // namespace zwsd