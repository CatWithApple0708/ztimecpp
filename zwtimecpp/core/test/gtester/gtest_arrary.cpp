#include "gtest/gtest.h"
extern "C" {
#include "zwtimecpp/core/utils/cutils/arrary.h"
}

#ifndef ARRARY_SIZE
#define ARRARY_SIZE(arrary) sizeof(arrary) / sizeof(arrary[0])
#endif

TEST(TestArrary, test_u8) {
  uint8_t buf[128];
  vector_u8_t vector;

  vector_u8_init(&vector, buf, ARRARY_SIZE(buf));

  for (unsigned testNum = 0; testNum < 2; ++testNum) {
    for (unsigned i = 0; i < vector_u8_capacity(&vector); ++i) {
      EXPECT_TRUE(vector_u8_push(&vector, i));
      EXPECT_EQ(vector_u8_size(&vector), (size_t)i + 1);
    }
    EXPECT_TRUE(!vector_u8_push(&vector, 1));
    EXPECT_TRUE(vector_u8_is_full(&vector));

    for (unsigned i = 0; i < vector_u8_size(&vector); ++i) {
      EXPECT_EQ(vector_u8_begin(&vector)[i], (size_t)i);
    }
    vector_u8_clear(&vector);
    EXPECT_EQ(vector_u8_size(&vector), (size_t)0);
  }
}
