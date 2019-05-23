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
#include "zwtimecpp/core/exception/null_expection.hpp"
namespace zwsd {
namespace core {
using namespace std;

namespace internal{
/*这个方法只是为了解决无法在Core中调用throwException*/
template<class T>
static void inline throwException2(const string &msg) {
	throwException<T>(msg);
};
}

class Core {
	list<ExceptionHandler *> exceptionHandlers;
	Core() {}
	static shared_ptr<Core> &instance() {
		static shared_ptr<Core> value;
		return value;
	}
  public:
	static shared_ptr<Core> Instance() {
		if (instance() == nullptr) {
			internal::throwException2<NullException>("Core has't been initialized Core::instance == nullptr");
		}
		return instance();
	}
	static void initialize() {
		if (instance() != nullptr) {
			internal::throwException2<BaseException>("Core has been initialized");
		}
		instance().reset(new Core());
	}

//exception api
	void regExceptionHandler(ExceptionHandler *handler);
	void throwException(shared_ptr<exception> expec);
	void throwException(shared_ptr<BaseException> expec);

//eventBus api
	void fireEventSync(shared_ptr<BaseEvent> baseEvent);
	void fireEventAsync(shared_ptr<BaseEvent> baseEvent);
	template<class T>
	void regEventHandler(shared_ptr<EventHandler<T>> handler) {}

};
}
}


