#include "gtest/gtest.h"
#include <functional>

#include "project_mock.hpp"

using namespace std;
using namespace zwsd;
using namespace core;

using namespace testing;

class GtestStringUnpacker : public testing::Test {
  ENABLE_LOGGER(GtestStringUnpacker);

 public:
  int num = 0;
  shared_ptr<StringUnpacker> nullUnpacker;
  shared_ptr<StringUnpacker> crLfUnpacker;

 public:
  shared_ptr<MockSignalListener> signalListener;
  void SetUp() override {
    signalListener.reset(new NiceMock<MockSignalListener>());
    logger->set_level(level::debug);
    nullUnpacker =
        StringUnpacker::createNullUnpacker("GtestStringUnpacker-nullUnpacker");
    crLfUnpacker =
        StringUnpacker::createCrLfUnpacker("GtestStringUnpacker-crlfUnpacker");
    nullUnpacker->logger->set_level(level::debug);
  }
};

TEST_F(GtestStringUnpacker, testNull1) {
  char buf1[] = {'1', '2', '3', '4', '\0', '5', '6', '7', '8', '\0'};
  char buf2[] = {};
  {
    InSequence dummy;
    EXPECT_CALL(*signalListener, onValue(Eq("1234"))).Times(1);
    EXPECT_CALL(*signalListener, onValue(Eq("5678"))).Times(1);
    nullUnpacker->feddata(buf1, ARRARY_SIZE(buf1),
                          [this](string var) {  //
                            signalListener->onValue(var);
                            num++;
                          });
    EXPECT_EQ(num, 2);
  }

  {
    EXPECT_CALL(*signalListener, onValue(_)).Times(0);
    nullUnpacker->feddata(buf2, ARRARY_SIZE(buf2),
                          [this](string var) {  //
                            signalListener->onValue(var);
                          });
  }
}

TEST_F(GtestStringUnpacker, testNull2) {
  char buf1[] = {'1', '2', '3', '4', '\0', '5', '6'};
  char buf2[] = {'7', '8', '\0'};
  InSequence dummy;
  EXPECT_CALL(*signalListener, onValue(Eq("1234"))).Times(1);
  EXPECT_CALL(*signalListener, onValue(Eq("5678"))).Times(1);
  nullUnpacker->feddata(buf1, ARRARY_SIZE(buf1),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 1);

  nullUnpacker->feddata(buf2, ARRARY_SIZE(buf2),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 2);
}

TEST_F(GtestStringUnpacker, testNull3) {
  char buf1[] = {'1', '2'};
  char buf2[] = {'3', '4', '\0', '5', '6', '7', '8', '\0'};
  InSequence dummy;
  EXPECT_CALL(*signalListener, onValue(Eq("1234"))).Times(1);
  EXPECT_CALL(*signalListener, onValue(Eq("5678"))).Times(1);
  nullUnpacker->feddata(buf1, ARRARY_SIZE(buf1),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 0);

  nullUnpacker->feddata(buf2, ARRARY_SIZE(buf2),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 2);
}

TEST_F(GtestStringUnpacker, testNull4) {
  char buf1[] = {
      '1', '2', '3', '4', '\0', '5', '6', '7', '8',
  };
  char buf2[] = {'\0'};
  InSequence dummy;
  EXPECT_CALL(*signalListener, onValue(Eq("1234"))).Times(1);
  EXPECT_CALL(*signalListener, onValue(Eq("5678"))).Times(1);
  nullUnpacker->feddata(buf1, ARRARY_SIZE(buf1),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 1);

  nullUnpacker->feddata(buf2, ARRARY_SIZE(buf2),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 2);
}
TEST_F(GtestStringUnpacker, testNull5) {
  char buf1[] = {'1', '2', '3', '4', '\0'};
  char buf2[] = {'5', '6', '7', '8', '\0'};
  InSequence dummy;
  EXPECT_CALL(*signalListener, onValue(Eq("1234"))).Times(1);
  EXPECT_CALL(*signalListener, onValue(Eq("5678"))).Times(1);
  nullUnpacker->feddata(buf1, ARRARY_SIZE(buf1),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 1);

  nullUnpacker->feddata(buf2, ARRARY_SIZE(buf2),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 2);
}

TEST_F(GtestStringUnpacker, testCrLfUnpacker1) {
  char buf1[] = {'1', '2', '3', '4', '\r', '\n'};
  char buf2[] = {'5', '6', '7', '8', '\r', '\n'};
  InSequence dummy;
  EXPECT_CALL(*signalListener, onValue(Eq("1234"))).Times(1);
  EXPECT_CALL(*signalListener, onValue(Eq("5678"))).Times(1);
  crLfUnpacker->feddata(buf1, ARRARY_SIZE(buf1),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 1);
  crLfUnpacker->feddata(buf2, ARRARY_SIZE(buf2),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 2);
}

TEST_F(GtestStringUnpacker, testCrLfUnpacker2) {
  char buf1[] = {'1', '2', '3', '4', '\r'};
  char buf2[] = {'\n', '5', '6', '7', '8', '\r', '\n'};
  InSequence dummy;
  EXPECT_CALL(*signalListener, onValue(Eq("1234"))).Times(1);
  EXPECT_CALL(*signalListener, onValue(Eq("5678"))).Times(1);
  crLfUnpacker->feddata(buf1, ARRARY_SIZE(buf1),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 0);
  crLfUnpacker->feddata(buf2, ARRARY_SIZE(buf2),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 2);
}

TEST_F(GtestStringUnpacker, testCrLfUnpacker3) {
  char buf1[] = {'1', '2', '3'};
  char buf2[] = {'4', '\r', '\n', '5', '6', '7', '8', '\r', '\n'};
  InSequence dummy;
  EXPECT_CALL(*signalListener, onValue(Eq("1234"))).Times(1);
  EXPECT_CALL(*signalListener, onValue(Eq("5678"))).Times(1);
  crLfUnpacker->feddata(buf1, ARRARY_SIZE(buf1),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 0);
  crLfUnpacker->feddata(buf2, ARRARY_SIZE(buf2),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 2);
}
TEST_F(GtestStringUnpacker, testCrLfUnpacker4) {
  char buf1[] = {'1', '2', '3', '4', '\r', '\n', '5'};
  char buf2[] = {'6', '7', '8', '\r', '\n'};
  InSequence dummy;
  EXPECT_CALL(*signalListener, onValue(Eq("1234"))).Times(1);
  EXPECT_CALL(*signalListener, onValue(Eq("5678"))).Times(1);
  crLfUnpacker->feddata(buf1, ARRARY_SIZE(buf1),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 1);
  crLfUnpacker->feddata(buf2, ARRARY_SIZE(buf2),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 2);
}
TEST_F(GtestStringUnpacker, testCrLfUnpacker5) {
  char buf1[] = {'1', '2', '3', '4', '\r', '\n',
                 '5', '6', '7', '8', '\r', '\n'};
  char buf2[] = {};
  InSequence dummy;
  EXPECT_CALL(*signalListener, onValue(Eq("1234"))).Times(1);
  EXPECT_CALL(*signalListener, onValue(Eq("5678"))).Times(1);
  crLfUnpacker->feddata(buf1, ARRARY_SIZE(buf1),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 2);
  crLfUnpacker->feddata(buf2, ARRARY_SIZE(buf2),
                        [this](string var) {  //
                          signalListener->onValue(var);
                          num++;
                        });
  EXPECT_EQ(num, 2);
}
