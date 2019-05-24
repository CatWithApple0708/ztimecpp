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
#include <typeindex>
#include <zwtimecpp/core/thread/thread.hpp>
#include "zwtimecpp/core/utils/signal.hpp"
#include "zwtimecpp/core/utils/concurrentqueue/blockingconcurrentqueue.h"

namespace zwsd {
namespace core {
using namespace std;
using namespace moodycamel;

class EventHandler {
  public:
	/**
	 * \brief Default constructor that enforces the template type
	 */
	EventHandler() {
	}
	/**
	 * \brief Empty virtual destructor
	 */
	virtual ~EventHandler() { }
	/**
	 * \brief Pure virtual method for implementing the body of the listener
	 *
	 * @param The event instance
	 */
	virtual void onEvent(shared_ptr<BaseEvent> ) = 0;

	virtual const set<std::type_index>& requiredEvent() = 0;
};

class EventBusState {
	BlockingConcurrentQueue<shared_ptr<BaseEvent>> baseEvents;
	list<shared_ptr<EventHandler>> eventHandlers;
	shared_ptr<Thread> evenAsyncHandleThread;
	bool eventAsyncHandleStopFlag = false;
	EventBusState() {}
  public:
	static EventBusState &instance() {
		static EventBusState value;
		return value;
	}

  public:
	BlockingConcurrentQueue<shared_ptr<BaseEvent>> &getBaseEvents() {
		return baseEvents;
	}
	list<shared_ptr<EventHandler>> &getEventHandlers() {
		return eventHandlers;
	}
	shared_ptr<Thread> &getEvenAsyncHandleThread() {
		return evenAsyncHandleThread;
	}

	bool isEventAsyncHandleStopFlag() const {
		return eventAsyncHandleStopFlag;
	}
	void setEventAsyncHandleStopFlag(bool eventAsyncHandleStopFlag) {
		EventBusState::eventAsyncHandleStopFlag = eventAsyncHandleStopFlag;
	}
};
}
}


