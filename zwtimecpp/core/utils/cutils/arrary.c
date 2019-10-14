#include "arrary.h"
#include <string.h>
void __vector_init(__vector_t* vector, size_t each_size, uint8_t* data,
                   size_t size) {
  vector->capacity = (size / each_size);
  vector->data = data;
  vector->each_size = each_size;
  vector->size = 0;
  return;
}
uint8_t* __vector_begin(__vector_t* vector) { return vector->data; }
size_t __vector_size(__vector_t* vector) { return vector->size; }
size_t __vector_capacity(__vector_t* vector) { return vector->capacity; }
void __vector_clear(__vector_t* vector) {
  vector->size = 0;
  return;
}
bool __vector_push(__vector_t* vector, uint8_t* data) {
  if (vector->size >= vector->capacity) return false;
  memcpy(&vector->data[vector->size * vector->each_size], data,
         vector->each_size);
  vector->size++;
  return true;
}
bool __vector_is_full(__vector_t* vector) {
  if (vector->size >= vector->capacity) return true;
  return false;
}
