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
class BaseException {
	string stackInfo;
	string description;
	pthread_t pthreadId;
  public://Getter
	const string &getStackInfo() const {
		return stackInfo;
	}
	const string &getDescription() const {
		return description;
	}
	pthread_t getPthreadId() const {
		return pthreadId;
	}

  public:
	/**
	 * 构造一个基础类型的异常
	 * @param description
	 */
	BaseException(string description);
	/**
	 * 格式化字符串,最大字符长度1024
	 * @param fmt
	 * @param ...
	 * @return
	 */
	static string format1024(const char *fmt, ...) __attribute__ ((__format__ (__printf__, 1, 2)));
  private:
};

template<class T>
static void throwException(const string &msg) {
	shared_ptr<T> exception;
	exception.reset(new T(msg));
	throw exception;
};



}
}