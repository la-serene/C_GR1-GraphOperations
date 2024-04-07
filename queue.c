#include "stdio.h"
#include "stdlib.h"
#include "queue.h"

Queue initQueue() {
    Queue newQueue = (Queue) malloc(sizeof (Queue_s));
    newQueue->_front = NULL;
    newQueue->_rear = NULL;

    return newQueue;
}

Queue enqueue(Queue queue, node_t node) {
    node_t newNode = initNode(node->_vertex);

    if (isEmptyQueue(queue)) {
        queue->_front = newNode;
        queue->_rear = newNode;
    } else {
        queue->_rear->_next = newNode;
        queue->_rear = newNode;
    }

    return queue;
}

Queue dequeue(Queue queue) {
    if (isEmptyQueue(queue)) printf("Queue is empty now.");
    else {
        node_t tmp = queue->_front;
        queue->_front = tmp->_next;
        free(tmp);
    }

    return queue;
}

int isEmptyQueue(Queue queue) {
    return queue->_front == NULL;
}