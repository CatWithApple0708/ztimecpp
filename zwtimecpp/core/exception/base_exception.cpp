//
// Created by zhaohe on 19-5-21.
//

#include "base_exception.hpp"
#include "../utils/backward/backward.hpp"
#include <stdarg.h>
#include <thread>

using namespace std;
using namespace zwsd;
using namespace core;
using namespace backward;

BaseException::BaseException(string description) {
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
}

string BaseException::format1024(const char *fmt, ...) {
	char buf[1024] = {0};
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, 1024, fmt, args);
	va_end(args);

	return string(buf);
}

