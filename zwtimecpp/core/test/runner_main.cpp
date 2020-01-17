//
// Created by zhaohe on 19-6-16.
//
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "zwtimecpp/core/logger/logger.hpp"
#include "zwtimecpp/core/test/test_utils/runner_manager.hpp"
#include "zwtimecpp/core/thread/thread.hpp"

#include "zwtimecpp/core/utils/argh/argh.h"
#include "zwtimecpp/core/utils/argh/argh.h"
using namespace std;
using namespace zwsd;
using namespace core;
int main(int argc, char const* argv[]) {
  logger_t s_logger = SpdLoggerFactory::Instance().createLogger("RunnerMain");
  Z_WARP_THREAD(main);

  argh::parser cmdl;
  cmdl.parse(argc, argv);
  cmdl.add_params({"help"});
  if ((cmdl["--help"] && argc == 2) || argc < 2) {
    s_logger->info("使用方法");
    s_logger->info("./runner_main module_name module_parameter......");
    s_logger->info(
        "./runner_main module_name --help //to show module helpe msg");
    s_logger->info(
        "--------------------------------------------------------------");
    s_logger->info("-module name list:");
    for (auto& var : RunnerManager::Instance().runners()) {
      s_logger->info("- {}", var->getName());
      if (!var->briefIntroduction().empty()) {
        s_logger->info("-                {}", var->briefIntroduction());
      }
    }

    exit(-1);
  }

  if (cmdl["--help"]) {
    bool hasShowHelp = false;
    for (auto& var : RunnerManager::Instance().runners()) {
      if (var->getName() == argv[1]) {
        var->introduction(nullptr);
        hasShowHelp = true;
        break;
      }

      if (!hasShowHelp) {
        s_logger->info(
            "./runner_main module_name --help //to show module helpe msg");
      }
    }
    exit(-1);
  }

  RunnerManager::Instance().run(argv[1], argc, argv);
  return 0;
}
