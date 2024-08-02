
#ifndef _DEQUE_H_
#define _DEQUE_H_

typedef void* data_type;

typedef struct Deque Deque;

Deque *deque_construct();
void deque_push_back(Deque *f, data_type item);
void deque_push_front(Deque *f, data_type item);
int deque_size(Deque *f);
data_type deque_pop_back(Deque *f);
data_type deque_pop_front(Deque *f);
void deque_destroy(Deque *f);

#endif