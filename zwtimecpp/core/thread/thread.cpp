//
// Created by zhaohe on 19-5-21.
//

#include "thread.hpp"
#include <atomic>
#include <mutex>
#include <zwtimecpp/core/base/interlog/simple_logger.hpp>
#include "unistd.h"
#include "zwtimecpp/core/exception/base_exception.hpp"
#include "zwtimecpp/core/exception/null_expection.hpp"
#include "zwtimecpp/core/exception/system_or_third_lib_exception.hpp"
#include "zwtimecpp/core/exception/thread_unjointed_exception.hpp"
#include "zwtimecpp/core/exception/unkown_type_exception.hpp"
#include "zwtimecpp/core/system_state.hpp"
#include "zwtimecpp/core/utils/concurrentqueue/blockingconcurrentqueue.h"
#include "zwtimecpp/core/utils/fatall_error.hpp"
#include "zwtimecpp/core/utils/signal.hpp"
// #include <zwtimecpp/core/helper/exception_helper.hpp>
using namespace std;
using namespace zwsd;
using namespace core;
using namespace moodycamel;
// namespace
//{
// class ThreadMonitor
//{
//	unique_ptr<thread> threadW;
//	BlockingConcurrentQueue<shared_ptr<ThreadInfo>> threadInfoQ;
//	bool stopFlag = false;
//
// public:
//	ThreadMonitor()
//	{
//		SimpleLogger::info("CoreThreadMonitor initialized...");
//		threadW.reset(new thread([this]() {
//			CoreSystemState::Instance().createThreadInfo("CoreThreadMonitor-Thread");
//			while (1)
//			{
//				shared_ptr<ThreadInfo> threadInfo = nullptr;
//				threadInfoQ.wait_dequeue(threadInfo);
//
//				if (threadInfo != nullptr)
//				{
//					//   if (thread->getListener().lock()) {
//					// 	  if
//(thread->getListener().lock())
//{
//					//
// thread->getListener().lock()->onExistSync(thread);
//					// 	  } else {
//					// 	  }
//					//   }
//				}
//
//				//直到所有我们创建的线程退出后,这个线程才真正的退出.
//				if (stopFlag == true &&
// CoreSystemState::Instance().getOurThreadNum() == 0)
//				{
//					break;
//				}
//			}
//		}));
//	}
//	static ThreadMonitor &Instance()
//	{
//		static ThreadMonitor value;
//		return value;
//	}
//	void pushExitedThread(Thread *thread)
//	{
//		// threads.enqueue(thread);
//	}
//	~ThreadMonitor()
//	{
//		// stopFlag = true;
//		// threads.enqueue(nullptr);
//		// threadW->join();
//	}
//};
// static ThreadMonitor &threadMonitor = ThreadMonitor::Instance();
//} // namespace
Thread::Thread(std::function<void()> run) { Thread("notSet", run); }
Thread::Thread(string name, function<void()> run) {
  this->run = run;
  this->name = name;
  if (this->run == nullptr) {
    throw NullException("Create Thread run == nullptr");
  }

  workThread.reset(new thread([this]() {
    this->id = pthread_self();
    CoreSystemState::Instance().createThreadInfo(this->name);
    this->threadInitialized = true;

    try {
      this->run();
    } catch (const std::exception &exception) {
      auto exHandler = CoreSystemState::Instance().getDefaultExceptionHandler();
      if (exHandler)
        exHandler->onExceptionSync(exception);
      else
        throw exception;
    } catch (...) {
      /**
       *	特殊情况只知道存在异常但异常是什么不知道
       *
       *	TODO:处理
       *线程独有的打断异常,当调用pthread_yield时产生的异常,这个异常要抛出交给系统处理,属于线程的正常退出,如果截断会导致程序退出.
       */

      UnkownTypeException unkownTypeException("unkownException from thread");
      unkownTypeException.setLoseInfo(true);
      auto exHandler = CoreSystemState::Instance().getDefaultExceptionHandler();
      if (exHandler)
        exHandler->onExceptionSync(unkownTypeException);
      else
        throw unkownTypeException;
    }
  }));

  while (!threadInitialized) {
    usleep(1);
  }
  CoreSystemState::Instance().increaseOurThreadNum();
}
// void Thread::sleep() {
//   shared_ptr<ThreadInfo> threadInfo =
//       CoreSystemState::Instance().getThreadInfo(pthread_self());
//   if (threadInfo)
//     threadInfo->signal.sleep();
//   else
//     throw BaseException(BaseException::format1024(
//         "Thread %s not call CoreSystemState::Instance().createThreadInfo(name)",
//         to_string(pthread_self()).c_str()));
// }
// void Thread::sleepForMs(int ms) {
//   shared_ptr<ThreadInfo> threadInfo =
//       CoreSystemState::Instance().getThreadInfo(pthread_self());
//   if (threadInfo)
//     threadInfo->signal.sleep_for_us(ms * 1000);
//   else
//     throw BaseException(BaseException::format1024(
//         "Thread %s not call CoreSystemState::Instance().createThreadInfo(name)",
//         to_string(pthread_self()).c_str()));
// }

