//
// Created by zhaohe on 19-6-11.
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

namespace zwsd {
namespace core {
using namespace std;
class MapUtils {
 public:
  template <class Key, class Value>
  static shared_ptr<Value> find(map<Key, shared_ptr<Value>> mapv, Key k) {
    auto result = mapv.find(k);
    if (result == mapv.end()) {
      return nullptr;
    }
    return result->second;
  }

  template <class Key, class Value>
  static bool contain(map<Key, Value> mapv, Key k) {
    auto result = mapv.find(k);
    if (result == mapv.end()) {
      return true;
    }
    return false;
  }
};
}  // namespace core
}  // namespace zwsd
