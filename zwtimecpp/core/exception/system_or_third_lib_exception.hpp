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
#include "zwtimecpp/core/thread_state.hpp"

namespace zwsd {
using namespace std;
using namespace core;
/**
 *
 * 系统或者第三方库函抛出的继承于std::exception的异常,特点是在一些情况下没办法获得准确的栈回溯信息
 * 例如:
 * func(){
 *	//这里是最佳的进行栈回溯的地方,但由于异常抛出的并非我们定义的BaseException,无法获得准确的栈信息.
 * 	throw std::exception();
 * }
 *
 * call(){
 * 		try(){
 * 			func();
 * 		}
 * 		catch(){
 *			//这里进行栈回溯可能会丢失部分栈信息
 * 		}
 * }
 */
class SystemOrThirdLibException :public BaseException{
  public:
	SystemOrThirdLibException(const string &description, const exception &sysException)
		: BaseException(description,sysException){
	}

};
}


