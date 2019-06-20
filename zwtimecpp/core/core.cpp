//
// Created by zhaohe on 19-6-20.
//
#include "core.hpp"
#include "zwtimecpp/core/utils/backward/backward.hpp"

using namespace std;
using namespace zwsd;
using namespace core;
backward::SignalHandling sh;

void Core::initialize() {
  if (Core::instance() != nullptr) {
    throw BaseException("Core has been initialized");
  }
  Core::instance().reset(new Core());
  //基础数据结构初始化
  CoreSystemState::Instance();
  EventBus::initialize();
  ExceptionHandleCenter::instance();
  if (sh.loaded()) {
    Core::instance()->logger->info("backward::SignalHandling success");
  }
  sh.regSignalHandeler([](siginfo_t* info, std::string backtrackMsg) {
    Core::instance()->logger->error("stackInfo:\n{}", backtrackMsg);
    spdlog::drop_all();
  });
}