#include "stdio.h"
#include "stdlib.h"
#include "node.h"

node_t initNode(int vertex) {
    node_t newNode = malloc(sizeof (node_s));
    newNode->_vertex = vertex;
    newNode->_next = NULL;

    return newNode;
}

void addNode(node_t *root, int vertex) {
    if (*root == NULL) *root = initNode(vertex);
    else {
        node_t tmp = *root;
        while (tmp->_next != NULL) {
            tmp = tmp->_next;
        }
        tmp->_next = initNode(vertex);
    }
}

void traverseNode(node_t *root) {
    node_t tmp = *root;
    if (tmp != NULL) {
        printf("%d", tmp->_vertex);

        while (tmp->_next != NULL) {
            tmp = tmp->_next;
            printf(" -> %d", tmp->_vertex);
        }

        printf("\n");
    }
}