#include "gtest/gtest.h"
#include <functional>

#include "project_mock.hpp"
#include "zwtimecpp/core/utils/zmath.hpp"

using namespace std;
using namespace zwsd;
using namespace core;

using namespace testing;

class GtestZmath : public testing::Test {
 public:
  void SetUp() override {}
};

TEST_F(GtestZmath, testlimitPi1) {
  {
    float direction = 1.5 * M_PI;
    float v = limitPi1(direction);
    EXPECT_NEAR(-0.5 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.8 * M_PI;
    float v = limitPi1(direction);
    EXPECT_NEAR(-0.2 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.1 * M_PI;
    float v = limitPi1(direction);
    EXPECT_NEAR(-0.9 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.5 * M_PI + M_PI * 10;
    float v = limitPi1(direction);
    EXPECT_NEAR(-0.5 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.8 * M_PI + M_PI * 10;
    ;
    float v = limitPi1(direction);
    EXPECT_NEAR(-0.2 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.1 * M_PI + M_PI * 10;
    ;
    float v = limitPi1(direction);
    EXPECT_NEAR(-0.9 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.5 * M_PI - M_PI * 10;
    float v = limitPi1(direction);
    EXPECT_NEAR(-0.5 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.8 * M_PI - M_PI * 10;
    ;
    float v = limitPi1(direction);
    EXPECT_NEAR(-0.2 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.1 * M_PI - M_PI * 10;
    ;
    float v = limitPi1(direction);
    EXPECT_NEAR(-0.9 * M_PI, v, 0.00001);
  }
}

TEST_F(GtestZmath, testlimitPiRecursion) {
  {
    float direction = 1.5 * M_PI;
    float v = limitPiRecursion(direction);
    EXPECT_NEAR(-0.5 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.8 * M_PI;
    float v = limitPiRecursion(direction);
    EXPECT_NEAR(-0.2 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.1 * M_PI;
    float v = limitPiRecursion(direction);
    EXPECT_NEAR(-0.9 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.5 * M_PI + M_PI * 10;
    float v = limitPiRecursion(direction);
    EXPECT_NEAR(-0.5 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.8 * M_PI + M_PI * 10;
    ;
    float v = limitPiRecursion(direction);
    EXPECT_NEAR(-0.2 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.1 * M_PI + M_PI * 10;
    ;
    float v = limitPiRecursion(direction);
    EXPECT_NEAR(-0.9 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.5 * M_PI - M_PI * 10;
    float v = limitPiRecursion(direction);
    EXPECT_NEAR(-0.5 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.8 * M_PI - M_PI * 10;
    ;
    float v = limitPiRecursion(direction);
    EXPECT_NEAR(-0.2 * M_PI, v, 0.00001);
  }

  {
    float direction = 1.1 * M_PI - M_PI * 10;
    ;
    float v = limitPiRecursion(direction);
    EXPECT_NEAR(-0.9 * M_PI, v, 0.00001);
  }
}