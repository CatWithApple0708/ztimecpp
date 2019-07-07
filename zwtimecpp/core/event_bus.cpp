//
// Created by zhaohe on 19-5-21.
//

#include "event_bus.hpp"
#include "system_state.hpp"
#include "zwtimecpp/core/base/interlog/simple_logger.hpp"
#include "zwtimecpp/core/constant.hpp"
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
                               set<type_index> requiredEvent, bool urgen) {
  regEventHandler(handler, requiredEvent, {}, urgen);
}
void EventBus::regEventHandler(shared_ptr<EventHandler> handler,
                               set<type_index> requiredEvent,
                               map<type_index, EventPriority_t> priority,
                               bool urgen) {
  quickFindMap_t *quickMap;
  mutex* cur_lock;
  if (urgen) {
    quickMap = &urgentEventHandlersQuickFind;
    cur_lock = &lock2_;
  } else {
    quickMap = &eventHandlersQuickFind;
    cur_lock = &lock_;
  }

  if (!evenAsyncHandleThread ||
      pthread_self() == evenAsyncHandleThread->getId()) {
    throw BaseException("Don't call regEventHandler in onEvent");
  }

  lock_guard<mutex> lock(*cur_lock);
  if (handler != nullptr) {
    //对于没有设置优先的设置默认优先级
    for (auto &typeindex : requiredEvent) {
      auto result = priority.find(typeindex);
      if (result == priority.end())
        priority.insert(make_pair(typeindex, DEFAULT_EVENT_PRIORITY));
    }

    handler->requiredEvent = requiredEvent;
    handler->requiredEventPriority = priority;
    eventHandlers.push_back(handler);

    for (auto &typeindex : requiredEvent) {
      auto &list = (*quickMap)[typeindex];
      list.push_back(handler);

      //从优先级高到优先级低
      sort(list.begin(), list.end(),
           [this, typeindex](const weak_ptr<EventHandler> &wa,
                             const weak_ptr<EventHandler> &wb) {
             shared_ptr<EventHandler> a = wa.lock();
             shared_ptr<EventHandler> b = wb.lock();
             if (!a) return false;
             if (!b) return true;
             EventPriority_t apriority = DEFAULT_EVENT_PRIORITY;
             EventPriority_t bpriority = DEFAULT_EVENT_PRIORITY;
             auto aFindresult = a->requiredEventPriority.find(typeindex);
             auto bFindresult = b->requiredEventPriority.find(typeindex);
             if (aFindresult != a->requiredEventPriority.end())
               apriority = aFindresult->second;
             if (bFindresult != b->requiredEventPriority.end())
               bpriority = bFindresult->second;
             if (apriority >= bpriority) {
               return true;
             }
             return false;
           });
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

  {
    type_index index = typeid(*baseEvent);
    lock_guard<mutex> lock(lock2_);
    auto handlers = urgentEventHandlersQuickFind.find(index);
    if (handlers != urgentEventHandlersQuickFind.end()) {
      for (auto &handler : handlers->second) {
        auto eventHandler = handler.lock();
        if (eventHandler) eventHandler->onEvent(baseEvent);
      }
    }
  }

  logger->trace("fireEventAsync {}", typeid(*baseEvent).name());
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
  {
    /**
     * @brief
     * 这里事件的调用顺序必须是顺序的，依次调度的．（因为队列中的内容已经按照优先级排序好了）
     *
     * @return lock_guard<mutex>
     */
    logger->trace("callHandler {}", typeid(*baseEvent).name());
    type_index index = typeid(*baseEvent);
    lock_guard<mutex> lock(lock_);
    auto handlers = eventHandlersQuickFind.find(index);
    if (handlers != eventHandlersQuickFind.end()) {
      for (auto &handler : handlers->second) {
        auto eventHandler = handler.lock();
        if (eventHandler) eventHandler->onEvent(baseEvent);
      }
    }
  }
}
EventBus::~EventBus() {
  baseEvents.enqueue(nullptr);
  eventAsyncHandleStopFlag = true;
  evenAsyncHandleThread->join();
}
