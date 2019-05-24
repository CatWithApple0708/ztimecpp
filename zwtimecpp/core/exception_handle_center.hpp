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
#include "zwtimecpp/core/exception/base_exception.hpp"

namespace zwsd{
namespace core{

class ExceptionHandler {
  public:
	virtual void onExceptionSync(std::shared_ptr<zwsd::core::BaseException> expec) = 0;
	~ExceptionHandler() {};
};

using namespace std;
class ExceptionHandleCenter {
  private:

	shared_ptr<ExceptionHandler> exceptionHandler;
	list<shared_ptr<BaseException>> baseExceptions;
	function<shared_ptr<BaseException>(const std::exception&)> transformer;

	ExceptionHandleCenter(){};
  public:
	static ExceptionHandleCenter &instance()
	{
		static ExceptionHandleCenter value;
		return value;
	}
	/**
	 * OnlyCanRegOne;
	 * @param handler
	 */
	void regExceptionHandler(shared_ptr<ExceptionHandler> handler);
	/**
	 * 登记异常转换器,用来转换普通异常到BaseException
	 * @param transformer
	 */
	void regExceptionTransformer(function<shared_ptr<BaseException>(const std::exception&)> transformer);
	/**
	 * 清除异常监听者
	 */
	void clearExceptionHandler();
	/**
	 * 将希望统一处理的异常邮寄到异常处理中心
	 * @param expec
	 */
	void postException(shared_ptr<BaseException> expec);

	shared_ptr<BaseException> transformException(const std::exception& exception1);

  public:

};
}
}


