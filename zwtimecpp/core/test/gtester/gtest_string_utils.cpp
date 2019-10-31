#include "gtest/gtest.h"

#include "zwtimecpp/core/utils/string_utils.hpp"
#ifndef ARRARY_SIZE
#define ARRARY_SIZE(arrary) sizeof(arrary) / sizeof(arrary[0])
#endif
using namespace std;
using namespace zwsd;
using namespace core;

TEST(TestStringUtils, test_byte_to_string) {
  {
    vector<uint8_t> byte = {0x24, 0xdb};
    string bytestr = StringUtils::bytesToString(byte);
    EXPECT_EQ(bytestr, string("24DB"));
  }

  {
    vector<uint8_t> byte = {1, 2, 3, 4, 5, 6};
    string bytestr = StringUtils::bytesToString(byte);
    EXPECT_EQ(bytestr, string("010203040506"));
  }
}

TEST(TestStringUtils, test_splitByString) {
  {
    string var = "\n123456-1234-6789\r";
    int pos = var.find("/r/n", 0);
    auto bytestr = StringUtils::splitByStrDelim(var, "\r\n");
    EXPECT_TRUE(bytestr.size() == 1);
    EXPECT_EQ(bytestr[0], var);
  }

  {
    string var = "123\r\n456";
    int pos = var.find("/r/n", 0);
    auto bytestr = StringUtils::splitByStrDelim(var, "\r\n");
    EXPECT_TRUE(bytestr.size() == 2);
    EXPECT_EQ(bytestr[0], "123");
    EXPECT_EQ(bytestr[1], "456");
  }

  {
    string var = "\r\n123\r\n456\r\n";
    int pos = var.find("/r/n", 0);
    auto bytestr = StringUtils::splitByStrDelim(var, "\r\n");
    EXPECT_TRUE(bytestr.size() == 4);
    EXPECT_EQ(bytestr[0], "");
    EXPECT_EQ(bytestr[1], "123");
    EXPECT_EQ(bytestr[2], "456");
    EXPECT_EQ(bytestr[3], "");
  }
}
