//
// Created by zhaohe on 19-5-24.
//

#pragma once
#include <memory>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include "zwtimecpp/core/exception/base_exception.hpp"
namespace zwsd {
namespace core {
using namespace std;
class ThreadUnjointedException : public BaseException{
  public:
	ThreadUnjointedException(const string &description) : BaseException(description) {}
};
}
}


