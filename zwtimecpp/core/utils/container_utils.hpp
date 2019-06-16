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
using namespace std;
class ContainerUtils {
 public:
  template <class T>
  static list<shared_ptr<T>> ConstructList(set<shared_ptr<T>> from) {
    list<shared_ptr<T>> to;
    for (auto& var : from) to.push_back(var);
    return move(to);
  }

  //   template <class Key, class T>
  //   static list<shared_ptr<T>> ConstructList(map<Key, shared_ptr<T>> from) {
  //     list<shared_ptr<T>> to;
  //     for (auto& var : from) to.push_back(var->second);
  //     return move(to);
  //   }
};
}  // namespace zwsd
