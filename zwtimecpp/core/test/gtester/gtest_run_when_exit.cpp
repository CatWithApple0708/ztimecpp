#include "gtest/gtest.h"
extern "C" {
#include "zwtimecpp/core/utils/cutils/net.h"
}
#include <vector>
#include "project_mock.hpp"
#include "zwtimecpp/core/utils/run_when_exit.hpp"

using namespace std;
using namespace zwsd;
using namespace core;

using namespace testing;

class TestRunWhenExit : public testing::Test {
 public:
  ENABLE_LOGGER(GTestNet);

 public:
  void SetUp() override {}
};

#ifndef ARRARY_SIZE
#define ARRARY_SIZE(arrary) sizeof(arrary) / sizeof(arrary[0])
#endif

TEST_F(TestRunWhenExit, testNet) {
  logger->set_level(level::debug);
  bool testFlag = false;
  { RUN_WHEN_EXIT(testFlag = true); }
  EXPECT_EQ(testFlag, true);
}
