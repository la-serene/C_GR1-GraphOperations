#ifndef GR1_NODE_H
#define GR1_NODE_H

/*
 * Node: the most elementary structure of the project, used in Graph, Stack and Queue.
 */

typedef struct node {
    int _vertex;
    struct node *_next;
} *node_t, node_s;

node_t initNode(int vertex);
node_t addNode(node_t root, int vertex);
int toString(node_t root);
void traverseNode(node_t root);ut

#endif //GR1_NODE_H
