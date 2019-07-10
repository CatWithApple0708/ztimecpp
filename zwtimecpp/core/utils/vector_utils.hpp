//
// Created by zhaohe on 19-7-10.
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
using namespace std;
class VectorUtils {
 public:
  template <class T>
  static void append(vector<T>& des, const vector<T>& src) {
    des.insert(des.end(), src.begin(), src.end());
  }
  /**
   * @brief
   *
   * @tparam T
   * @param src
   * @param splitSize
   * @return list<vector<T>>
   */
  template <class T>
  static vector<vector<T>> split(const vector<T>& src, int splitSize,
                                 vector<T>& theRemain) {
    vector<vector<T>> ret;
    ret.reserve(src.size() / splitSize + 1);
    theRemain.clear();
    for (size_t i = 0;; i += splitSize) {
      if (i + splitSize > src.size()) {
        theRemain.insert(theRemain.end(), src.begin() + i, src.end());
        break;
      }
      vector<T> cur(src.begin() + i, src.begin() + i + splitSize);
      ret.push_back(cur);
    }
    return ret;
  }
};
}
