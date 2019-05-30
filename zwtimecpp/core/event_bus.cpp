//
// Created by zhaohe on 19-5-21.
//

#include "event_bus.hpp"
#include "system_state.hpp"
#include "zwtimecpp/core/base/interlog/simple_logger.hpp"
#include "zwtimecpp/core/exception/exception_helper.hpp"
using namespace std;
using namespace zwsd;
using namespace core;

EventBus::EventBus() {
}
void EventBus::internal_initialize() {
	evenAsyncHandleThread.reset(new Thread(
		"EventBus-EventHandleThread",
		[this]() {
		  busThreadRestartTimes = -1;
		  while (!eventAsyncHandleStopFlag) {
			  busThreadRestartTimes++;
			  SimpleLogger::info("EventBus-EventHandledThread start, restartTimes %d", busThreadRestartTimes);
			  //将捕获的异常抛给异常处理中心
			  tryCatchException(
				  [this]() {
					while (!eventAsyncHandleStopFlag) {
						shared_ptr<BaseEvent> event;
						baseEvents.wait_dequeue(event);
						if (event != nullptr) {
							callHandler(event);
						}
					};
				  },
				  [this](const exception &exception) {
					auto exHandler = SystemState::Instance().getDefaultExceptionHandler();
					if (exHandler)
						exHandler->onExceptionSync(exception);
					else
						throw exception;
				  }
			  );
		  }
		}));
}

void EventBus::regEventHandler(shared_ptr<EventHandler> handler, set<std::type_index> requiredEvent) {
	if (handler != nullptr) {
		handler->requiredEvent = requiredEvent;
		eventHandlers.push_back(handler);
	}
}
void EventBus::fireEventSync(shared_ptr<BaseEvent> baseEvent) {
	if (baseEvent == nullptr) {
		return;
	}
	callHandler(baseEvent);

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
		shared_ptr<EventHandler> eventHandler = var.lock();
		if (eventHandler) {
			type_index index = typeid(*baseEvent);
			if (eventHandler->requiredEvent.find(index) != eventHandler->requiredEvent.end()) {
				eventHandler->onEvent(baseEvent);
			}
		}
	}
}
EventBus::~EventBus() {
	eventAsyncHandleStopFlag = false;
	evenAsyncHandleThread->join();
}

