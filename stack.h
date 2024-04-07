#ifndef GR1_STACK_H
#define GR1_STACK_H

#include "node.h"

typedef struct {
    node_t _top;
} *Stack, Stack_s;

Stack initStack();
Stack pop(Stack stack);
Stack push(Stack stack, node_t node);
int isEmptyStack(Stack stack);

#endif //GR1_STACK_H