void Thread::wake(pthread_t id) {
  shared_ptr<ThreadInfo> threadInfo =
      CoreSystemState::Instance().getThreadInfo(id);
  if (threadInfo)
    threadInfo->signal.notify();
  else
    throw BaseException(BaseException::format1024(
        "Thread %s not call CoreSystemState::Instance().createThreadInfo(name)",
        to_string(pthread_self()).c_str()));
}

void Thread::wake() {
  if (!hasJointd) {
    shared_ptr<ThreadInfo> threadInfo =
        CoreSystemState::Instance().getThreadInfo(this->id);
    if (threadInfo)
      threadInfo->signal.notify();
    else
      throw BaseException(BaseException::format1024(
          "Thread %s not call "
          "CoreSystemState::Instance().createThreadInfo(name)",
          to_string(pthread_self()).c_str()));
  }else{
    logger->warn("wake fail Thread {} has been joined", name);
  }
}
/**
 * @brief
 * 这里不将变量threadExitFlag放在Thread对象中，是因为很多使用用户的使用方式如下
 *
 * uniq_ptr<Thread> thread(new Thread("name",[this](){
 *  while(thread->getExitFlag()){}//这种情况会暴段错误，因为thread对象可能并没有初始化完成.
 * }));
 *
 * @return true
 * @return false
 */
// bool Thread::getExitFlag() {
//   shared_ptr<ThreadInfo> threadInfo =
//       CoreSystemState::Instance().getThreadInfo(pthread_self());
//   if (threadInfo)
//     return threadInfo->threadExitFlag;
//   else
//     throw BaseException(BaseException::format1024(
//         "Thread %s not call CoreSystemState::Instance().createThreadInfo(name)",
//         to_string(pthread_self()).c_str()));
//   return false;
// };

void Thread::join(function<void()> wakeFunc) {
  shared_ptr<ThreadInfo> threadInfo =
      CoreSystemState::Instance().getThreadInfo(this->id);
  if (!threadInfo)
    throw BaseException(BaseException::format1024(
        "Thread %s not call CoreSystemState::Instance().createThreadInfo(name)",
        to_string(pthread_self()).c_str()));

  threadInfo->threadExitFlag = true;
  threadInfo->signal.notify();
  if (wakeFunc) wakeFunc();
  workThread->join();
  /**
   * 之所以在这里清理线程信息，而非在析构中清理线程信息的原因是当某个线程被join之后其pthreadId可能会在创建新的线程的时候被使用
   * 如果在析构函数中清理，可能会导致新创建的线程的ThreadInfo被清理掉
   */
  CoreSystemState::Instance().clearThreadInfo(id);
  CoreSystemState::Instance().decreaseOurThreadNum();
  hasJointd = true;
};

Thread::~Thread() {
  if (!hasJointd) {
    FatallError(logger, fmt::format("Thread {} unjoin ", name));
  }

}
const shared_ptr<BaseException> &Thread::getExitException() const {
  return exitException;
}
pthread_t Thread::getId() const { return id; }
void Thread::callDefaultExceptionHandler(const std::exception &exception) {
  auto handler = CoreSystemState::Instance().getDefaultExceptionHandler();
  if (handler) {
    handler->onExceptionSync(exception);
  } else {
    throw exception;
  }
}

ThisThread::ThisThread() {
  threadInfo =
      CoreSystemState::Instance().getThreadInfo(pthread_self());
  if (!threadInfo) {
    ENABLE_LOGGER(ThisThread);
    FatallError(logger,fmt::format(
                "Thread {} not call "
                "CoreSystemState::Instance().createThreadInfo(name)",pthread_self()));
  }
};

bool ThisThread::getExitFlag() { return threadInfo->threadExitFlag; }
void ThisThread::sleep() { threadInfo->signal.sleep(); }
void ThisThread::sleepForMs(int ms) {
  threadInfo->signal.sleep_for_us(ms * 1000);
}
