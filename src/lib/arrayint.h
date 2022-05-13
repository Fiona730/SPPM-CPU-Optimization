#ifndef _ARRAY_INT_H
#define _ARRAY_INT_H

#include "array.h"

typedef struct {
    size_t size;
    size_t capacity;
    int *data;
} IntArray;

static inline void arr_add_int(IntArray *arr, void *item) {
    if (arr->size == arr->capacity) {
        arr->capacity = _ARRAY_INCRE_MULT * arr->capacity;
        arr->data = realloc(arr->data, arr->capacity * sizeof(int));
    }

    void *target_addr = (uint8_t *) arr->data + arr->size * sizeof(int);
    memcpy(target_addr, item, sizeof(int));
    arr->size++;
}

static inline int arr_get_int(const IntArray *arr, size_t index) {
    assert(index < arr->size);
    return (int) arr->data[index];
}

static inline void arr_set_int(IntArray *arr, size_t index, int value) {
    assert(index < arr->size);
    arr->data[index] = value;
}

static inline void arr_set_add_int(IntArray *arr, size_t index, int value) {
    assert(index < arr->size);
    arr->data[index] += value;
}

static inline size_t arr_size_int(const IntArray *arr) {
    return arr->size;
}

static inline void arr_init_int(IntArray *arr, size_t capacity, size_t initial_size) {
    assert(initial_size <= capacity);
    arr->size = initial_size;
    arr->capacity = capacity;
    arr->data = malloc(capacity * sizeof(int));
}

static inline void arr_free_int(IntArray *arr) {
    free(arr->data);
}

#endif