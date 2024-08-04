#include <stdio.h>
#include <stdlib.h>

#include "deque.h"

struct Deque {
    data_type *arr;
    int start;
    int end;
    int size;
    int allocated;
};

Deque *deque_construct() {

    Deque *f = (Deque *)calloc(1, sizeof(Deque));
    f->arr = (data_type *)calloc(1, sizeof(data_type));
    f->start = 0;
    f->end = 0;
    f->size = 0;
    f->allocated = 1;

    return f;
}

void deque_push_back(Deque *f, data_type item) {
    if (f->size >= f->allocated) {
        f->allocated *= 2;

        data_type *new_array = (data_type *)malloc(f->allocated * sizeof(data_type));

        for (int i = 0; i < f->size; i++) {
            int idx = (f->start + i) % f->size;
            new_array[i] = f->arr[idx];
        }
        f->start = 0;
        f->end = f->size;

        free(f->arr);
        f->arr = new_array;
    }
    f->arr[f->end] = item;
    f->end = (f->end + 1) % f->allocated;
    f->size++;
}

void deque_push_front(Deque *f, data_type item) {
    if (f->size >= f->allocated) {
        f->allocated *= 2;

        data_type *new_array = (data_type *)malloc(f->allocated * sizeof(data_type));

        for (int i = 0; i < f->size; i++) {
            int idx = (f->start + i) % f->size;
            new_array[i] = f->arr[idx];
        }
        f->start = 0;
        f->end = f->size;

        free(f->arr);
        f->arr = new_array;
    }

    if (f->start - 1 < 0)
        f->start = f->allocated;
  
    f->arr[f->start - 1] = item;
    f->start--;
    f->size++;
}

int deque_size(Deque *f) {
    return f->size;
}

data_type deque_pop_back(Deque *f) {
    if (f->end - 1 < 0) 
        f->end = f->allocated;
    
    data_type popped = f->arr[f->end - 1];
    f->end = (f->end - 1) % f->allocated;
    f->size--;
    return popped;
}

data_type deque_pop_front(Deque *f) {
    data_type popped = f->arr[f->start];
    f->start = (f->start + 1) % f->allocated;
    f->size--;
    return popped;

}

int deque_find(Deque *f, data_type item, int(*eq_name)(void*,void*)) {
    int i = f->start;

    while (i != f->end) {
        if (eq_name(item, f->arr[i])) {
            return i;
        }
        i = (i + 1) % f->allocated;
    }
    return -1;
}

void deque_destroy(Deque *f) {
    if (f != NULL) {
        if (f->arr != NULL) {
            free(f->arr);
        }
        free(f);
    }
}