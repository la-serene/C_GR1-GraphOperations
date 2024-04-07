#ifndef GR1_GRAPH_H
#define GR1_GRAPH_H

#include "node.h"
#include "queue.h"
#include "stack.h"

typedef struct Graph {
    int _numVertex;
    int _numUniqueEdge;
    node_t *_hash;
} Graph;

Graph initGraph();
Graph assignMemoryToGraph(Graph graph);
Graph resetHashTableToNull(Graph graph);
Graph addEdgeToGraph(Graph graph, int source, int destination);
int getValidPosition(Graph graph, int source, int start, int end);
int findPosition(Graph graph, int source);
int countValidEdge(Graph graph, int vertex, int **visited);
void traverseGraph(Graph graph, int maximum);
void DFS(Graph graph, int source, Stack stack, int *visited);
void BFS(Graph graph, int source, Queue queue, int *visited);
void freeGraph(Graph);

#endif //GR1_GRAPH_H