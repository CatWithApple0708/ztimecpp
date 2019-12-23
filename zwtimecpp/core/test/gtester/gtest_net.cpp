#include "gtest/gtest.h"
extern "C" {
#include "zwtimecpp/core/utils/cutils/net.h"
}
#include "project_mock.hpp"
#include <vector>

using namespace std;
using namespace zwsd;
using namespace core;

using namespace testing;

class TestNet : public testing::Test {
 public:
  ENABLE_LOGGER(GTestNet);
 public:
  void SetUp() override {}
};

#ifndef ARRARY_SIZE
#define ARRARY_SIZE(arrary) sizeof(arrary) / sizeof(arrary[0])
#endif

TEST_F(TestNet, testNet) {
    logger->set_level(level::debug);
    // logger->info("say hello");

    vector<uint8_t> arrary = {1, 2, 3, 4, 5, 6, 7, 8};
    vector<uint8_t> arraryOrigion = arrary;
    transNet(arrary.data(), arrary.size());
    // logger->info("{} {}", arrary, checkCPUEndian());
    transFromNet(arrary.data(), arrary.size());
    ASSERT_TRUE(
        memcmp(arrary.data(), arraryOrigion.data(), arraryOrigion.size()) == 0);

    // logger->info("{} {}", arrary, checkCPUEndian());

    float value = 123456.123456;
    float valueOrigion = value;
    // logger->info("{} {}", value, checkCPUEndian());
    // printf("%f\n", value);
    transNet((uint8_t*)&value, sizeof(value));
    transFromNet((uint8_t*)&value, sizeof(value));
    EXPECT_FLOAT_EQ(value, valueOrigion);
    // logger->info("{} {}", value, checkCPUEndian());
}
