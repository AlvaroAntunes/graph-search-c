#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "vector.h"

typedef struct Queue Queue;

Queue *queue_constructor();

int queue_size(Queue *queue);

void enqueue(Queue *queue, void *data);

void *dequeue(Queue *queue);

void queue_destroy(Queue *queue);

#endif