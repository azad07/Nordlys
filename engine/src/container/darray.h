/**
 * @file darray.h
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-06-29
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#pragma once

#include "defines.h"

 /**
  * Memory layout of dynamic array.
  * u64 capacity = number of elements that can be held.
  * u64 length = number of elements currently contained.
  * u64 stride = size of each element in bytes.
  * void* elements.
  *
  */

enum {
    DARRAY_CAPACITY = 0,
    DARRAY_LENGTH,
    DARRAY_STRIDE,
    DARRAY_FIELD_LENGTH
};

#define DARRAY_DEFAULT_CAPACITY 1
#define DARRAY_RESIZE_FACTOR 2

NAPI void* _darray_create(u64 length, u64 stride);
NAPI void _darray_destroy(void* array);

NAPI u64 _darray_field_get(void* array, u64 field);
NAPI void _darray_field_set(void* array, u64 field, u64 value);

NAPI void* _darray_resize(void* array);

NAPI void* _darray_push(void* array, const void* value_ptr);
NAPI void _darray_pop(void* array, void* dest);

NAPI void* _darray_pop_at(void* array, u64 index, void* dest);
NAPI void* _darray_insert_at(void* array, u64 index, void* value_ptr);

#define darray_create(type) \
    _darray_create(DARRAY_DEFAULT_CAPACITY, sizeof(type))

#define darray_reserve(type, capacity) \
    _darray_create(capacity, sizeof(type))

#define darray_destroy(array) \
    _darray_destroy(array)

#define darray_push(array, value)           \
    {                                       \
        typeof(value) temp = value;         \
        array = _darray_push(array, &temp); \
    }

#define darray_pop(array, value_ptr) \
    _darray_pop(array, value_ptr)

#define darray_insert_at(array, index, value)           \
    {                                                   \
        typeof(value) temp = value;                     \
        array = _darray_insert_at(array, index, &temp); \
    }

#define darray_pop_at(array, index, value_ptr) \
    _darray_pop_at(array, index, value_ptr)

#define darray_clear(array)      \
    _darray_field_set(array, DARRAY_LENGTH, 0)

#define darray_capacity(array)  \
    _darray_field_get(array, DARRAY_CAPACITY)

#define darray_length(array)        \
    _darray_field_get(array, DARRAY_LENGTH)

#define darray_stride(array)    \
    _darray_field_get(array, DARRAY_STRIDE)

#define darray_length_set(array, value)    \
    _darray_field_set(array, DARRAY_LENGTH, value)


