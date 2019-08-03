//
// Created by zhaohe on 19-8-2.
//

#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace zwsd {
namespace core {
using namespace std;
template <class T>
class Result {
 public:
  Result(T value, bool success) : value(value), success(success) {}
  T value;
  bool success = false;
};
}
}
