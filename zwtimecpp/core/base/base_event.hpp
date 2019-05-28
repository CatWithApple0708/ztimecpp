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
#include "zwtimecpp/core/base/object.hpp"
#include "zwtimecpp/core/exception/base_exception.hpp"
#include "zwtimecpp/core/base/object.hpp"
#include "zwtimecpp/core/base/interlog/simple_logger.hpp"

namespace zwsd {
namespace core{
using namespace std;

class BaseEvent {
	shared_ptr<Object> object;
  public:
	/**
	 * @param object object != null 如果等于null 则抛出Null异常
	 */
	BaseEvent(shared_ptr<Object> object){
		this->object = object;
	}
	BaseEvent(){

	}
	~BaseEvent(){
		SimpleLogger::trace("~BaseEvent");
	};
};
}
}


