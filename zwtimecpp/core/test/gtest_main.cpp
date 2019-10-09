
#include <stdio.h>

#include "gtest/gtest.h"
#include "zwtimecpp/core/core.hpp"
#include "zwtimecpp/core/logger/default_logger_config.hpp"

SET_DEFAULT_SPD_LOG_CONFIG_FILE(gtest_spdlog.json)
using namespace zwsd::core;
int main(int argc, char **argv) {

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}