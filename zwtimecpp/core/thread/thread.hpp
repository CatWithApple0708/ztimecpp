//
// Created by zhaohe on 19-5-21.
//

#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>

#include "zwtimecpp/core/base/object.hpp"
#include "zwtimecpp/core/exception/base_exception.hpp"
#include "zwtimecpp/core/logger/logger.hpp"
#include "zwtimecpp/core/system_state.hpp"
namespace zwsd {
namespace core {
using namespace std;
/**
 * 静态方法:
 * 通过线程id知道线程是否阻塞
 * 通过线程id唤醒线程
 * 默认睡眠
 *
 * 通过线程对象获得:
 * 获得线程创建的位置
 * 抛出所有未处理的异常到异常处理中心
 * 给线程给予名字
 */
class Thread;
//
// class ThreadStateListener :public Object{
//  public:
//	/**
//	 *
//@这个回调的位置线程还没有退出,不能在这里进行线程的回收需要另启一个线程进行这线程的回收.
//	 * @param baseException
//	 */
//	virtual void onCatchException(Thread *thread, const std::exception
//&baseException) = 0;
//	/**
//	 *
//线程即将退出的时候进行回调,注意这个回调中不能调用thread->join,因为这个函数的运行环境是线程本身
//	 * @param thread
//	 */
//	virtual void onExistSync(Thread *thread) = 0;;
//	virtual ~ThreadStateListener(){};
//};

class Thread : public Object {
  ENABLE_LOGGER(Thread);

 public:
  typedef function<void(const std::exception &expec)> exceptionHandler_t;
  std::mutex lock_;

 private:
  function<void()> run;
  unique_ptr<thread> workThread;
  shared_ptr<BaseException> exitException;
  atomic_bool hasJointd = {false};
  string name;
  pthread_t id = 0;
  bool threadInitialized = false;
  bool waitingForJoin = false;/*当前线程是否运行退出等待回收*/
  Thread(std::function<void()> run);

 public:
  Thread(string name, function<void()> run);

  //下面的static方法都是针对于当前线程,与具体的线程对象无关
  // static void sleep();
  // static void sleepForMs(int ms);
  //这个方法 Thread::getExitFlag(pthread_self());,调用join的时候会自动设置为true
  // TODO:修改这个api，很容易勿用,不要使用这个api,使用getCurrentThreadExitFlag
  // static bool getExitFlag();

  static void wake(pthread_t threadid);
  void wake();
  void join(function<void()>wakeFunc = nullptr);
  bool isWaitingForJoin() { return waitingForJoin; }
  pthread_t getId() const;
  ~Thread();

  /**
   * 设置默认的异常处理回调方法,返回上一个异常处理方法.这里需要注意,exceptionHandler,在Thread中是使用weak_ptr保存的
   *
   * error_code
   * {
   *		Thread::setDefaultExceptionHandler(make_shared<ExceptionHandlerImpl>());//ExceptionHandlerImpl会被析构掉
   * }
   * right_code
   * {
   * 		static shared_ptr<ExceptionHandler> handler =
   *make_shared<ExceptionHandlerImpl>(); //保证handler不会析构
   *		Thread::setDefaultExceptionHandler(handler);
   * }
   * @param exceptionHandler
   * @return
   */
 private:
  const shared_ptr<BaseException> &getExitException() const;
  void callDefaultExceptionHandler(const std::exception &exception);
};
class ThisThread {
  shared_ptr<ThreadInfo> threadInfo;

 public:
  ThisThread();
  bool getExitFlag();
  void sleep();
  void sleepForMs(int ms);
};

}  // namespace core
}  // namespace zwsd
