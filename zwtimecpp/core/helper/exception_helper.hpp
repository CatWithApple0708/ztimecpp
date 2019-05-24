//
// Created by zhaohe on 19-5-24.
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
#include <zwtimecpp/core/interlog/simple_logger.hpp>
#include "zwtimecpp/core/exception/base_exception.hpp"
#include "zwtimecpp/core/exception_handle_center.hpp"
#include "zwtimecpp/core/exception/system_or_third_lib_exception.hpp"
#include "zwtimecpp/core/exception/unkown_type_exception.hpp"
#include "zwtimecpp/core/exception/null_expection.hpp"

namespace zwsd {
namespace core {
using namespace std;

/**
 * 只捕获继承于baseException的异常,其他异常直接强转成baseException(会丢失部分信息)
 * @param work 要做的事
 * @param onException 当收到异常
 * @param final 异常回收工作
 */
static inline void tryCatchException(function<void()> work,
                                        function<void(shared_ptr<BaseException> baseException)> onException,
                                        function<void()> final = nullptr) {
	if (work == nullptr) {
		SimpleLogger::fatal("core::catchExceptionSimple work == nullptr");
	}

	if (onException == nullptr) {
		SimpleLogger::fatal("core::catchExceptionSimple onException == nullptr");
	}

	try {
		work();
	}
	catch (const shared_ptr<BaseException> baseException) {
		onException(baseException);
	}
	catch (const BaseException &baseException) {
		shared_ptr<BaseException> newException;
		newException.reset(new BaseException(baseException));
		newException->setLoseInfo(true);
		onException(newException);
	}
	catch (const std::exception &exception) {
		shared_ptr<BaseException> newException = ExceptionHandleCenter::instance().transformException(exception);
		onException(newException);
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
		onException(newException);
	}

	if (final) {
		final();
	}
}

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
	catch (const shared_ptr<BaseException> baseException) {
		ExceptionHandleCenter::instance().postException(baseException);
	}
	catch (const BaseException &baseException) {
		shared_ptr<BaseException> newException;
		newException.reset(new BaseException(baseException));
		newException->setLoseInfo(true);
		ExceptionHandleCenter::instance().postException(newException);
	}
	catch (const std::exception & exception_value) {
		shared_ptr<BaseException> newException = ExceptionHandleCenter::instance().transformException(exception_value);
		ExceptionHandleCenter::instance().postException(newException);
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
		ExceptionHandleCenter::instance().postException(newException);
	}
}
}
}


