#ifndef GR1_NODE_H
#define GR1_NODE_H

typedef struct node {
    int _vertex;
    struct node *_next;
} *node_t, node_s;

node_t initNode(int vertex);
node_t addNode(node_t root, int vertex);
int toString(node_t root);
void traverseNode(node_t root);

#endif //GR1_NODE_H
