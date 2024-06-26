#include "stdio.h"
#include "stdlib.h"
#include "graph.h"
#include "string.h"

int k = 0;
int *visited = NULL;
int *ds = NULL;
int *waiting = NULL;

int *resetArray(int numElem) {
    int *data_structure = (int *) malloc(numElem * sizeof(int));
    for (int i = 0; i < numElem; i++) data_structure[i] = -1;

    return data_structure;
}

Graph initVanillaGraph() {
    Graph newGraph = (Graph) malloc(sizeof(Graph_s));
    newGraph->_numVertex = 0;
    newGraph->_numUniqueEdge = 0;
    newGraph->_hash = NULL;

    return newGraph;
}

void allocateMemoryToHashTable(Graph *graph) {
    Graph tmp = *graph;
    tmp->_hash = (node_t *) malloc(tmp->_numVertex * sizeof(node_t));
}

void resetHashTableToNull(Graph *graph) {
    Graph tmp = *graph;
    for (int i = 0; i < tmp->_numVertex; i++) tmp->_hash[i] = NULL;
}

void addEdgeToGraph(Graph *graph, int source, int destination, int position) {
    Graph tmp = *graph;
    if (tmp->_hash[position] == NULL) tmp->_hash[position] = initNode(source);
    addNode(&tmp->_hash[position], destination);
}

void DFS(Graph *graph, int source) {
    k = 0;
    Graph tmp = *graph;
    visited = resetArray(tmp->_numVertex);
    ds = resetArray(tmp->_numVertex);
    waiting = resetArray(tmp->_numVertex);

    int *stack = ds;
    int numInStack = 0, top = 0;

    stack[top] = source;
    numInStack = 1;

    int index;
    node_t adjList;
    while (numInStack) {
        numInStack -= 1;
        top = (top == 0) ? 0 : top - 1;
        source = stack[top];
        index = (source < tmp->_numVertex) ? source : getOORIndex(source);
        adjList = tmp->_hash[index];
        visited[index] = 1;
        k += 1;
        if (k % 100000 == 0) printf("%d %d\n", k, source);

        while (adjList->_next != NULL || adjList->_next != NULL) {
            adjList = adjList->_next;
            source = adjList->_vertex;
            index = (source < tmp->_numVertex) ? source : getOORIndex(source);

            if (visited[index] == 1 || waiting[index] == 1) {
                continue;
            }

            stack[top] = source;
            waiting[index] = 1;
            top += 1;
            numInStack += 1;
        }
    }
    printf("k: %d\n", k);
    free(visited);
    free(stack);
    free(waiting);
}

void BFS(Graph *graph, int source) {
    k = 0;
    Graph tmp = *graph;
    visited = resetArray(tmp->_numVertex);
    ds = resetArray(tmp->_numVertex);
    waiting = resetArray(tmp->_numVertex);

    int *queue = ds;
    int numInQueue = 0, front = 0, rear = 0;
    int index;
    node_t adjList;

    numInQueue = 1;
    queue[front] = source;
    while (numInQueue) {
        numInQueue -= 1;
        source = queue[front];
        front += 1;
        index = (source < tmp->_numVertex) ? source : getOORIndex(source);
        adjList = tmp->_hash[index];
        visited[index] = 1;
        k += 1;
        if (k % 100000 == 0) printf("%d %d\n", k, source);

        while (adjList->_next != NULL || adjList->_next != NULL) {
            adjList = adjList->_next;
            source = adjList->_vertex;
            index = (source < tmp->_numVertex) ? source : getOORIndex(source);

            if (visited[index] == 1 || waiting[index] == 1) {
                continue;
            }

            rear += 1;
            queue[rear] = source;
            waiting[index] = 1;
            numInQueue += 1;
        }
    }

    printf("k: %d\n", k);
    free(visited);
    free(queue);
    free(waiting);
}

int getOORIndex(int source) {
    char *pathOORIndex = "I:\\BKA\\nam_ba\\20232\\GR1\\index.txt";
    FILE *fPtrIndex;
    char buffer[100];
    if ((fPtrIndex = fopen(pathOORIndex, "r")) == NULL) {
        printf("Error opening index file.\n");
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return -1;
    }

    int idx, node_id;
    while (fgets(buffer, sizeof(buffer), fPtrIndex)) {
        sscanf(buffer, "%d  %d", &idx, &node_id);
        if (node_id == source) {
            fclose(fPtrIndex);
            return idx;
        }
    }
    fclose(fPtrIndex);

    return -1;
}

void traverseGraph(Graph graph, int maximum) {
    if (graph->_hash == NULL) printf("Graph is empty");
    else {
        for (int i = 0; i < maximum; i++) {
            traverseNode(&graph->_hash[i]);
        }
    }
    printf("Graph fully traversed!\n");
}

void freeGraph(Graph graph) {
    for (int i = 0; i < graph->_numVertex; i++) free(graph->_hash[i]);
    free(graph->_hash);
}