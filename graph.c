#include "stdio.h"
#include "stdlib.h"
#include "graph.h"

Graph initVanillaGraph() {
    Graph newGraph = (Graph) malloc(sizeof (Graph_s));
    newGraph->_numVertex = 0;
    newGraph->_numUniqueEdge = 0;
	newGraph->_visited = NULL;
	newGraph->_hash = NULL;

    return newGraph;
}

void allocateMemoryToVisited(Graph *graph) {
	Graph tmp = *graph;
	tmp->_visited = (int *) malloc(tmp->_numVertex * sizeof (int));
}

void resetVisited(Graph *graph) {
	Graph tmp = *graph;
	for (int i = 0; i < tmp->_numVertex; i++) tmp->_visited[i] = -1; 
}

void allocateMemoryToHashTable(Graph *graph) {
	Graph tmp = *graph;
	tmp->_hash = (node_t *) malloc(tmp->_numVertex * sizeof (node_t));
}

void resetHashTableToNull(Graph *graph) {
	Graph tmp = *graph;
	for (int i = 0; i < tmp->_numVertex; i++) tmp->_hash[i] = NULL; 
}

void addEdgeToGraph(Graph *graph, int source, int destination) {
	Graph tmp = *graph;
	if (source >= tmp->_numVertex) {
		for (int i = tmp->_numVertex - 1; i >= 0; i--) {
			if (tmp->_hash[i] == NULL) {
				tmp->_hash[i] = initNode(source);
				addNode(&tmp->_hash[i], destination);
				
				return;
			}
			
			if (tmp->_hash[i]->_vertex == source) {
				addNode(&tmp->_hash[i], destination);	
				
				return;
			}
		}
	}
	
	int index = source % tmp->_numVertex;
	for (int i = index; i < tmp->_numVertex; i++) {
		if (tmp->_hash[i] == NULL) {
			tmp->_hash[i] = initNode(source);
			addNode(&tmp->_hash[i], destination);
				
			return;
		}
			
		if (tmp->_hash[i]->_vertex == source) {
			addNode(&tmp->_hash[i], destination);	
				
			return;
		}	
	}
	
	for (int i = 0; i < index; i++) {
		if (tmp->_hash[i] == NULL) {
			tmp->_hash[i] = initNode(source);
			addNode(&tmp->_hash[i], destination);
				
			return;
		}
			
		if (tmp->_hash[i]->_vertex == source) {
			addNode(&tmp->_hash[i], destination);	
				
			return;
		}	
	}
}

void DFS(Graph *graph, int source) {

}

void traverseGraph(Graph graph, int maximum) {
    if (graph->_hash == NULL) printf("Graph is empty");
    else {
        for (int i = 0; i < maximum; i++) {
            traverseNode(&graph->_hash[i]);
        }
    }
}

void freeGraph(Graph graph) {
    for (int i = 0; i < graph->_numVertex; i++) free(graph->_hash[i]);
	free(graph->_visited);
	free(graph->_hash);
}