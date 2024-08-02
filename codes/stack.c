#include <stdlib.h>
#include "stack.h"

struct Stack {
    Vector *v;
};

Stack* stack_constructor() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->v = vector_construct();
    return stack;
}

int stack_size(Stack *stack) {
    return vector_size(stack->v);
}

void stack_push(Stack *stack, data_type data) {
    vector_push_back(stack->v, data);
}

data_type stack_pop(Stack *stack) {
    void *data = vector_remove(stack->v, vector_size(stack->v) - 1);
    return data;
}

void stack_destroy(Stack *stack) {
    if (stack) {
        vector_destroy(stack->v);
        free(stack);
    }
}