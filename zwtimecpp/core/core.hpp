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
#include "zwtimecpp/core/exception/null_expection.hpp"
#include "zwtimecpp/core/exception/base_exception.hpp"
#include "zwtimecpp/core/event_bus.hpp"
#include "zwtimecpp/core/exception_handle_center.hpp"
#include "zwtimecpp/core/base/system_state.hpp"

namespace zwsd {
namespace core {
using namespace std;

class Core : public Object {
  private:
	Core() {
		SimpleLogger::trace("Core");
	}
  public:
	virtual ~Core() {
		SimpleLogger::trace("~Core");
	}
  private:
	static shared_ptr<Core> &instance() {
		static shared_ptr<Core> value;
		return value;
	}

  public:
	static shared_ptr<Core> Instance() {
		if (instance() == nullptr) {
			throw NullException("Core instance hasn't been initialized ZigbeeGatewayService::instance == nullptr");
		}
		return instance();
	}
	static void initialize() {
		if (instance() != nullptr) {
			throw BaseException("Core has been initialized");
		}
		instance().reset(new Core());
		EventBus::initialize();
	}

	shared_ptr<EventBus> getEventBus() { return EventBus::Instance(); }

	ExceptionHandleCenter &getExceptionHandleCenter() { return ExceptionHandleCenter::instance(); }

	const SystemState &getThreadState() { return SystemState::Instance(); }

	const void closeMain() { std::abort(); }
};
}
}


