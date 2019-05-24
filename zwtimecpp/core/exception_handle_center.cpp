//
// Created by zhaohe on 19-5-23.
//

#include "exception_handle_center.hpp"
#include "zwtimecpp/core/interlog/simple_logger.hpp"
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

void ExceptionHandleCenter::postException(shared_ptr<BaseException> expec) {
	if (expec == nullptr) {
		SimpleLogger::fatal("postException exception is null");
	}
	if (exceptionHandler) {
		exceptionHandler->onExceptionSync(expec);
	} else {
		SimpleLogger::fatal("Catch One exception but no exceptionHandler");
	}
}
void ExceptionHandleCenter::clearExceptionHandler() {
	exceptionHandler = nullptr;
}
void ExceptionHandleCenter::regExceptionTransformer(function<shared_ptr<BaseException>(const std::exception &)> transformer) {
	this->transformer = transformer;
}
shared_ptr<BaseException> ExceptionHandleCenter::transformException(const std::exception &exception1) {
	shared_ptr<BaseException> newException;

	if (this->transformer == nullptr) {
		newException.reset(new BaseException("unkown exception type, because regExceptionTransformer hasn't been called",
		                                     exception1));
		newException->setLoseInfo(true);
	} else {
		newException = transformer(exception1);
		if (newException == nullptr) {
			newException.reset(new BaseException("unkown exception type, because ", exception1));
			newException->setLoseInfo(true);
		}
	}
	return newException;
}
