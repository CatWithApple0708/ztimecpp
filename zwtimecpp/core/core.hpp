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
#include "system_state.hpp"
#include "zwtimecpp/core/logger/logger.hpp"

namespace zwsd {
namespace core {
using namespace std;

class Core : public Object {
  private:
	Core() {
	}
  public:
	virtual ~Core() {
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
		//基础数据结构初始化
		CoreSystemState::Instance();
		EventBus::initialize();
		ExceptionHandleCenter::instance();
	}

	shared_ptr<EventBus> getEventBus() { return EventBus::Instance(); }

	ExceptionHandleCenter &getExceptionHandleCenter() { return ExceptionHandleCenter::instance(); }

	CoreSystemState &getSystemState() { return CoreSystemState::Instance(); }

	const void closeMain() { std::abort(); }
};
}
}


