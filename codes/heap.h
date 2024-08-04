#ifndef _HEAP_H_
#define _HEAP_H_

#include "vector.h"

typedef struct Heap Heap;

Heap *heap_constructor(int(*cmp_fn)(data_type, data_type));
void heap_push(Heap *heap, data_type data);
int heap_size(Heap *heap);
void *heap_pop(Heap *heap);
int heap_find(Heap *heap, data_type data, int(*eq_name)(void*,void*));
void heap_swap_priority(Heap *heap, data_type data, int(*eq_name)(void*,void*));
void heap_destroy(Heap *heap);

#endif