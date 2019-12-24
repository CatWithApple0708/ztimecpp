#include "zwtimecpp/core/logger/logger.hpp"
#include "zwtimecpp/core/test/test_utils/runner_manager.hpp"
#include "zwtimecpp/core/thread/thread.hpp"
#include "zwtimecpp/core/utils/argh/argh.h"
#include "zwtimecpp/core/utils/better-enums/enum.h"
#include "zwtimecpp/core/utils/memory_utils.hpp"
#include "zwtimecpp/core/utils/nlohmann/json.hpp"

#include <mutex>
#include "zwtimecpp/core/utils/lock_helper.hpp"

#include "zwtimecpp/core/logger/func_call.hpp"

using namespace std;
using namespace zwsd;
using namespace core;

class TestTryLockHelper : public Runner {
  ENABLE_LOGGER(TestTryLockHelper);
  recursive_mutex lock_;

 public:
  virtual void run(int argc, const char **argv) override;
  virtual string introduction(logger_t logForHelp) override { return ""; }

  void func1() {
    TRY_LOCK_RECURSIVE_MUTEX(lock_);
    ZFUNC_CALL_INFO(ZVOID);
    func2();
  }
  void func2() {
    TRY_LOCK_RECURSIVE_MUTEX(lock_);
    ZFUNC_CALL_INFO(ZVOID);
    func3();
  }
  void func3() {
    TRY_LOCK_RECURSIVE_MUTEX(lock_);
    ZFUNC_CALL_INFO(ZVOID);
    sleep(1);
  }
};

void TestTryLockHelper::run(int argc, const char **argv) {
  //命令行参数demo ./runner_main TestTryLockHelper -n name
  //--string_full_name -b bool_value -i int_value

  //
  unique_ptr<Thread> thread(
      new Thread("TestTryLockHelper", [&]() { func1(); }));
  func1();

  ThisThread().sleep();
}

ENABLE_TEST2(TestTryLockHelper, "测试锁助手")