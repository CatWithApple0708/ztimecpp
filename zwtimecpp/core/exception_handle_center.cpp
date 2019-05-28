//
// Created by zhaohe on 19-5-23.
//

#include "exception_handle_center.hpp"
#include "zwtimecpp/core/base/interlog/simple_logger.hpp"
#include <zwtimecpp/core/exception/system_or_third_lib_exception.hpp>
using namespace std;
using namespace zwsd;
using namespace core;



void ExceptionHandleCenter::regExceptionHandler(shared_ptr<ExceptionHandler> handler) {
	if (exceptionHandler != nullptr) {
		SimpleLogger::fatal("exceptionHandler has been reg");
		return;
	}

	if (handler == nullptr) {
		SimpleLogger::fatal("regExceptionHandler handler is null");
	} else {
		exceptionHandler = handler;
	}
	return;
}

void ExceptionHandleCenter::postException(const exception &expec) {
	if (exceptionHandler) {
		exceptionHandler->onExceptionSync(expec);
	} else {
		SimpleLogger::fatal("Catch One exception but no exceptionHandler %s",expec.what());
	}
}
void ExceptionHandleCenter::clearExceptionHandler() {
	exceptionHandler = nullptr;
}
