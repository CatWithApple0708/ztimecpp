//
// Created by zhaohe on 19-5-21.
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

class ExceptionHandler {
  public:
	virtual void onExceptionSync(shared_ptr<BaseException> expec) {};
	virtual void onExceptionAsync(shared_ptr<BaseException> expec) {};
	~ExceptionHandler() {};
};
}
}


