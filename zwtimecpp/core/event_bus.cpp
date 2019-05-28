//
// Created by zhaohe on 19-5-21.
//

#include "event_bus.hpp"
#include "zwtimecpp/core/base/system_state.hpp"
#include "exception_handle_center.hpp"
#include "zwtimecpp/core/base/interlog/simple_logger.hpp"
#include "zwtimecpp/core/helper/exception_helper.hpp"
using namespace std;
using namespace zwsd;
using namespace core;

EventBus::EventBus() {
	SimpleLogger::trace("EventBus");
}
void EventBus::internal_initialize() {
	evenAsyncHandleThread.reset(new Thread(
		"EventBus-EventHandleThread",
		[this]() {
		  busThreadRestartTimes = -1;
		  while (!eventAsyncHandleStopFlag) {
			  busThreadRestartTimes++;
			  SimpleLogger::info("EventBus-EventHandledThread start, restartTimes %d",busThreadRestartTimes);
			  //将捕获的异常抛给异常处理中心
			  throwAllExceptionToExceptionCenter(
				  [this]() {
					while (!eventAsyncHandleStopFlag) {
						shared_ptr<BaseEvent> event;
						baseEvents.wait_dequeue(event);
						if (event != nullptr) {
							callHandler(event);
						}
					};
				  }
			  );
		  }
		},
		Instance()));
}
void EventBus::onCatchException(Thread *thread, const std::exception &baseException) {
	ExceptionHandleCenter::instance().postException(baseException);
}
void EventBus::onExistSync(Thread *thread) {

}
void EventBus::regEventHandler(shared_ptr<EventHandler> handler) {
	if (handler != nullptr) {
		eventHandlers.push_back(handler);
	}
}
void EventBus::fireEventSync(shared_ptr<BaseEvent> baseEvent) {
	if (baseEvent == nullptr) {
		return;
	}
}
void EventBus::fireEventAsync(shared_ptr<BaseEvent> baseEvent) {
	if (baseEvent == nullptr) {
		return;
	}
	baseEvents.enqueue(baseEvent);
}
void EventBus::callHandler(shared_ptr<BaseEvent> baseEvent) {
	auto handlers = eventHandlers;
	for (auto &var : handlers) {
		type_index index = typeid(*baseEvent);
		if (var->requiredEvent().find(index) != var->requiredEvent().end()) {
			var->onEvent(baseEvent);
		}
	}
}
EventBus::~EventBus() {
	SimpleLogger::trace("~EventBus");
	eventAsyncHandleStopFlag = false;
	evenAsyncHandleThread->join();
}

