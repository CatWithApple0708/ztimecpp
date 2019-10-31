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
#include "zwtimecpp/core/logger/logger.hpp"
namespace zwsd {
namespace core {
using namespace std;
typedef function<void(string)> StringUnpackerOnString_t;
class StringUnpacker {
  ENABLE_LOGGER(StringUnpacker);
  string name;
  string delim;
  int maxSize = -1;
  string buf;
  bool nullDelims = false;

 private:
  StringUnpacker(){};

 public:
  /**
   * @brief 构造使用\0为分割符的Unpacker
   *
   * @return shared_ptr<StringUnpacker>
   */
  static shared_ptr<StringUnpacker> createNullUnpacker(string name,
                                                       int max_size = -1) {
    shared_ptr<StringUnpacker> var(new StringUnpacker());
    var->name = name;
    var->maxSize = max_size;
    var->nullDelims = true;
    return var;
  }
  /**
   * @brief 构造使用\n\r为分割符的Unpacker
   *
   * @return shared_ptr<StringUnpacker>
   */
  static shared_ptr<StringUnpacker> createCrLfUnpacker(string name,
                                                       int max_size = -1) {
    shared_ptr<StringUnpacker> var(new StringUnpacker());
    var->name = name;
    var->maxSize = max_size;
    var->nullDelims = false;
    var->delim = "\r\n";
    return var;
  }

 public:
  void feddata(const char* rawData, size_t len,
               StringUnpackerOnString_t unpacker);
};
}
}  // namespace zwsd