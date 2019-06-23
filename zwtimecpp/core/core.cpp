//
// Created by zhaohe on 19-6-20.
//
#include "core.hpp"
#include "zwtimecpp/core/utils/backward/backward.hpp"

using namespace std;
using namespace zwsd;
using namespace core;
backward::SignalHandling sh;

#define CASE(value, explain) \
  case value:                \
    return fmt::format("{}:{}", #value, explain);

std::string signalToStr(int value) {
  switch (value) {
    CASE(SIGABRT, "Abort signal from abort(3)")
    CASE(SIGBUS, " Bus error (bad memory access)")
    CASE(SIGFPE, " Floating point exception")
    CASE(SIGILL, " Illegal Instruction")
    // CASE(SIGIOT, " IOT trap. A synonym for SIGABRT")
    CASE(SIGQUIT, "Quit from keyboard")
    CASE(SIGSEGV, "Invalid memory reference")
    CASE(SIGSYS, " Bad argument to routine (SVr4)")
    CASE(SIGTRAP, "Trace/breakpoint trap")
    CASE(SIGXCPU, "CPU time limit exceeded (4.2BSD)")
    CASE(SIGXFSZ, "File size limit exceeded (4.2BSD)")
    default:
      return fmt::format("unkownSignal{}", value);
      break;
  }
}

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
    Core::instance()->logger->error("{} stackInfo:\n{}",
                                    signalToStr(info->si_signo), backtrackMsg);
    spdlog::drop_all();
  });
}