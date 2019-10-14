#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "zwtimecpp/core/utils/cutils/compiler_config.h"

typedef struct __vector_s __vector_t;
struct __vector_s {
  size_t size;
  size_t capacity;
  uint8_t* data;
  int each_size;
};
void __vector_init(__vector_t* vector, size_t each_size, uint8_t* data,
                   size_t size);
uint8_t* __vector_begin(__vector_t* vector);
size_t __vector_size(__vector_t* vector);
size_t __vector_capacity(__vector_t* vector);
void __vector_clear(__vector_t* vector);
bool __vector_push(__vector_t* vector, uint8_t* data);
bool __vector_is_full(__vector_t* vector);

#define ARRARY_ENABLE_SUPPORT(name, type)                                    \
  typedef struct { __vector_t vector; } vector_##name##_t;                   \
  /**                                                                        \
   * @brief 初始化数组                                                  \
   * @vector                                                                 \
   * @data,存储数据的空间                                             \
   * @capacity,空间大小                                                  \
   */                                                                        \
  static INLINE void vector_##name##_init(vector_##name##_t* vector,         \
                                          type* data, size_t capacity) {     \
    __vector_init(&vector->vector, sizeof(type), (uint8_t*)data,             \
                  capacity * sizeof(type));                                  \
    return;                                                                  \
  }                                                                          \
  /**                                                                        \
   * @brief 获得数组的开始地址                                      \
   *                                                                         \
   */                                                                        \
  static INLINE type* vector_##name##_begin(vector_##name##_t* vector) {     \
    return (type*)__vector_begin(&vector->vector);                           \
  }                                                                          \
  /**                                                                        \
   * @brief 当前数组中数量量                                         \
   *                                                                         \
   */                                                                        \
  static INLINE size_t vector_##name##_size(vector_##name##_t* vector) {     \
    return __vector_size(&vector->vector);                                   \
  }                                                                          \
  /**                                                                        \
   * @brief 获得数组的容积                                            \
   *                                                                         \
   */                                                                        \
  static INLINE size_t vector_##name##_capacity(vector_##name##_t* vector) { \
    return __vector_capacity(&vector->vector);                               \
  }                                                                          \
  /**                                                                        \
   * @brief 清理数组                                                     \
   *                                                                         \
   */                                                                        \
  static INLINE void vector_##name##_clear(vector_##name##_t* vector) {      \
    __vector_clear(&vector->vector);                                         \
    return;                                                                  \
  }                                                                          \
  /**                                                                        \
    * @brief 压入一个数据                                              \
    *                                                                        \
    */                                                                       \
  static INLINE bool vector_##name##_push(vector_##name##_t* vector,         \
                                          type data) {                       \
    return __vector_push(&vector->vector, (uint8_t*)&data);                  \
  }                                                                          \
  static INLINE bool vector_##name##_push_p(vector_##name##_t* vector,       \
                                            const type* data) {              \
    return __vector_push(&vector->vector, (uint8_t*)data);                   \
  }                                                                          \
  /**                                                                        \
   * @brief 压入一个数据      \                                        \
   *                                                                         \
   */                                                                        \
  static INLINE bool vector_##name##_push1(vector_##name##_t* vector,        \
                                           type* data) {                     \
    return __vector_push(&vector->vector, (uint8_t*)data);                   \
  }                                                                          \
  static INLINE bool vector_##name##_is_full(vector_##name##_t* vector) {    \
    return __vector_is_full(&vector->vector);                                \
  }

ARRARY_ENABLE_SUPPORT(u8, uint8_t)
ARRARY_ENABLE_SUPPORT(u16, uint16_t)
