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
#include <zwtimecpp/core/base/interlog/simple_logger.hpp>
#include "zwtimecpp/core/exception/base_exception.hpp"
#include "zwtimecpp/core/exception/system_or_third_lib_exception.hpp"
#include "zwtimecpp/core/exception/unkown_type_exception.hpp"
#include "zwtimecpp/core/exception/null_expection.hpp"
#include "zwtimecpp/core/base/object.hpp"

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
                                     function<void(const exception &)> onException,
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
	catch (const std::exception &exception) {
		onException(exception);
	}
	catch (...) {
		/**
		   *	特殊情况只知道存在异常但异常是什么不知道
		   *
		   *	TODO:处理 线程独有的打断异常,当调用pthread_yield时产生的异常,这个异常要抛出交给系统处理,属于线程的正常退出,如果截断会导致程序退出.
		   */
		UnkownTypeException unkownTypeException("unkownException from thread");
		onException(unkownTypeException);
	}

	if (final) {
		final();
	}
}
}
}


