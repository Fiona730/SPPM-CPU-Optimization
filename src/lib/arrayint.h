#ifndef _ARRAY_INT_H
#define _ARRAY_INT_H

#include "array.h"
#include "common.h"

typedef struct {
    size_t size;
    size_t capacity;
    int *data;
} IntArray;

static inline void arr_add_int(IntArray *arr, int item) {
    if (arr->size == arr->capacity) {
        arr->capacity = _ARRAY_INCRE_MULT * arr->capacity;
        // realloc with align
        int *old_data = arr->data;
        arr->data = malloc_align(arr->capacity * sizeof(int));
        memcpy(arr->data, old_data, arr->size * sizeof(int));
        free_align(old_data);
    }

    arr->data[arr->size] = item;
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
    arr->data = malloc_align(capacity * sizeof(int));
}

static inline void arr_free_int(IntArray *arr) {
    free_align(arr->data);
}

#endif