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
    // Therefore, call fflush to ensure that all data from fPtrPairs is written in index.txt for indexing step.
    fflush(fPtrPairs);
    printf("Successfully load data from raw file.\n");
    fclose(fPtr);
    fclose(fPtrPairs);
}

int *getNullIndex(Graph graph) {
    int track = 0;
    int *nullIndex = (int *) malloc(numOutOfRange * sizeof(int));

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

void print_state_menu() {
    printf("\nChoose a dataset:\n");
    printf("1. CA\n");
    printf("2. PA\n");
    printf("3. TX\n");
    printf("0. Exit\n");
}

void print_option_menu() {
    printf("\nChoose an operation:\n");
    printf("1. DFS\n");
    printf("2. BFS\n");
    printf("3. Check Vertex Cover\n");
    printf("4. Traverse Graph\n");
    printf("0. Back to State Menu\n");
}

int isValidVertex(Graph *graph, int vertex) {
    Graph tmp = *graph;

    for (int i = 0; i < tmp->_numVertex; i++) {
        if (tmp->_hash[i]->_vertex == vertex) return 1;
    }

    return 0;
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

    int option, isBreak = 0;
    while (1) {
        Graph g = initVanillaGraph();

        print_state_menu();
        printf("Enter your choice (0 to exit): ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                importDataFromFile(&g, CA);
                break;
            case 2:
                importDataFromFile(&g, PA);
                break;
            case 3:
                importDataFromFile(&g, TX);
                break;
            case 4:
                importDataFromFile(&g, KY);
                break;
            case 0:
                isBreak = 1;
                break;
            default:
                printf("Invalid option.\n");
        }

        if (isBreak) break;

        // Case if user didn't press 0
        int *nullIndex = getNullIndex(g);
        importOutOfRangeData(&g, nullIndex);

        // Operation Menu
        while(1) {
            print_option_menu();
            printf("Enter your choice (0 to exit): ");
            scanf("%d", &option);

            switch (option) {
                case 1:
                    printf("\n========Performing DFS========\n");
                    printf("Enter starting vertex:");
                    scanf("%d", &option);

                    if (isValidVertex(&g, option)) DFS(&g, option);
                    else printf("Invalid vertex");

                    break;
                case 2:
                    printf("\n========Performing BFS========\n");
                    printf("Enter starting vertex: ");
                    scanf("%d", &option);

                    if (isValidVertex(&g, option)) BFS(&g, option);
                    else printf("Invalid vertex");

                    break;
                case 3:
                    printf("\n========Checking Vertex Cover========\n");
                    break;
                case 4:
                    printf("\n========Traversing the graph========\n");
                    printf("Enter number of node traversed: (if 0, print all node)");
                    scanf("%d", &option);

                    if (option == 0) option = g->_numVertex;
                    traverseGraph(g, option);

                    break;
                case 0:
                    isBreak = 1;
                default:
                    printf("Invalid option.\n");
            }
            if (isBreak) break;
        }

        isBreak = 0;

        freeGraph(g);
        free(nullIndex);
    }

    return 0;
}
