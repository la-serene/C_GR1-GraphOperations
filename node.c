#include "stdio.h"
#include "stdlib.h"
#include "node.h"

node_t initNode(int vertex) {
    node_t newNode = (node_t) malloc(sizeof(node_s));
    newNode->_vertex = vertex;
    newNode->_next = NULL;

    return newNode;
}

node_t addNode(node_t root, int vertex) {
    node_t temp = root;

    while (temp->_next != NULL) {
        temp = temp->_next;
    }

    temp->_next = initNode(vertex);

    return root;
}

int toString(node_t root) {
    if (root == NULL) return -1;
    else return root->_vertex;
}

void traverseNode(node_t root) {
    if (root != NULL) {
        printf("%d", toString(root));

        while (root->_next != NULL) {
            root = root->_next;
            printf(" -> %d", root->_vertex);
        }

        printf("\n");
    }
}