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
#include "zwtimecpp/core/base/object.hpp"
#include "zwtimecpp/core/exception/base_exception.hpp"
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
 public:
  typedef function<void(const std::exception &expec)> exceptionHandler_t;

 private:
  function<void()> run;
  unique_ptr<thread> workThread;
  shared_ptr<BaseException> exitException;
  bool hasJointd = false;
  string name;
  pthread_t id = 0;
  bool threadInitialized = false;
  bool threadExitFlag = false;
  Thread(std::function<void()> run);

 public:
  Thread(string name, function<void()> run);

  static void sleep();
  static void sleepForMs(int ms);
  static void wake(pthread_t threadid);

  void wake();
  bool getExitFlag();

  void join();
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
}  // namespace core
}  // namespace zwsd
