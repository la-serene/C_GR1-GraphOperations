#include "stdio.h"
#include "stdlib.h"
#include "graph.h"

#pragma pack(1)

Graph importDataFromFile(Graph graph, char *path) {
    FILE *fPtr;
    char buffer[1000];
    int numVertex = 0;
    int numEdge = 0;

    if ((fPtr = fopen(path, "r")) == NULL) {
        printf("Error opening file.");
        return graph;
    }

    // Each file has first 4 lines as info
    for (int i = 0; i < 4; i++) {
        fgets(buffer, sizeof(buffer), fPtr);
        if (!numVertex) {
            sscanf(buffer, "# Nodes: %d Edges: %d", &numVertex, &numEdge);
        }
    }

    graph->_numVertex = numVertex;
    graph->_numUniqueEdge = numEdge / 2;
    allocateMemoryToVisited(&graph);
    resetVisited(&graph);
    allocateMemoryToHashTable(&graph);
    resetHashTableToNull(&graph);

    while (fgets(buffer, sizeof(buffer), fPtr)) {
        int source, destination;
        sscanf(buffer, "%d  %d", &source, &destination);

        addEdgeToGraph(&graph, source, destination);
    }

    return graph;
}

//int isVertexCover(Graph graph, char *path, int *visited) {
//    FILE *fPtr;
//    char buffer[1000];
//    int currentEdge = 0;
//
//    if ((fPtr = fopen(path, "r")) == NULL) {
//        printf("Error opening file.");
//        return -1;
//    }
//
//    // Each test file has first 3 lines as info
//    for (int i = 0; i < 3; i++) {
//        fgets(buffer, sizeof(buffer), fPtr);
//    }
//
//    while (fgets(buffer, sizeof(buffer), fPtr)) {
//        int nominee;
//        sscanf(buffer, "v %d", &nominee);
//
//        currentEdge += countValidEdge(graph, nominee, &visited);
//    }
//
//    if (currentEdge == graph->_numUniqueEdge) {
//        printf("Is vertex cover.");
//        return 1;
//    } else {
//        printf("Not vertex cover");
//        return 0;
//    }
//}

void exportGraphToFile(Graph graph, char *filename) {
    FILE *fPtr;

    if ((fPtr = fopen(filename, "w")) == NULL) {
        printf("Error opening file.");
        return;
    }

    fprintf(fPtr, "%d %d\n", graph->_numVertex, graph->_numUniqueEdge);

    int vertex;
    for (int i = 0; i < graph->_numVertex; i++) {
        if (graph->_hash[i] == NULL) {
            fprintf(fPtr, "%d\n", i);
            continue;
        }

        node_t temp = graph->_hash[i];
        vertex = temp->_vertex;
        while (temp->_next != NULL) {
            fprintf(fPtr, "%d %d %d\n", i, vertex, temp->_next->_vertex);
            temp = temp->_next;
        }
    }

    printf("Successfully export all graph data to file\n");
}

Graph importDataFromStructuredFile(Graph graph, char *path) {
    FILE *fPtr;
    char buffer[1000];
    int position, vertex, next;

    if ((fPtr = fopen(path, "r")) == NULL) {
        printf("Error opening file.");
        return graph;
    }

    fgets(buffer, sizeof(buffer), fPtr);
    sscanf(buffer, "%d %d", &graph->_numVertex, &graph->_numUniqueEdge);
    allocateMemoryToVisited(&graph);
    resetVisited(&graph);
    allocateMemoryToHashTable(&graph);
    resetHashTableToNull(&graph);

    while (fgets(buffer, sizeof(buffer), fPtr)) {
        sscanf(buffer, "%d %d %d", &position, &vertex, &next);

        if (graph->_hash[position] == NULL) graph->_hash[position] = initNode(vertex);
        addNode(&graph->_hash[position], next);
    }

    printf("Successfully import all data from structured file\n");

    return graph;
}

int main() {
    char *KY = "..\\dataset\\roadNet-KY.txt\\roadNet-KY.txt";       // Simple graph data for testing
    char *CA = "..\\dataset\\roadNet-CA.txt\\roadNet-CA.txt";
    char *PA = "..\\dataset\\roadNet-PA.txt\\roadNet-PA.txt";
    char *TX = "..\\dataset\\roadNet-TX.txt\\roadNet-TX.txt";

    char *KY_test = "..\\testset\\roadNet-KY.vc";
    char *CA_test = "..\\testset\\roadNet-CA.vc";
    char *PA_test = "..\\testset\\roadNet-PA.vc";
    char *TX_test = "..\\testset\\roadNet-TX.vc";

    char *KY_data = "..\\graph_data\\roadNet-KY.txt";
    char *CA_data = "..\\graph_data\\roadNet-CA.txt";
    char *PA_data = "..\\graph_data\\roadNet-PA.txt";
    char *TX_data = "..\\graph_data\\roadNet-TX.txt";

    Graph g = initVanillaGraph();
    g = importDataFromStructuredFile(g, CA_data);
//    g = importDataFromFile(g, CA);



//    traverseGraph(g, g->_numVertex);

    return 0;
}
