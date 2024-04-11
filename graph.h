#ifndef GR1_GRAPH_H
#define GR1_GRAPH_H

#include "node.h"

typedef struct Graph {
    int _numVertex;
    int _numUniqueEdge;
    node_t *_hash;
} *Graph, Graph_s;

Graph initVanillaGraph();
void allocateMemoryToHashTable(Graph *graph);
void resetHashTableToNull(Graph *graph);
void addEdgeToGraph(Graph *graph, int source, int destination, int position);
void DFS(Graph *graph, int source);
void BFS(Graph *graph, int source);
int getOORIndex(int source);
void traverseGraph(Graph graph, int maximum);
void freeGraph(Graph graph);
#endif //GR1_GRAPH_H
