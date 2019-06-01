//
// Created by zhaohe on 19-5-21.
//

#pragma once
#include "utils/concurrentqueue/blockingconcurrentqueue.h"
#include "zwtimecpp/core/base/base_event.hpp"
#include "zwtimecpp/core/exception/null_expection.hpp"
#include "zwtimecpp/core/thread/thread.hpp"
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <vector>
namespace zwsd {
namespace core {
using namespace moodycamel;
using namespace std;
class EventBus;
class EventHandler : public Object {
    set<std::type_index> requiredEvent;
    friend EventBus;

  public:
    /**
	 * \brief Default constructor that enforces the template type
	 */
    EventHandler() {
    }
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
    BlockingConcurrentQueue<shared_ptr<BaseEvent>> baseEvents;
    /**
     * @TODO
     *  优化存储方式,map(key = event, value = handlers)去存储handler,加速事件处理速度
     */
    list<weak_ptr<EventHandler>> eventHandlers;
    bool eventAsyncHandleStopFlag = false;
    int busThreadRestartTimes = 0;

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
            throw NullException("EventBus has't been initialized EventBus::instance == nullptr");
        }
        return instance();
    }

    //call it in core.hpp
    static void initialize() {
        if (instance() != nullptr) {
            throw BaseException("EventBus has been initialized");
        }
        instance().reset(new EventBus());
        instance()->internal_initialize();
    }
    //eventBus api
    void fireEventAsync(shared_ptr<BaseEvent> baseEvent);

    /**
     * @brief 
     * 
     * @param handler 
     * @param requiredEvent 
     * 
     * @Usage
     *    class TestEvent1 :public BaseEvent
     *    {};
     *    class TestEvent2 :public BaseEvent
     *    {};
		 *    regEventHandler(handler, {typeid(TestEvent1), typeid(TestEvent2)});
     */
    void regEventHandler(shared_ptr<EventHandler> handler, set<std::type_index> requiredEvent);

    //override ThreadStateListener
    ~EventBus();

  private:
    void internal_initialize();
    void callHandler(shared_ptr<BaseEvent> event);
};
} // namespace core
} // namespace zwsd
