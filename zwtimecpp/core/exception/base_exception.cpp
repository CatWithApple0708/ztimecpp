//
// Created by zhaohe on 19-5-21.
//

#include "base_exception.hpp"
#include "../utils/backward/backward.hpp"
#include <stdarg.h>
#include <thread>
#include <iostream>
#include "zwtimecpp/core/system_state.hpp"
#include "zwtimecpp/core/exception_handle_center.hpp"
#include "zwtimecpp/core/base/interlog/simple_logger.hpp"
#include "zwtimecpp/core/logger/logger.hpp"
using namespace std;
using namespace zwsd;
using namespace core;
using namespace backward;
static shared_ptr<BaseException> s_theLastedBaseException;
void BaseException::setLastException(shared_ptr<BaseException> e) {
	s_theLastedBaseException = e;
}
shared_ptr<BaseException> BaseException::getUnHandledException() {
	if (s_theLastedBaseException && !s_theLastedBaseException->isHasCalledToString()) {
		return s_theLastedBaseException;
	}
	if (s_theLastedBaseException){
		return s_theLastedBaseException;
	}
	return nullptr;
}
BaseException::BaseException(string description, string stdExceptionTypeinfo, string baseExceptionWhat) {
	initialize(description, stdExceptionTypeinfo, baseExceptionWhat);
};

void BaseException::initialize(string description, string stdExceptionTypeinfo, string baseExceptionWhat) {
	StackTrace st;
	st.load_here(32);
	Printer p;
	p.object = true;
	p.snippet = true;
	p.color_mode = ColorMode::always;
	p.address = true;
	ostringstream out;
	p.print(st, out);

	this->description = description;
	this->stackInfo = out.str();
	this->pthreadId = pthread_self();
	this->stdExceptionWhat = baseExceptionWhat;
	this->stdExceptionTypeinfo = stdExceptionTypeinfo;
//	setLastException(shared_from_this());
}

BaseException::BaseException(string description, const std::exception &stdexcep) {
	initialize(description, typeid(stdexcep).name(), stdexcep.what());
	//这里不能写成
	//BaseException(description,typeid(stdexcep).name(),stdexcep.what()); 不知道为什么对象的成员变量会被清空
}
string BaseException::format1024(const char *fmt, ...) {
	char buf[1024] = {0};
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, 1024, fmt, args);
	va_end(args);

	return string(buf);
}
string BaseException::toString() const{
	string ret;
	ret += "\n#-----------------------exceptionInfo-----------------------------\n";
	ret += "#exception type:  " + string(typeid(*this).name()) + "\n";
	ret += "#description: " + this->description + "\n";

	if (!this->stdExceptionTypeinfo.empty())
		ret += "#stdExceptionTypeinfo: " + this->stdExceptionTypeinfo + "\n";
	if (!this->stdExceptionWhat.empty())
		ret += "#stdExceptionWhat: " + this->stdExceptionWhat + "\n";

	string threadInfo;

//	ret += "#pthreadId: " + CoreSystemState::Instance().get (this->pthreadId) + "\n";
	ret += "#loseInfo: " + to_string(this->loseInfo) + "\n";
	ret += "#stackTrace: \n" + this->stackInfo;
	hasCalledToString  = true;
	return ret;
}
BaseException::~BaseException() {
	if (!hasCalledToString){
		std::cerr << "#Show exception message, because not call exception->toString before it destroy";
		std::cerr << toString();
	}

}
bool BaseException::isHasCalledToString() const {
	return hasCalledToString;
}
const char *BaseException::what() const _GLIBCXX_USE_NOEXCEPT {
  // return toString().c_str();
  //之所以在这里打印log，因为在arm上由系统自动打印的，what()可能会出现乱码.
  spdlog::critical("Catch exception \n{}", toString());
  spdlog::default_logger()->flush();
  return "end";
}
