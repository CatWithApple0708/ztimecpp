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
