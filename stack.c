#include "stdio.h"
#include "stdlib.h"
#include "stack.h"

Stack initStack() {
    Stack stack = (Stack) malloc(sizeof(Stack_s));
    stack->_top = NULL;

    return stack;
}

Stack pop(Stack stack) {
    if (isEmptyStack(stack)) printf("Stack is empty.");
    else {
        node_t tmp = stack->_top;
        stack->_top = tmp->_next;
        free(tmp);
    }

    return stack;
}

Stack push(Stack stack, node_t node) {
    if (isEmptyStack(stack)) stack->_top = initNode(node->_vertex);
    else {
        // node->_next is still pointing to an address,
        // change its _next to top may affect the original graph.
        node_t temp = initNode(node->_vertex);
        temp->_next = stack->_top;
        stack->_top = temp;
    }

    return stack;
}

int isEmptyStack(Stack stack) {
    return stack->_top == NULL;
}