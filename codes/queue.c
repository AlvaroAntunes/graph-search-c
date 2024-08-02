#include <stdlib.h>
#include "queue.h"

struct Queue {
    Vector *v;
};

Queue* queue_constructor() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->v = vector_construct();
    return queue;
}

int queue_size(Queue *queue) {
    return vector_size(queue->v);
}

void enqueue(Queue *queue, void *data) {
    vector_push_back(queue->v, data);
}

void *dequeue(Queue *queue) {
    int first = 0;
    void *data = vector_remove(queue->v, first);
    return data;
}

void queue_destroy(Queue *queue) {
    if (queue) {
        vector_destroy(queue->v);
        free(queue);
    }
}