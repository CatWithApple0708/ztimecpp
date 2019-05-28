//
// Created by zhaohe on 19-5-28.
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
#include "object.hpp"
namespace zwsd {
namespace core {
using namespace std;

class ExceptionHandler : public Object {
  public:
	virtual void onExceptionSync(const std::exception &expec) = 0;
	~ExceptionHandler() {};
};
}
}


