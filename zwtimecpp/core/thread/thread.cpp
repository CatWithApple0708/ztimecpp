//
// Created by zhaohe on 19-5-21.
//

#include "thread.hpp"
#include "zwtimecpp/core/exception/base_exception.hpp"
#include "zwtimecpp/core/exception_handle_center.hpp"
#include "zwtimecpp/core/exception/system_or_third_lib_exception.hpp"
#include "zwtimecpp/core/exception/unkown_type_exception.hpp"
#include "zwtimecpp/core/exception/thread_unjointed_exception.hpp"
#include "zwtimecpp/core/exception/null_expection.hpp"
#include "zwtimecpp/core/utils/signal.hpp"
#include "zwtimecpp/core/thread_state.hpp"
#include "unistd.h"
#include "zwtimecpp/core/utils/concurrentqueue/blockingconcurrentqueue.h"
#include <mutex>
#include <atomic>
#include <zwtimecpp/core/interlog/simple_logger.hpp>
#include <zwtimecpp/core/helper/exception_helper.hpp>
using namespace std;
using namespace zwsd;
using namespace core;
using namespace moodycamel;
namespace {

class ThreadMonitor {
	unique_ptr<thread> threadMonitor;
	BlockingConcurrentQueue<Thread *> threads;
	bool stopFlag = false;

  public:
	ThreadMonitor() {
		SimpleLogger::info("CoreThreadMonitor initialized...");
		threadMonitor.reset(new thread([this]() {
		  ThreadState::Instance().setThreadName(pthread_self(), "CoreThreadMonitor-Thread");
		  while (1) {
			  Thread *thread = nullptr;
			  threads.wait_dequeue(thread);
			  if (thread != nullptr) {
				  if (thread->getListener()) {
					  if (thread->getListener()) {
						  throwAllExceptionToExceptionCenter([&]() {
							thread->getListener()->onExistSync(thread, thread->getExitException());
						  });
					  } else {
						  ExceptionHandleCenter::instance().postException(thread->getExitException());
					  }
				  }
			  }
			  //直到所有我们创建的线程退出后,这个线程才真正的退出.
			  if (stopFlag == true && ThreadState::Instance().getOurThreadNum() == 0) {
				  break;
			  }
		  }
		}));
	}
	static ThreadMonitor &Instance() {
		static ThreadMonitor value;
		return value;
	}
	void pushExitedThread(Thread *thread) {
		threads.enqueue(thread);
	}
	~ThreadMonitor() {
		stopFlag = true;
		threads.enqueue(nullptr);
		threadMonitor->join();
	}
};
static ThreadMonitor& threadMonitor = ThreadMonitor::Instance();
} // namespace
Thread::Thread(std::function<void()> run) {
	Thread("notSet", run, nullptr);
}
Thread::Thread(string name, function<void()> run, shared_ptr<ThreadStateListener> listener) {
	this->listener = listener;
	this->run = run;
	this->name = name;
	if (this->run == nullptr) {
		throwException<NullException>("Create Thread run == nullptr");
	}

	workThread.reset(new thread([this]() {
	  this->id = pthread_self();
	  ThreadState::Instance().setThreadName(workThread->native_handle(), this->name);
	  this->threadInitialized = true;
	  shared_ptr<BaseException> newException;
	  try {
		  this->run();
	  }
	  catch (const shared_ptr<BaseException> baseException) {
		  newException = baseException;
	  }
	  catch (const BaseException &baseException) {
		  newException.reset(new BaseException(baseException));
		  newException->setLoseInfo(true);
	  }
	  catch (const std::exception &exception) {
		  newException = ExceptionHandleCenter::instance().transformException(exception);
	  }
	  catch (...) {
		  /**
			 *	特殊情况只知道存在异常但异常是什么不知道
			 *
			 *	TODO:处理 线程独有的打断异常,当调用pthread_yield时产生的异常,这个异常要抛出交给系统处理,属于线程的正常退出,如果截断会导致程序退出.
			 */
		  shared_ptr<BaseException> newException;
		  newException.reset(new UnkownTypeException("unkownException from thread"));
		  newException->setLoseInfo(true);
	  }
	  ThreadMonitor::Instance().pushExitedThread(this);
	}));

	while (!threadInitialized) {
		usleep(1);
	}
	ThreadState::Instance().increaseOurThreadNum();
}
void Thread::sleep() {
	ThreadState::Instance().getSignal(pthread_self())->sleep();
}
void Thread::sleepForMs(int ms) {
	ThreadState::Instance().getSignal(pthread_self())->sleep_for_us(ms * 1000);
}
void Thread::wake() {
	ThreadState::Instance().getSignal(pthread_self())->notify();
}
void Thread::processException(shared_ptr<BaseException> baseException) {
	if (this->listener) {
		this->listener->onExistSync(this, baseException);
	} else {
		ExceptionHandleCenter::instance().postException(baseException);
	}
}

void Thread::join(){
	workThread->join();
	hasJointd = true;
};

Thread::~Thread() {
	ThreadState::Instance().clearThreadInfo(id);
	ThreadState::Instance().decreaseOurThreadNum();
	if (!hasJointd){
		throwException<ThreadUnjointedException>("ThreadUnjointedException");
	}
}
const shared_ptr<BaseException> &Thread::getExitException() const {
	return exitException;
}
pthread_t Thread::getId() const {
	return id;
}
const shared_ptr<ThreadStateListener> &Thread::getListener() const {
	return listener;
}
