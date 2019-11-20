#include "gtest/gtest.h"
extern "C" {
#include "zwtimecpp/core/utils/cutils/loop_queue.h"
}

#ifndef ARRARY_SIZE
#define ARRARY_SIZE(arrary) sizeof(arrary) / sizeof(arrary[0])
#endif

TEST(TestLoopQueue, test_u8) {
  {
    loop_queue_u8_t loop_queue;
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
    loop_queue_u8_t loop_queue;
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

  {
    //测试push_some and push some
    loop_queue_u8_t loop_queue;
    uint8_t buf[16] = {0};
    uint8_t testBuf[3] = {0, 1, 2};
    loop_queue_init_u8(&loop_queue, buf, ARRARY_SIZE(buf));

    ASSERT_TRUE(loop_queue_push_some_u8(&loop_queue, testBuf, 3));
    uint8_t value = 0;
    for (unsigned i = 0; i < 3; ++i) {
      ASSERT_TRUE(loop_queue_pop_one_u8(&loop_queue, &value));
      ASSERT_TRUE(value == i);
    }
    ASSERT_TRUE(!loop_queue_pop_one_u8(&loop_queue, &value));
  }

  {
    //测试push_some and push some
    loop_queue_u8_t loop_queue;
    uint8_t buf[16] = {0};
    uint8_t readBuf[16] = {0};
    uint8_t testBuf[3] = {0, 1, 2};
    uint8_t testBuf2[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15};
    loop_queue_init_u8(&loop_queue, buf, ARRARY_SIZE(buf));
    ASSERT_TRUE(loop_queue_get_capatity_u8(&loop_queue) ==
                (ARRARY_SIZE(buf) - 1));

    ASSERT_TRUE(loop_queue_push_some_u8(&loop_queue, testBuf, 3));
    ASSERT_TRUE(loop_queue_pop_some_u8(&loop_queue, readBuf, 3) == 3);
    ASSERT_TRUE(memcmp(readBuf, testBuf, 3 * sizeof(uint8_t)) == 0);

    //测试压入超过容量的数据
    ASSERT_TRUE(!loop_queue_push_some_u8(&loop_queue, testBuf2, 16));

    //测试推入数据和取出数据
    ASSERT_TRUE(loop_queue_push_some_u8(&loop_queue, testBuf2, 15));
    ASSERT_TRUE(loop_queue_pop_some_u8(&loop_queue, readBuf, 16) == 15);
    ASSERT_TRUE(memcmp(readBuf, testBuf2, 15 * sizeof(uint8_t)) == 0);

    ASSERT_TRUE(loop_queue_push_some_u8(&loop_queue, testBuf2, 15));
    ASSERT_TRUE(loop_queue_pop_some_u8(&loop_queue, readBuf, 7) == 7);
    ASSERT_TRUE(memcmp(readBuf, testBuf2, 7 * sizeof(uint8_t)) == 0);
    ASSERT_TRUE(loop_queue_pop_some_u8(&loop_queue, readBuf, 8) == 8);
    ASSERT_TRUE(memcmp(readBuf, testBuf2 + 7, 8 * sizeof(uint8_t)) == 0);
    ASSERT_TRUE(loop_queue_pop_some_u8(&loop_queue, readBuf, 1) == 0);
  }
}

TEST(TestLoopQueue, test_u8_push_large) {
  {
    loop_queue_u8_t loop_queue;
    uint8_t buf[16] = {0};
    loop_queue_init_u8(&loop_queue, buf, ARRARY_SIZE(buf));
    uint8_t pushbuf[] = {0, 1, 2, 3};
    for (unsigned i = 0; i < 100; ++i) {
     bool value = loop_queue_push_some_u8(&loop_queue, pushbuf, ARRARY_SIZE(pushbuf));
     if(i<=2) {
       EXPECT_TRUE(value);
     } else {
       EXPECT_TRUE(!value);
     }
    }
  }

  {
    loop_queue_u8_t loop_queue;
    uint8_t buf[16] = {0};
    loop_queue_init_u8(&loop_queue, buf, ARRARY_SIZE(buf));
    uint8_t pushbuf[] = {1};
    for (unsigned i = 0; i < 100; ++i) {
      bool value = loop_queue_push_some_u8(&loop_queue, pushbuf, ARRARY_SIZE(pushbuf));
      if (i <= 14) {
        EXPECT_TRUE(value);
      } else {
        EXPECT_TRUE(!value);
      }
    }
  }

  {
    loop_queue_u8_t loop_queue;
    uint8_t buf[16] = {0};
    loop_queue_init_u8(&loop_queue, buf, ARRARY_SIZE(buf));
    uint8_t pushbuf[] = {0, 1, 2, 3};
    uint8_t popbuf[] = {0, 1, 2, 3};
    for (unsigned i = 0; i < 100; ++i) {
      bool value =
          loop_queue_push_some_u8(&loop_queue, pushbuf, ARRARY_SIZE(pushbuf));
      if (!value) {
        loop_queue_pop_some_u8(&loop_queue, popbuf, 2);
      }
    }
  }
}

TEST(TestLoopQueue, test_u8_push_some_and_pop_some) {
  loop_queue_u8_t loop_queue;
  uint8_t buf[9] = {0};
  loop_queue_init_u8(&loop_queue, buf, ARRARY_SIZE(buf));
  
  for(unsigned i = 0; i < 100; ++i) {
    uint8_t pushbuf[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    uint8_t popbuf[ARRARY_SIZE(pushbuf)] = {0};
    loop_queue_push_some_u8(&loop_queue, pushbuf, 6);
    loop_queue_pop_some_u8(&loop_queue, popbuf, 3);
    loop_queue_push_some_u8(&loop_queue, pushbuf + 6, 5);
    loop_queue_pop_some_u8(&loop_queue, popbuf + 3, 8);

    EXPECT_TRUE(memcmp(pushbuf, popbuf, ARRARY_SIZE(pushbuf)) == 0);
  }
}

TEST(TestLoopQueue, test_u32) {
  {
    loop_queue_u32_t loop_queue;
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
    loop_queue_u32_t loop_queue;
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

  {
    //测试push_some and push some
    loop_queue_u32_t loop_queue;
    uint32_t buf[16] = {0};
    uint32_t testBuf[3] = {0, 1, 2};
    loop_queue_init_u32(&loop_queue, buf, ARRARY_SIZE(buf));

    ASSERT_TRUE(loop_queue_push_some_u32(&loop_queue, testBuf, 3));
    uint32_t value = 0;
    for (unsigned i = 0; i < 3; ++i) {
      ASSERT_TRUE(loop_queue_pop_one_u32(&loop_queue, &value));
      ASSERT_TRUE(value == i);
    }
    ASSERT_TRUE(!loop_queue_pop_one_u32(&loop_queue, &value));
  }

  {
    //测试push_some and push some
    loop_queue_u32_t loop_queue;
    uint32_t buf[16] = {0};
    uint32_t readBuf[16] = {0};
    uint32_t testBuf[3] = {0, 1, 2};
    uint32_t testBuf2[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15};
    loop_queue_init_u32(&loop_queue, buf, ARRARY_SIZE(buf));
    ASSERT_TRUE(loop_queue_get_capatity_u32(&loop_queue) ==
                (ARRARY_SIZE(buf) - 1));

    ASSERT_TRUE(loop_queue_push_some_u32(&loop_queue, testBuf, 3));
    ASSERT_TRUE(loop_queue_pop_some_u32(&loop_queue, readBuf, 3) == 3);
    ASSERT_TRUE(memcmp(readBuf, testBuf, 3 * sizeof(uint32_t)) == 0);

    //测试压入超过容量的数据
    ASSERT_TRUE(!loop_queue_push_some_u32(&loop_queue, testBuf2, 16));

    //测试推入数据和取出数据
    ASSERT_TRUE(loop_queue_push_some_u32(&loop_queue, testBuf2, 15));
    ASSERT_TRUE(loop_queue_pop_some_u32(&loop_queue, readBuf, 16) == 15);
    ASSERT_TRUE(memcmp(readBuf, testBuf2, 15 * sizeof(uint32_t)) == 0);

    ASSERT_TRUE(loop_queue_push_some_u32(&loop_queue, testBuf2, 15));
    ASSERT_TRUE(loop_queue_pop_some_u32(&loop_queue, readBuf, 7) == 7);
    ASSERT_TRUE(memcmp(readBuf, testBuf2, 7 * sizeof(uint32_t)) == 0);
    ASSERT_TRUE(loop_queue_pop_some_u32(&loop_queue, readBuf, 8) == 8);
    ASSERT_TRUE(memcmp(readBuf, testBuf2 + 7, 8 * sizeof(uint32_t)) == 0);
    ASSERT_TRUE(loop_queue_pop_some_u32(&loop_queue, readBuf, 1) == 0);
  }
}