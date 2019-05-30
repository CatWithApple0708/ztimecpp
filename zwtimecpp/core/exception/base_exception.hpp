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
#include <zwtimecpp/core/base/interlog/simple_logger.hpp>
#include "zwtimecpp/core/base/object.hpp"

namespace zwsd {
namespace core {
using namespace std;

/**
 *	1. 保存栈信息 (ok)
 *  2. 使能和失能保存栈信息功能 ( )
 *  3. 格式化输入信息
 *  4. 集中处理所有异常
 *  5. 获得线程的相关信息
 */
  class BaseException  :public std::exception,public Object{
  protected:
	string stackInfo;
	string description;
	pthread_t pthreadId;
	bool loseInfo = false; //这个
	string stdExceptionWhat;
	string stdExceptionTypeinfo;
    protected:
	  mutable bool hasCalledToString = false;
  public://Getter
	virtual const string &getStackInfo() const {
		return stackInfo;
	}
	virtual const string &getDescription() const {
		return description;
	}
	bool isHasCalledToString() const;
	virtual pthread_t getPthreadId() const {
		return pthreadId;
	}
	virtual bool isLoseInfo() const {
		return loseInfo;
	}
	virtual void setLoseInfo(bool loseInfo) {
		BaseException::loseInfo = loseInfo;
	}
	  const char *what() const _GLIBCXX_USE_NOEXCEPT override;
    public:
	/**
  	 * 构造一个基础类型的异常,
  	 *
  	 * 特性: 构造异常之后如果异常在析构前没有被调用toString, 则会自动调用异常的toString, 但不要依赖这个特性去写代码, 因为非继承于BaseException的异常会被忽悠掉
     * @param description
     */
	BaseException(string description, string stdExceptionTypeinfo = "", string baseExceptionWhat = "");

	BaseException(string description, const std::exception &stdexcep);

	virtual ~BaseException();
	virtual string toString() const;

	/**
	 * 格式化字符串,最大字符长度1024
	 * @param fmt
	 * @param ...
	 * @return
	 */
	static string format1024(const char *fmt, ...) __attribute__ ((__format__ (__printf__, 1, 2)));

	static void setLastException(shared_ptr<BaseException> e);
	static shared_ptr<BaseException> getUnHandledException();
  private:
	void initialize(string description, string stdExceptionTypeinfo = "", string baseExceptionWhat = "");
};


}
}