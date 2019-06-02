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
#include "zwtimecpp/core/utils/uuid/sole/sole.hpp"
namespace zwsd {
namespace core {
using namespace std;

class UUID {
 public:
  UUID() {
    sole::uuid u4 = sole::uuid4();
    value = u4.str();
  };
  ~UUID(){};
  const std::string &toString() { return value; };
 private:
  std::string value;
};
}  // namespace core
}  // namespace zwsd
