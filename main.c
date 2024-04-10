#include "stdio.h"
#include "stdlib.h"
#include "graph.h"

int numOutOfRange = 0;

void importDataFromFile(Graph *_graph, char *path) {
    Graph graph = *_graph;
    FILE *fPtr, *fPtrPairs;
    char buffer[100];
    char *pathPairs = "I:\\BKA\\nam_ba\\20232\\GR1\\pairs.txt";

    if ((fPtr = fopen(path, "r")) == NULL) {
        printf("Error opening file.");
        return;
    }

    if ((fPtrPairs = fopen(pathPairs, "w")) == NULL) {
        printf("Error opening file.");
        return;
    }


    if ((fPtrPairs = fopen(pathPairs, "a")) == NULL) {
        printf("Error opening file.");
        return;
    }

    // Each file has first 4 lines as info
    for (int i = 0; i < 4; i++) {
        fgets(buffer, sizeof(buffer), fPtr);
        if (!graph->_numVertex) {
            sscanf(buffer, "# Nodes: %d Edges: %d", &graph->_numVertex, &graph->_numUniqueEdge);
        }
    }

    graph->_numUniqueEdge /= 2;
    allocateMemoryToHashTable(&graph);
    resetHashTableToNull(&graph);

    int source, destination;
    while (fgets(buffer, sizeof(buffer), fPtr)) {
        sscanf(buffer, "%d  %d", &source, &destination);

        if (source < graph->_numVertex) addEdgeToGraph(&graph, source, destination, source);
        else {
            numOutOfRange += 1;
            fprintf(fPtrPairs, "%d  %d\n", source, destination);
        }
    }

    // In C, if buffer is not fulled, data will be cached until the end of program to decrease the I/O on disk
    // Therefore, call fflush to ensure that all data from fPtrPairs is ready for indexing step.
    fflush(fPtrPairs);
    printf("Successfully load data from raw file.\n");
    fclose(fPtr);
    fclose(fPtrPairs);
}

int *getNullIndex(Graph graph) {
    int track = 0;
    int *nullIndex = (int *) malloc(numOutOfRange * sizeof (int));

    for (int i = 0; i < graph->_numVertex; i++) {
        if (graph->_hash[i] == NULL) {
            nullIndex[track] = i;
            track += 1;
        }
    }

    return nullIndex;
}

void importOutOfRangeData(Graph *graph, int *nullIndex) {
    char *pathPairs = "I:\\BKA\\nam_ba\\20232\\GR1\\pairs.txt";
    FILE *fPtr;
    if ((fPtr = fopen(pathPairs, "r")) == NULL) {
        printf("Error opening file.");

        return;
    }

    char *pathOORIndex = "I:\\BKA\\nam_ba\\20232\\GR1\\index.txt";
    FILE *fPtrIndex;
    if ((fPtrIndex = fopen(pathOORIndex, "w")) == NULL) {
        printf("Error opening file.");

        return;
    }
    if ((fPtrIndex = fopen(pathOORIndex, "a")) == NULL) {
        printf("Error opening file.");

        return;
    }

    int track = 0;
    int source, destination;
    Graph tmp = *graph;
    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), fPtr)) {
        sscanf(buffer, "%d  %d", &source, &destination);

        if (tmp->_hash[nullIndex[track]] == NULL) {
            tmp->_hash[nullIndex[track]] = initNode(source);
            addNode(&tmp->_hash[nullIndex[track]], destination);
            fprintf(fPtrIndex, "%d  %d\n", nullIndex[track], source);
            continue;
        }

        if (tmp->_hash[nullIndex[track]]->_vertex == source) {
            addNode(&tmp->_hash[nullIndex[track]], destination);
            continue;
        }

        track += 1;
        tmp->_hash[nullIndex[track]] = initNode(source);
        addNode(&tmp->_hash[nullIndex[track]], destination);
        fprintf(fPtrIndex, "%d  %d\n", nullIndex[track], source);
    }

    fflush(fPtrIndex);
    printf("Successfully load out of range node from file.\n");
    fclose(fPtr);
    fclose(fPtrIndex);
}

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
    fclose(fPtr);
    printf("Successfully export all graph data to file.\n");
}

Graph importDataFromStructuredFile(Graph graph, char *path) {
    FILE *fPtr;

    if ((fPtr = fopen(path, "r")) == NULL) {
        printf("Error opening file.");
        return graph;
    }

    char buffer[1000];
    fgets(buffer, sizeof(buffer), fPtr);
    sscanf(buffer, "%d %d", &graph->_numVertex, &graph->_numUniqueEdge);
    allocateMemoryToHashTable(&graph);
    resetHashTableToNull(&graph);

    int position, vertex, next;
    while (fgets(buffer, sizeof(buffer), fPtr)) {
        sscanf(buffer, "%d %d %d", &position, &vertex, &next);

        if (graph->_hash[position] == NULL) graph->_hash[position] = initNode(vertex);
        addNode(&graph->_hash[position], next);
    }
    fclose(fPtr);
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

    // Import data
    importDataFromFile(&g, PA);
    int *nullIndex = getNullIndex(g);
    importOutOfRangeData(&g, nullIndex);

//    g = importDataFromStructuredFile(g, KY_data);
//    exportGraphToFile(g, CA_data);
//    traverseGraph(g, g->_numVertex);

    DFS(&g, 0);


//    free(nullIndex);

    return 0;
}
