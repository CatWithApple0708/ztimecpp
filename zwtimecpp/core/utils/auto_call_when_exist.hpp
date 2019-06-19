//
// Created by zhaohe on 19-6-18.
//

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

namespace zwsd {
namespace core {
using namespace std;
class AutoCallWhenExist {
  function<void()> autoCall;

 public:
  AutoCallWhenExist(function<void()> func) : autoCall(func) {}
  ~AutoCallWhenExist() {
    if (autoCall) autoCall();
  }
};
}  // namespace core
}  // namespace zwsd
