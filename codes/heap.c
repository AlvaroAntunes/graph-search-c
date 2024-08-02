#include <stdlib.h>
#include "heap.h"

struct Heap {
    Vector *v;
    int(*cmp_fn)(data_type, data_type);
};

Heap *heap_constructor(int (*cmp_fn)(data_type, data_type)) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->v = vector_construct();
    heap->cmp_fn = cmp_fn;

    return heap;
}

void heap_push(Heap *heap, data_type data) {
    vector_push_back(heap->v, data);

    int idx = vector_size(heap->v) - 1;

    while (idx > 0) {
        int idx_father = (idx - 1) / 2;

        if (heap->cmp_fn(data, vector_get(heap->v, idx_father)) < 0) {
            vector_swap(heap->v, idx, idx_father);
            idx = idx_father;
        } 
        else {
            break;
        }
    }
}

void *heap_pop(Heap *heap) {
    int idx = 0, min = 0;

    if (vector_size(heap->v) >= 2) {
        vector_swap(heap->v, idx, vector_size(heap->v) - 1);
    }
    
    void *data = vector_remove(heap->v, vector_size(heap->v) - 1);

    while(1) {
        min = idx;
        int left_child = 2 * idx + 1;
        int right_child = 2 * idx + 2;

        if ((left_child < vector_size(heap->v)) &&
            (heap->cmp_fn(vector_get(heap->v, left_child), vector_get(heap->v, min))) < 0) {
                min = left_child;
            }
        
        if ((right_child < vector_size(heap->v)) &&
            (heap->cmp_fn(vector_get(heap->v, right_child), vector_get(heap->v, min))) < 0) {
                min = right_child;
            }

        if (min != idx) {
            vector_swap(heap->v, idx, min);
            idx = min;
        }
        else {
            break;
        }
    }
    return data;
}

int heap_size(Heap *heap) {
    return vector_size(heap->v);
}

void heap_destroy(Heap *heap) {
    if (heap != NULL) {
        if (heap->v != NULL) {
            vector_destroy(heap->v);
        }    
        free(heap);
    }
}