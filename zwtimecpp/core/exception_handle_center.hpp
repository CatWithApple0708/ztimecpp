//
// Created by zhaohe on 19-5-23.
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
#include <zwtimecpp/core/base/exception_handler.hpp>
#include <zwtimecpp/core/exception/unkown_type_exception.hpp>
#include "zwtimecpp/core/exception/base_exception.hpp"
#include "zwtimecpp/core/base/object.hpp"
#include "zwtimecpp/core/base/interlog/simple_logger.hpp"


namespace zwsd {
namespace core {


using namespace std;

class ExceptionHandleCenter : public Object {
  private:

	shared_ptr<ExceptionHandler> exceptionHandler;
	list<shared_ptr<BaseException>> baseExceptions;
	function<shared_ptr<BaseException>(const std::exception &)> transformer;

	ExceptionHandleCenter() {
	};
  public:
	virtual ~ExceptionHandleCenter() {
	}

	static ExceptionHandleCenter &instance() {
		static ExceptionHandleCenter value;
		return value;
	}
	/**
	 * OnlyCanRegOne;
	 * @param handler
	 */
	void regExceptionHandler(shared_ptr<ExceptionHandler> handler);
	/**
	 * 清除异常监听者
	 */
	void clearExceptionHandler();
	/**
	 * 将希望统一处理的异常邮寄到异常处理中心
	 * @param expec
	 */
	void postException(const exception &expec);

};

/**
 * 不处理任何异常,直接将所有异常抛给异常处理中心
 * @param work
 */
static inline void throwAllExceptionToExceptionCenter(function<void()> work){
	if (work == nullptr) {
		SimpleLogger::fatal("core::catchExceptionSimple work == nullptr");
	}
	try {
		work();
	}

	catch (const std::exception & exception_value) {
		ExceptionHandleCenter::instance().postException(exception_value);
	}
	catch (...) {
		/**
		   *	特殊情况只知道存在异常但异常是什么不知道
		   *
		   *	TODO:处理 线程独有的打断异常,当调用pthread_yield时产生的异常,这个异常要抛出交给系统处理,属于线程的正常退出,如果截断会导致程序退出.
		   */
		UnkownTypeException unkownTypeException("unkownException from thread");
		ExceptionHandleCenter::instance().postException(unkownTypeException);
	}
}
}
}




