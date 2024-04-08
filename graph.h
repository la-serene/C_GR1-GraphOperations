#ifndef GR1_GRAPH_H
#define GR1_GRAPH_H

#include "node.h"

typedef struct Graph {
    int _numVertex;
    int _numUniqueEdge;
    int *_visited;
    node_t *_hash;
} *Graph, Graph_s;

Graph initVanillaGraph();
void allocateMemoryToVisited(Graph *graph);
void resetVisited(Graph *graph);
void allocateMemoryToHashTable(Graph *graph);
void resetHashTableToNull(Graph *graph);
void addEdgeToGraph(Graph *graph, int source, int destination);
void DFS(Graph *graph, int source);
void traverseGraph(Graph graph, int maximum);
void freeGraph(Graph graph);
#endif //GR1_GRAPH_H
