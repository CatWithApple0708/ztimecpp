#pragma once
/*
   _                   ___
  | |   ___  ___ _ __ / _ \ _  _ ___ _  _ ___
  | |__/ _ \/ _ \ '_ \ (_) | || / -_) || / -_)
  |____\___/\___/ .__/\__\_\\_,_\___|\_,_\___|
                |_|
*/
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct __loop_queue_s __loop_queue_t;
struct __loop_queue_s {
  uint8_t *buf;
  size_t capacity;

  size_t read_offset;  // real_offset = read_offset*each_element_size
  size_t write_offset;
  size_t each_element_size;
};

/*
   _   _
  | | | |___ __ _ __ _ ___
  | |_| (_-</ _` / _` / -_)
   \___//__/\__,_\__, \___|
                 |___/
*/
// /*使能对uint8_t类型的支持*/
// LOOP_QUEUE_ENABLE_SUPPORT(uint8_t);
// void usage() {
//   uint8_t buf[16] = {0};
//   __loop_queue_t loop_queue;
//   loop_queue_push_one_uint8_t(&loop_queue, 1);
// }
//
// /*使能对uint16_t类型的支持*/
// LOOP_QUEUE_ENABLE_SUPPORT(uint16_t);
// void usage() {
//   uint16_t buf[16] = {0};
//   __loop_queue_t loop_queue;
//   loop_queue_push_one_uint16_t(&loop_queue, 1);
// }

/**
 * @brief 初始化队列
 *
 * @param queue
 * @param each_element_size 每个元素所使用的空间大小
 * @param data
 * @param size
 */
void __loop_queue_init_xxxx(__loop_queue_t *queue, size_t each_element_size,
                            uint8_t *data, size_t size);
/**
 * @brief pop一个元素
 *
 * @param queue
 * @param data
 * @return true
 * @return false
 */
bool __loop_queue_pop_one_xxxx(__loop_queue_t *queue, void *data);
#if 0

/**
 * @brief pop一个元素
 *
 * @param queue
 * @param data
 * @return true
 * @return false
 */
int __loop_queue_pop_some_xxxx(__loop_queue_t *queue, void *data, int num);
#endif
/**
 * @brief push一个元素
 *
 * @param queue
 * @param data
 * @return true
 * @return false
 */
bool __loop_queue_push_one_xxxx(__loop_queue_t *queue, const void *data);
/**
 * @brief 判断队列是否为空
 *
 * @param queue
 * @return true
 * @return false
 */
bool __loop_queue_is_empty(__loop_queue_t *queue);
/**
 * @brief 判断队列是否满
 *
 * @param queue
 * @return true
 * @return false
 */
bool __loop_queue_is_full(__loop_queue_t *queue);
/**
 * @brief 获得队列当前size
 *
 * @param queue
 * @return size_t
 */
size_t __loop_queue_get_size(__loop_queue_t *queue);

#define LOOP_QUEUE_ENABLE_SUPPORT(name, type)                                 \
  typedef struct { __loop_queue_t handler; } loop_queue_##name;               \
  static inline void loop_queue_init_##name(loop_queue_##name *queue,         \
                                            type *data, size_t size) {        \
    __loop_queue_init_xxxx(&queue->handler, sizeof(type), (uint8_t *)data,    \
                           size * sizeof(type));                              \
  }                                                                           \
  static inline bool loop_queue_pop_one_##name(loop_queue_##name *queue,      \
                                               type *data) {                  \
    return __loop_queue_pop_one_xxxx(&queue->handler, data);                  \
  }                                                                           \
  static inline bool loop_queue_push_one_##name(loop_queue_##name *queue,     \
                                                type data) {                  \
    return __loop_queue_push_one_xxxx(&queue->handler, &data);                \
  }                                                                           \
  static inline bool loop_queue_is_empty_##name(loop_queue_##name *queue) {   \
    return __loop_queue_is_empty(&queue->handler);                            \
  }                                                                           \
  static inline bool loop_queue_is_full_##name(loop_queue_##name *queue) {    \
    return __loop_queue_is_full(&queue->handler);                             \
  }                                                                           \
  static inline size_t loop_queue_get_size_##name(loop_queue_##name *queue) { \
    return __loop_queue_get_size(&queue->handler);                            \
  }

/**
 * @brief 哪里用到这个定义在哪个c文件中使用下面的宏使能对相应结构体的支持
 *
 */
LOOP_QUEUE_ENABLE_SUPPORT(u8, uint8_t);
LOOP_QUEUE_ENABLE_SUPPORT(u16, uint16_t);
LOOP_QUEUE_ENABLE_SUPPORT(u32, uint32_t);
LOOP_QUEUE_ENABLE_SUPPORT(i8, int8_t);
LOOP_QUEUE_ENABLE_SUPPORT(i16, int16_t);
LOOP_QUEUE_ENABLE_SUPPORT(i32, int32_t);