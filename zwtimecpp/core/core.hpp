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
#include "zwtimecpp/core/exception/exception_handler.hpp"
#include "zwtimecpp/core/event/base_event.hpp"
#include "zwtimecpp/core/event/event_handler.hpp"


namespace zwsd {
namespace core{
using namespace std;



class Core {
	list<ExceptionHandler*> exceptionHandlers;
	Core(){}
  public:
	static Core &instance(){
		static Core core;
		return core;
	}

	//exception api
	void regExceptionHandler(ExceptionHandler* handler);
	void throwException(shared_ptr<exception> expec);
	void throwException(shared_ptr<BaseException> expec);

	//event api
	void fireEventSync(shared_ptr<BaseEvent> baseEvent);
	void fireEventAsync(shared_ptr<BaseEvent> baseEvent);
	template <class T>
	void regEventHandler(shared_ptr<EventHandler<T>> handler){}


};
}
}


