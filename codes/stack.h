#ifndef _STACK_H_
#define _STACK_H_

#include "vector.h"
typedef struct Stack Stack;

Stack* stack_constructor();
int stack_size(Stack *stack);
void stack_push(Stack *stack, data_type data);
void *stack_pop(Stack *stack);
void stack_destroy(Stack *stack);

#endif