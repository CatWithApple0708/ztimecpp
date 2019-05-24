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
#include "base_exception.hpp"
namespace zwsd {
namespace core{
using namespace std;
using namespace core;
/**
 * 不知道是什么类型的exception, 异常没有继承 std::exception
 *
 * 例如:
 * 	throw 1
 * 	throw "Hello"
 */
class UnkownTypeException : public BaseException{

  public:
	UnkownTypeException(const string &description) : BaseException(description) {}
};
}
}


