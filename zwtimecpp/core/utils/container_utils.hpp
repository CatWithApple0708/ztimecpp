//
// Created by zhaohe on 19-6-16.
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
class ContainerUtils {
 public:
  template <class T>
  static list<shared_ptr<T>> ConstructList(set<shared_ptr<T>> from) {
    list<shared_ptr<T>> to;
    for (auto& var : from) to.push_back(var);
    return move(to);
  }

  template <class Key, class T>
  static list<shared_ptr<T>> ConstructList(map<Key, shared_ptr<T>> from) {
    list<shared_ptr<T>> to;
    for (auto& var : from) to.push_back(var.second);
    return move(to);
  }

  template <class T>
  static T VGet(const vector<T>& v, size_t offset, T defaultValue) {
    if (offset < v.size()) {
      return v[offset];
    }
    return defaultValue;
  }

  template <class T>
  static bool contain(const set<T>& set_container, const T& value) {
    if (sets.find(value) != sets.end()) return true;
    return false;
  }

  template <class T>
  static bool contain(const list<T> &list_container, const T& value) {
    for (auto& var : list_container)
      if (var == value) return true;

    return false;
  }
  // template <class T>
  // static inline void cpyVectorToArray(const vector<T>& src, T* arry,
  //                                     size_t arrary_size) {
  //   memcpy((void*)array, (void*)&src[0],
  //          (arrary_size < src.size() ? arrary_size : src.size()) *
  //          sizeof(T));
  // }
};
}  // namespace core
}  // namespace zwsd
