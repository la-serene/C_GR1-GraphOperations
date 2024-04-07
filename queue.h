#ifndef GR1_Queue_H
#define GR1_Queue_H

#include "node.h"

typedef struct {
    node_t _front;
    node_t _rear;
} *Queue, Queue_s;

Queue initQueue();
Queue enqueue(Queue queue, node_t node);
Queue dequeue(Queue queue);
int isEmptyQueue(Queue queue);

#endif //GR1_Queue_H
