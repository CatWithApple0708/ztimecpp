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

EventBus::EventBus() {}
void EventBus::internal_initialize() {
  evenAsyncHandleThread.reset(
      new Thread("EventBus-EventHandleThread", [this]() {
        busThreadRestartTimes = -1;
        while (!eventAsyncHandleStopFlag) {
          busThreadRestartTimes++;
          SimpleLogger::info(
              "EventBus-EventHandledThread start, restartTimes %d",
              busThreadRestartTimes);
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
                auto exHandler =
                    CoreSystemState::Instance().getDefaultExceptionHandler();
                if (exHandler)
                  exHandler->onExceptionSync(exception);
                else
                  throw exception;
              });
        }
      }));
}

void EventBus::regEventHandler(shared_ptr<EventHandler> handler,
                               set<type_index> requiredEvent) {
                                 
  if (!evenAsyncHandleThread ||
      pthread_self() == evenAsyncHandleThread->getId()) {
    throw BaseException("Don't call regEventHandler in onEvent");
  }

  lock_guard<mutex> lock(lock_);
  if (handler != nullptr) {
    handler->requiredEvent = requiredEvent;
    eventHandlers.push_back(handler);

    for (auto &typeindex : requiredEvent) {
      eventHandlersQuickFind[typeindex].push_back(handler);
    }
  }
}
void EventBus::fireEventSync(shared_ptr<BaseEvent> baseEvent) {
  if (baseEvent == nullptr) {
    return;
  }
  callHandler(baseEvent);
}
/**
 * @brief
 * TODO:优化事件调度,每个监听者独享一个事件队列
 * @param baseEvent
 */
void EventBus::fireEventAsync(shared_ptr<BaseEvent> baseEvent) {
  if (baseEvent == nullptr) {
    return;
  }
  baseEvents.enqueue(baseEvent);
}

void EventBus::callHandler(shared_ptr<BaseEvent> baseEvent) {
//简单方法查找handler调用
#if 0
  auto handlers = eventHandlers;
  for (auto &var : handlers) {
    shared_ptr<EventHandler> eventHandler = var.lock();
    if (eventHandler) {
      type_index index = typeid(*baseEvent);
      if (eventHandler->requiredEvent.find(index) !=
          eventHandler->requiredEvent.end()) {
        eventHandler->onEvent(baseEvent);
      }
    }
  }
#endif
  type_index index = typeid(*baseEvent);
  {
    lock_guard<mutex> lock(lock_);
    for (auto &handler : eventHandlersQuickFind[index]) {
      auto eventHandler = handler.lock();
      if (eventHandler) eventHandler->onEvent(baseEvent);
    }
  }
}
EventBus::~EventBus() {
  baseEvents.enqueue(nullptr);
  eventAsyncHandleStopFlag = true;
  evenAsyncHandleThread->join();
}
