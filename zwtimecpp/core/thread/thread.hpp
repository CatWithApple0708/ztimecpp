//
// Created by zhaohe on 19-5-21.
//

#pragma once
#include <memory>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <thread>
#include "zwtimecpp/core/exception/base_exception.hpp"
#include "zwtimecpp/core/base/object.hpp"
#include "zwtimecpp/core/base/system_state.hpp"

namespace zwsd {
namespace core{
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

class ThreadStateListener :public Object{
  public:
	/**
	 * @这个回调的位置线程还没有退出,不能在这里进行线程的回收需要另启一个线程进行这线程的回收.
	 * @param baseException
	 */
	virtual void onCatchException(Thread *thread, const std::exception &baseException) = 0;
	/**
	 * 线程即将退出的时候进行回调,注意这个回调中不能调用thread->join,因为这个函数的运行环境是线程本身
	 * @param thread
	 */
	virtual void onExistSync(Thread *thread) = 0;;
	virtual ~ThreadStateListener(){};
};

class Thread :public Object{
  private:
	function<void()> run;
	unique_ptr<thread> workThread;
	weak_ptr<ThreadStateListener> listener;
	shared_ptr<BaseException> exitException;
	bool hasJointd = false;
	string name;
	pthread_t id =0;
	bool  threadInitialized = false;
	Thread(std::function<void()> run);
  public:
	Thread(string name,function<void()> run,shared_ptr<ThreadStateListener> listener);

	static void sleep();
	static void sleepForMs(int ms);
	static void wake();

	void join();
	pthread_t getId() const;
	~Thread();
  private:
	const weak_ptr<ThreadStateListener> &getListener() const;
	const shared_ptr<BaseException> &getExitException() const;
	void callDefaultExceptionHandler(const std::exception& exception);

};
}
}


