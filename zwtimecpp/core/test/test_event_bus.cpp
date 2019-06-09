
#include "zwtimecpp/core/core.hpp"
#include "zwtimecpp/core/test/test_utils/tester_manager.hpp"
#include "zwtimecpp/core/utils/memory_utils.hpp"
namespace {
using namespace std;
using namespace zwsd;
using namespace backward;
using namespace core;

class TestEvent1 : public BaseEvent {};

class TestEvent2 : public BaseEvent {};

class TestEvent3 : public BaseEvent {};

class EventHandlerImpl : public EventHandler {
 public:
  virtual void onEvent(shared_ptr<BaseEvent> e) {
    if (instanceof <TestEvent1>(e)) {
      SimpleLogger::info("success catch TestEvent1");
    }

    if (instanceof <TestEvent2>(e)) {
      SimpleLogger::info("success catch TestEvent2");
    }

    if (instanceof <TestEvent3>(e)) {
      SimpleLogger::error("Error catch TestEvent3");
    }
    usleep(100 * 1000);
  };
};

class TestEventBus : public TestElement {
 public:
  TestEventBus() {}

 public:
  void run(int argc, const char **argv) override {
    //测试注册异常回调
    Core::initialize();
    {
      shared_ptr<EventHandler> handler = make_shared<EventHandlerImpl>();
      Core::Instance()->getEventBus()->regEventHandler(
          handler, {typeid(TestEvent1), typeid(TestEvent2)});
      SimpleLogger::info("listen event1 event2");

    //   SimpleLogger::info("onEvent testEventSync");
      // Core::Instance()->getEventBus()->fireEventSync(make_shared<TestEvent1>());
      // Core::Instance()->getEventBus()->fireEventSync(make_shared<TestEvent2>());
      // Core::Instance()->getEventBus()->fireEventSync(make_shared<TestEvent3>());
    //   SimpleLogger::info("onEvent testEventSync end");
    //   SimpleLogger::info("--");
      SimpleLogger::info("onEvent testEventAsync");
      Core::Instance()->getEventBus()->fireEventAsync(
          make_shared<TestEvent1>());
      SimpleLogger::info("fire event1");
      Core::Instance()->getEventBus()->fireEventAsync(
          make_shared<TestEvent2>());
      SimpleLogger::info("fire event2");
      Core::Instance()->getEventBus()->fireEventAsync(
          make_shared<TestEvent3>());
      SimpleLogger::info("fire event3");

      while (1) sleep(1);
    }
  }
  void run() override {}
};

class EventHandlerImpl1 : public EventHandler {
 public:
  virtual void onEvent(shared_ptr<BaseEvent> e) {
    if (instanceof <TestEvent1>(e)) {
      SimpleLogger::info("EventHandlerImpl1 success catch TestEvent1");
    }

    if (instanceof <TestEvent2>(e)) {
      SimpleLogger::info("EventHandlerImpl1 success catch TestEvent2");
    }
    usleep(100 * 1000);
  };
};
class EventHandlerImpl2 : public EventHandler {
 public:
  virtual void onEvent(shared_ptr<BaseEvent> e) {
    if (instanceof <TestEvent1>(e)) {
      SimpleLogger::info("EventHandlerImpl2 success catch TestEvent1");
    }

    if (instanceof <TestEvent2>(e)) {
      SimpleLogger::info("EventHandlerImpl2 success catch TestEvent2");
    }
    usleep(100 * 1000);
  };
};



class TestEventBusPority : public TestElement {
 public:
  TestEventBusPority() {}

 public:
  void run(int argc, const char **argv) override {
    //测试注册异常回调
    Core::initialize();
    {
      shared_ptr<EventHandler> handler1 = make_shared<EventHandlerImpl1>();
      shared_ptr<EventHandler> handler2 = make_shared<EventHandlerImpl2>();

      EventPriorityMap_t priority1map = {
        zmake_pair(typeid(TestEvent1), EventPriority_t::Hight)
      };
      EventPriorityMap_t priority2map = {
          zmake_pair(typeid(TestEvent2), EventPriority_t::Hight)};

      Core::Instance()->getEventBus()->regEventHandler(
          handler1, {typeid(TestEvent1), typeid(TestEvent2)}, priority1map);
      Core::Instance()->getEventBus()->regEventHandler(
          handler2, {typeid(TestEvent1), typeid(TestEvent2)}, priority2map);


      SimpleLogger::info("onEvent testEventAsync");
      Core::Instance()->getEventBus()->fireEventAsync(
          make_shared<TestEvent1>());
      SimpleLogger::info("fire event1");
      Core::Instance()->getEventBus()->fireEventAsync(
          make_shared<TestEvent2>());
      SimpleLogger::info("fire event2");
      Core::Instance()->getEventBus()->fireEventAsync(
          make_shared<TestEvent3>());
      SimpleLogger::info("fire event3");

      while (1) sleep(1);
    }
  }
  void run() override {}
};

ENABLE_TEST(TestEventBus);
ENABLE_TEST(TestEventBusPority);

}  // namespace