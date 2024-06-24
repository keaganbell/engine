#include "logger.h"

#include "containers/darray.h"

#include <stdlib.h>
#include <string.h>

typedef struct darray_header {
    u32 length;   // number of elements in the array
    u32 stride;   // number of bytes per element
    u32 capacity; // number of elements darray can currently hold
} darray_header_t;

static inline void set_capacity(void *array, u32 capacity) {
    if (array == NULL) {
        ERROR("can't set array capacity for null array");
        return;
    }
    u32 header_size = sizeof(darray_header_t);
    darray_header_t *header = (darray_header_t *)(array - header_size);
    header->capacity = capacity;
}

static inline void set_stride(void *array, u32 stride) {
    if (array == NULL) {
        ERROR("can't set array stride for null array");
        return;
    }
    u32 header_size = sizeof(darray_header_t);
    darray_header_t *header = (darray_header_t *)(array - header_size);
    header->stride = stride;
}

static inline void set_length(void *array, u32 length) {
    if (array == NULL) {
        ERROR("can't set array length for null array");
        return;
    }
    u32 header_size = sizeof(darray_header_t);
    darray_header_t *header = (darray_header_t *)(array - header_size);
    header->length = length;
}

static inline void *resize_darray(void *array) {
    void *temp = array;
    array = _create_darray(darray_stride(temp), darray_capacity(temp)*DARRAY_RESIZE_FACTOR);
    memcpy(array, temp, darray_size(temp));
    set_length(array, darray_length(temp));
    free_darray(temp);
    return array;
}

void *_create_darray(u32 stride, u32 capacity) {
    u32 header_size = sizeof(darray_header_t);
    void *array = malloc(header_size + stride*capacity);
    memset(array, 0, header_size + stride*capacity);
    set_stride(array + header_size, stride);
    set_capacity(array + header_size, capacity);
    return array + header_size;
}

void free_darray(void *array) {
    free(array - sizeof(darray_header_t));
}

void *_darray_push(void *array, const void *strct, u32 stride) {
    if (array == NULL) {
        FATAL("tried to push struct onto null array pointer");
        return NULL;
    }
    if (darray_stride(array) != stride) {
        FATAL("struct size doesn't match the stride of array");
        return NULL;
    }
    if (darray_length(array) + 1 > darray_capacity(array)) {
        array = resize_darray(array);
    }
    void *head = array + darray_length(array)*darray_stride(array);
    memcpy(head, strct, stride);
    set_length(array, darray_length(array)+1);
    return array;
}

void *pop_struct(void *array) {
    return NULL;
}

void *darray_get(void *array, u32 index) {
    if (index >= darray_length(array)) {
        FATAL("array index out of bounds");
        return NULL;
    }
    return (array + index*darray_stride(array));
}

u32 darray_size(void *array) {
    u32 header_size = sizeof(darray_header_t);
    darray_header_t *header = (darray_header_t *)(array - header_size);
    return header->stride*header->capacity;
}

u32 darray_length(void *array) {
    u32 header_size = sizeof(darray_header_t);
    darray_header_t *header = (darray_header_t *)(array - header_size);
    return header->length;
}

u32 darray_stride(void *array) {
    u32 header_size = sizeof(darray_header_t);
    darray_header_t *header = (darray_header_t *)(array - header_size);
    return header->stride;
}

u32 darray_capacity(void *array) {
    u32 header_size = sizeof(darray_header_t);
    darray_header_t *header = (darray_header_t *)(array - header_size);
    return header->capacity;
}
