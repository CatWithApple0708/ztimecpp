//
// Created by zhaohe on 19-5-21.
//

#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <sstream>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <vector>
#include "utils/concurrentqueue/blockingconcurrentqueue.h"
#include "zwtimecpp/core/base/base_event.hpp"
#include "zwtimecpp/core/event_priority.hpp"
#include "zwtimecpp/core/exception/null_expection.hpp"
#include "zwtimecpp/core/logger/logger.hpp"
#include "zwtimecpp/core/thread/thread.hpp"
namespace zwsd {
namespace core {
using namespace moodycamel;
using namespace std;
class EventBus;
typedef map<type_index, EventPriority_t> EventPriorityMap_t;

static inline pair<type_index, EventPriority_t> zmake_pair(
    type_index typeindex, EventPriority_t priority) {
  return move(make_pair(typeindex, priority));
}

class EventHandler : public Object {
  set<type_index> requiredEvent;
  map<type_index, EventPriority_t> requiredEventPriority;
  friend EventBus;

 public:
  /**
   * \brief Default constructor that enforces the template type
   */
  EventHandler() {}
  /**
   * \brief Empty virtual destructor
   */
  virtual ~EventHandler() {}
  /**
   * \brief Pure virtual method for implementing the body of the listener
   *
   * @param The event instance
   */
  virtual void onEvent(shared_ptr<BaseEvent>) = 0;
};

class EventBus {
  ENABLE_LOGGER(EventBus);
  typedef map<type_index, vector<weak_ptr<EventHandler>>> quickFindMap_t;
  BlockingConcurrentQueue<shared_ptr<BaseEvent>> baseEvents;
  /**
   * @TODO
   *  优化存储方式,map(key = event, value =
   * handlers)去存储handler,加速事件处理速度
   */
  list<weak_ptr<EventHandler>> eventHandlers;
  quickFindMap_t eventHandlersQuickFind;
  quickFindMap_t
      urgentEventHandlersQuickFind;  //时效高的队列，要求所有的监听者，均以线程的形式处理事件
  bool eventAsyncHandleStopFlag = false;
  int busThreadRestartTimes = 0;
  mutex lock_;
  mutex lock2_;

 private:
  EventBus();
  static shared_ptr<EventBus> &instance() {
    static shared_ptr<EventBus> value;
    return value;
  }
  unique_ptr<Thread> evenAsyncHandleThread;
  /**
   * @brief 暂时不支持同步事件,同步事件存在很大的风险
   *
   * @param baseEvent
   */
  void fireEventSync(shared_ptr<BaseEvent> baseEvent);

 public:
  static shared_ptr<EventBus> Instance() {
    if (instance() == nullptr) {
      throw NullException(
          "EventBus has't been initialized EventBus::instance == nullptr");
    }
    return instance();
  }

  // call it in core.hpp
  static void initialize() {
    if (instance() != nullptr) {
      throw BaseException("EventBus has been initialized");
    }
    instance().reset(new EventBus());
    instance()->internal_initialize();
  }
  // eventBus api
  /**
   * @brief  对于　urgen　== true的监听者来说，是同步事件调用,所以就要求
   * urgen==true的监听者要尽可能的少，同时，事件处理要异步
   * @note
   * @param  baseEvent:
   * @retval None
   */
  void fireEventAsync(shared_ptr<BaseEvent> baseEvent);

  /**
   * @brief
   *
   * @param handler
   * @param requiredEvent
   * @WARNING: 不要在EventHandler::onEvent回掉中调用这个方法,会造成死锁.
   * @Usage
   *    class TestEvent1 :public BaseEvent
   *    {};
   *    class TestEvent2 :public BaseEvent
   *    {};
   *    regEventHandler(handler, {typeid(TestEvent1), typeid(TestEvent2)});
   */
  void regEventHandler(shared_ptr<EventHandler> handler,
                       set<type_index> requiredEvent, bool urgen = false);

  void regEventHandler(shared_ptr<EventHandler> handler,
                       set<type_index> requiredEvent,
                       map<type_index, EventPriority_t> priority,
                       bool urgen = false);

  // override ThreadStateListener
  ~EventBus();

 private:
  void internal_initialize();
  void callHandler(shared_ptr<BaseEvent> event);
};
}  // namespace core
}  // namespace zwsd
