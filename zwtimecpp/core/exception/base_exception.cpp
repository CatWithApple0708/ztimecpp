//
// Created by zhaohe on 19-5-21.
//

#include "base_exception.hpp"
#include "../utils/backward/backward.hpp"
#include <stdarg.h>
#include <thread>
#include <iostream>
#include "zwtimecpp/core/thread_state.hpp"
#include "zwtimecpp/core/exception_handle_center.hpp"
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
string BaseException::toString() {
	string ret;
	ret += "\n|-----------------------exceptionInfo-----------------------------\n";
	ret += "|exception type:  " + string(typeid(*this).name()) + "\n";
	ret += "|description: " + this->description + "\n";

	if (!this->stdExceptionTypeinfo.empty())
		ret += "|stdExceptionTypeinfo: " + this->stdExceptionTypeinfo + "\n";
	if (!this->stdExceptionWhat.empty())
		ret += "|stdExceptionWhat: " + this->stdExceptionWhat + "\n";

	ret += "|pthreadId: " + ThreadState::Instance().getThreadName(this->pthreadId) + "\n";
	ret += "|loseInfo: " + to_string(this->loseInfo) + "\n";
	ret += "|stackTrace: \n" + this->stackInfo;

	hasCalledToString = true;
	return ret;
}
BaseException::~BaseException() {
	if (!hasCalledToString)
		std::cerr << toString();
}
bool BaseException::isHasCalledToString() const {
	return hasCalledToString;
}
