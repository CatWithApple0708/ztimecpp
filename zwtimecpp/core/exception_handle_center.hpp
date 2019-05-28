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
		SimpleLogger::trace("ExceptionHandleCenter");
	};
  public:
	virtual ~ExceptionHandleCenter() {
		SimpleLogger::trace("~ExceptionHandleCenter");
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
}
}


