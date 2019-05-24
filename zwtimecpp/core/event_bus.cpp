//
// Created by zhaohe on 19-5-21.
//

#include "event_bus.hpp"
#include "event_bus_state.hpp"
#include "thread_state.hpp"
#include "exception_handle_center.hpp"
#include "zwtimecpp/core/interlog/simple_logger.hpp"
using namespace std;
using namespace zwsd;
using namespace core;

EventBus::EventBus() {

}
void EventBus::internal_initialize() {
	EventBusState::instance().getEvenAsyncHandleThread().reset(new Thread(
		"EventBus-EventHandleThread",
		[this]() {
			SimpleLogger::info("EventBus-EventHandledThread start");
		  auto &un_handled_events = EventBusState::instance().getBaseEvents();
		  while(1){
		  	    shared_ptr<BaseEvent> event;
				un_handled_events.wait_dequeue(event);
				if (event != nullptr){
					callHandler(event);
				}
				if (EventBusState::instance().isEventAsyncHandleStopFlag()){
					break;
				}
			};
		},
		Instance()));
}

void EventBus::onExistSync(Thread *thread, shared_ptr<BaseException> baseException) {
	if (baseException != nullptr){
		ExceptionHandleCenter::instance().postException(baseException);
	}

	//重启事件总线
	if (!EventBusState::instance().isEventAsyncHandleStopFlag()){
		//如果需要做些清理工作,在这里完成.
//		internal_initialize();
	}
	SimpleLogger::info("EventBus-EventHandledThread start");
}

void EventBus::regEventHandler(shared_ptr<EventHandler> handler) {
	if (handler != nullptr) {
		EventBusState::instance().getEventHandlers().push_back(handler);
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
	EventBusState::instance().getBaseEvents().enqueue(baseEvent);
}
void EventBus::callHandler(shared_ptr<BaseEvent> baseEvent) {
	auto handlers = EventBusState::instance().getEventHandlers();
	for (auto &var : handlers) {
		type_index index = typeid(*baseEvent);
		if (var->requiredEvent().find(index) != var->requiredEvent().end()) {
			var->onEvent(baseEvent);
		}
	}
}

