#ifndef GR1_NODE_H
#define GR1_NODE_H

/*
 * Node: the most elementary structure of the project, used in Graph, Stack and Queue.
 */

typedef struct node {
    int _vertex : 22;
    struct node *_next;
} *node_t, node_s;

#endif //GR1_NODE_H
