#pragma once
#include "defines.h"

// notes:
// arrays are initially created with a capacity of 2
// when a darray reaches capacity, it resizes by a factor of 2
// currently there is no defragmentation or collapse of array

#define DARRAY_DEFAULT_CAPACITY 2
#define DARRAY_RESIZE_FACTOR 2

#define create_darray(array)                                             \
    {                                                                    \
        array = _create_darray(sizeof(*array), DARRAY_DEFAULT_CAPACITY); \
    }

#define darray_push(array, value)                         \
    {                                                     \
        typeof(value) temp = value;                       \
        array = _darray_push(array, &temp, sizeof(value));\
    }

void *_create_darray(u32 stride, u32 capacity);
void *_darray_push(void *array, const void *strct, u32 stride);
void *darray_pop(void *array);
void *darray_get(void *array, u32 index);
void free_darray(void *array);

u32 darray_size(void *array);
u32 darray_length(void *array);
u32 darray_stride(void *array);
u32 darray_capacity(void *array);
