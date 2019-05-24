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
#include "zwtimecpp/core/event/base_event.hpp"
#include "zwtimecpp/core/exception/null_expection.hpp"
#include "zwtimecpp/core/thread/thread.hpp"
#include "zwtimecpp/core/event_bus_state.hpp"
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

class EventBus :public ThreadStateListener{
	EventBus();
	static shared_ptr<EventBus> &instance() {
		static shared_ptr<EventBus> value;
		return value;
	}
  public:
	static shared_ptr<EventBus> Instance() {
		if (instance() == nullptr) {
			internal::throwException2<NullException>("EventBus has't been initialized EventBus::instance == nullptr");
		}
		return instance();
	}

	//call it in core.hpp
	static void initialize() {
		if (instance() != nullptr) {
			internal::throwException2<BaseException>("EventBus has been initialized");
		}
		instance().reset(new EventBus());
		instance()->internal_initialize();
	}
//eventBus api
	void fireEventSync(shared_ptr<BaseEvent> baseEvent);
	void fireEventAsync(shared_ptr<BaseEvent> baseEvent);
	void onExistSync(Thread *thread, shared_ptr<BaseException> baseException) override;
	void regEventHandler(shared_ptr<EventHandler> handler);

  private:
	void internal_initialize();
	void callHandler(shared_ptr<BaseEvent> event);
	void start();
};
}
}


