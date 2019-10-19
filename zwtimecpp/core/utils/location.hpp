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
class _Location {
  string file;
  int line;

 public:
  _Location(string file, int line) : file(file), line(line){};
  string toString() { return fmt::format("{}:{}", file, line); }
};

#define LocationStr() (zwsd::core::_Location(__FILE__, __LINE__).toString())
}
}  // namespace zwsd