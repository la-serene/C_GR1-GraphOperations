#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "graph.h"

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

    graph._numVertex = numVertex;
    graph._numUniqueEdge = numEdge / 2;
    graph = assignMemoryToGraph(graph);
    graph = resetHashTableToNull(graph);

    while (fgets(buffer, sizeof(buffer), fPtr)) {
        int source, destination;
        sscanf(buffer, "%d  %d", &source, &destination);

        graph = addEdgeToGraph(graph, source, destination);
    }

    return graph;
}

int isVertexCover(Graph graph, char *path, int *visited) {
    FILE *fPtr;
    char buffer[1000];
    int currentEdge = 0;

    if ((fPtr = fopen(path, "r")) == NULL) {
        printf("Error opening file.");
        return -1;
    }

    // Each test file has first 3 lines as info
    for (int i = 0; i < 3; i++) {
        fgets(buffer, sizeof(buffer), fPtr);
    }

    while (fgets(buffer, sizeof(buffer), fPtr)) {
        int nominee;
        sscanf(buffer, "v %d", &nominee);

        currentEdge += countValidEdge(graph, nominee, &visited);
    }

    if (currentEdge == graph._numUniqueEdge) {
        printf("Is vertex cover.");
        return 1;
    } else {
        printf("Not vertex cover");
        return 0;
    }
}

void exportGraphToFile(Graph graph, char *filename) {
    FILE *fPtr;

    if ((fPtr = fopen(filename, "w")) == NULL) {
        printf("Error opening file.");
        return;
    }

    fprintf(fPtr, "%d %d\n", graph._numVertex, graph._numUniqueEdge);

    int vertex;
    for (int i = 0; i < graph._numVertex; i++) {
        if (graph._hash[i] == NULL) {
            fprintf(fPtr, "%d\n", i);
            continue;
        }

        node_t temp = graph._hash[i];
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
    sscanf(buffer, "%d %d", &graph._numVertex, &graph._numUniqueEdge);
    graph = assignMemoryToGraph(graph);
    graph = resetHashTableToNull(graph);

    while (fgets(buffer, sizeof(buffer), fPtr)) {
        sscanf(buffer, "%d %d %d", &position, &vertex, &next);

        if (graph._hash[position] == NULL) graph._hash[position] = initNode(vertex);
        graph._hash[position] = addNode(graph._hash[position], next);
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

    Graph g = initGraph();

//    g = importDataFromFile(g, TX);

//    g = importDataFromStructuredFile(g, TX_data);

//    int *visited = (int *) malloc(g._numVertex * sizeof (int));
//    for (int i = 0; i < g._numVertex; i++) visited[i] = -1;

//    Stack stack = initStack();
//    DFS(g, 0, stack, visited);

//    Queue queue = initQueue();
//    BFS(g, 3, queue, visited);

//    isVertexCover(g, TX_test, visited);

//    exportGraphToFile(g, TX_data);
//    traverseGraph(g, g._numVertex);

    /*
     * Result:
     * CA: vertex cover
     * PA: not vertex cover
     * TX: vertex cover
     */

    freeGraph(g);
//    free(stack);
//    free(queue);
//    free(visited);

    return 0;
}
