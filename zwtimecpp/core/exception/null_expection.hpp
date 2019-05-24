//
// Created by zhaohe on 19-5-23.
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
namespace core{
using namespace std;

class NullException : public BaseException{
  public:
	NullException(const string &description) : BaseException(description) {}
};
}
}


