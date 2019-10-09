#include "gtest/gtest.h"
extern "C" {
#include "zwtimecpp/core/utils/cutils/loop_queue.h"
}

#ifndef ARRARY_SIZE
#define ARRARY_SIZE(arrary) sizeof(arrary) / sizeof(arrary[0])
#endif

TEST(TestLoopQueue, test_u8) {
  {
    loop_queue_u8 loop_queue;
    uint8_t buf[16] = {0};

    loop_queue_init_u8(&loop_queue, buf, ARRARY_SIZE(buf));
    ASSERT_TRUE(loop_queue_is_empty_u8(&loop_queue));
    ASSERT_TRUE(!loop_queue_is_full_u8(&loop_queue));
    ASSERT_TRUE(loop_queue_get_size_u8(&loop_queue) == 0);

    ASSERT_TRUE(loop_queue_push_one_u8(&loop_queue, 1));
    ASSERT_TRUE(!loop_queue_is_empty_u8(&loop_queue));
    ASSERT_TRUE(loop_queue_get_size_u8(&loop_queue) == 1);
    uint8_t value = 0;
    ASSERT_TRUE(loop_queue_pop_one_u8(&loop_queue, &value));
    ASSERT_TRUE(value == 1);
    ASSERT_TRUE(loop_queue_is_empty_u8(&loop_queue));
    ASSERT_TRUE(loop_queue_get_size_u8(&loop_queue) == 0);
  }

  {
    loop_queue_u8 loop_queue;
    uint8_t buf[16] = {0};

    loop_queue_init_u8(&loop_queue, buf, ARRARY_SIZE(buf));

    for (unsigned j = 0; j < 2; ++j) {
      for (unsigned i = 0; i < 15; ++i) {
        ASSERT_TRUE(loop_queue_push_one_u8(&loop_queue, i));
      }
      ASSERT_TRUE(loop_queue_is_full_u8(&loop_queue));
      ASSERT_TRUE(!loop_queue_push_one_u8(&loop_queue, 20));
      ASSERT_TRUE(!loop_queue_push_one_u8(&loop_queue, 20));
      ASSERT_TRUE(!loop_queue_push_one_u8(&loop_queue, 20));

      for (unsigned i = 0; i < 15; ++i) {
        uint8_t value = 0;
        ASSERT_TRUE(loop_queue_pop_one_u8(&loop_queue, &value));
        ASSERT_TRUE(value == i);
      }
      ASSERT_TRUE(loop_queue_is_empty_u8(&loop_queue));
    }
  }
}

TEST(TestLoopQueue, test_u32) {
  {
    loop_queue_u32 loop_queue;
    uint32_t buf[16] = {0};

    loop_queue_init_u32(&loop_queue, buf, ARRARY_SIZE(buf));
    ASSERT_TRUE(loop_queue_is_empty_u32(&loop_queue));
    ASSERT_TRUE(!loop_queue_is_full_u32(&loop_queue));
    ASSERT_TRUE(loop_queue_get_size_u32(&loop_queue) == 0);

    ASSERT_TRUE(loop_queue_push_one_u32(&loop_queue, 1));
    ASSERT_TRUE(!loop_queue_is_empty_u32(&loop_queue));
    ASSERT_TRUE(loop_queue_get_size_u32(&loop_queue) == 1);
    uint32_t value = 0;
    ASSERT_TRUE(loop_queue_pop_one_u32(&loop_queue, &value));
    ASSERT_TRUE(value == 1);
    ASSERT_TRUE(loop_queue_is_empty_u32(&loop_queue));
    ASSERT_TRUE(loop_queue_get_size_u32(&loop_queue) == 0);
  }

  {
    loop_queue_u32 loop_queue;
    uint32_t buf[16] = {0};

    loop_queue_init_u32(&loop_queue, buf, ARRARY_SIZE(buf));

    for (unsigned j = 0; j < 2; ++j) {
      for (unsigned i = 0; i < 15; ++i) {
        ASSERT_TRUE(loop_queue_push_one_u32(&loop_queue, i));
      }
      ASSERT_TRUE(loop_queue_is_full_u32(&loop_queue));
      ASSERT_TRUE(!loop_queue_push_one_u32(&loop_queue, 20));
      ASSERT_TRUE(!loop_queue_push_one_u32(&loop_queue, 20));
      ASSERT_TRUE(!loop_queue_push_one_u32(&loop_queue, 20));

      for (unsigned i = 0; i < 15; ++i) {
        uint32_t value = 0;
        ASSERT_TRUE(loop_queue_pop_one_u32(&loop_queue, &value));
        ASSERT_TRUE(value == i);
      }
      ASSERT_TRUE(loop_queue_is_empty_u32(&loop_queue));
    }
  }

  loop_queue_u32 loop_queue;
  uint32_t buf[16] = {0};

  loop_queue_init_u32(&loop_queue, buf, ARRARY_SIZE(buf));
  loop_queue_push_one_u32()

}