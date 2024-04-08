#include "stdio.h"
#include "stdlib.h"
#include "graph.h"

Graph initGraph() {
    Graph newGraph;
    newGraph._numVertex = 0;

    return newGraph;
}

Graph assignMemoryToGraph(Graph graph) {
    graph._hash = (node_t *) malloc(graph._numVertex * sizeof(node_t));

    return graph;
}


Graph resetHashTableToNull(Graph graph) {
    for (int i = 0; i < graph._numVertex; i++) {
        graph._hash[i] = NULL;
    }

    return graph;
}

Graph addEdgeToGraph(Graph graph, int source, int destination) {
    int position = source % graph._numVertex;

    if (source >= graph._numVertex) {
        position = getValidPosition(graph, source, position, graph._numVertex);
        if (position == -1) position = getValidPosition(graph, source, 0, position);
    }

    if (graph._hash[position] == NULL) {
        graph._hash[position] = initNode(source);
        graph._hash[position] = addNode(graph._hash[position], destination);

        return graph;
    }

    if (graph._hash[position]->_vertex == source) {
        graph._hash[position] = addNode(graph._hash[position], destination);

        return graph;
    }

    if (graph._hash[position]->_vertex != source) {
        graph._hash[position] = initNode(source);
        graph._hash[position] = addNode(graph._hash[position], destination);

        return graph;
    }

    return graph;
}

int getValidPosition(Graph graph, int source, int start, int end) {
    /*
     * Loop through graph's hash table from start to end
     * to find the first NULL index.
     * NOTE: Only use in graph's data ingestion step.
     * Params:
     *      graph: graph
     *      start: starting index
     *      end: ending index
     * Return:
     *      i: first NULL index
     */
    for (int i = start; i < end; i++)
        if (graph._hash[i] == NULL || graph._hash[i]->_vertex == source) return i;

    return -1;
}

int findPosition(Graph graph, int source) {
    /*
     * Find position of a vertex in a fulfilled graph.
     */
    int position = source % graph._numVertex;

    if (graph._hash[position]->_vertex == source) return position;

    for (int i = position + 1; i < graph._numVertex; i++) {
        if (graph._hash[position] == NULL) continue;
        if (graph._hash[i]->_vertex == source) return i;
    }

    for (int i = 0; i < position; i++) {
        if (graph._hash[position] == NULL) continue;
        if (graph._hash[i]->_vertex == source) return i;
    }

    return -1;
}

int countValidEdge(Graph graph, int vertex, int **visited) {
    int count = 0;
    int position = findPosition(graph, vertex);
    node_t temp = graph._hash[position];
    int *array = *visited;
    array[position] = 1;

    while (temp->_next != NULL) {
        int next_vertex = temp->_next->_vertex;
        position = findPosition(graph, next_vertex);
        if (array[position] != -1) {
            temp = temp->_next;
            continue;
        }
        temp = temp->_next;
        count += 1;
    }

    return count;
}

void traverseGraph(Graph graph, int maximum) {
    if (graph._hash == NULL) printf("Graph is empty");
    else {
        for (int i = 0; i < maximum; i++) {
            traverseNode(graph._hash[i]);
        }
    }
}

void DFS(Graph graph, int source, Stack stack, int *visited, int k) {
    int position = findPosition(graph, source);
    printf("%d %d\n", k, source);

    node_t temp = graph._hash[position];
    visited[position] = source;

    while (temp->_next != NULL) {
        position = findPosition(graph, temp->_next->_vertex);
        if (visited[position] != -1) {
            temp = temp->_next;
            continue;
        }

        stack = push(stack, temp->_next);
        temp = temp->_next;
    }

    if (isEmptyStack(stack)) return;
    else {
        source = stack->_top->_vertex;
        stack = pop(stack);
        DFS(graph, source, stack, visited, k + 1);
    }
}

void BFS(Graph graph, int source, Queue queue, int *visited) {
    int position = findPosition(graph, source);
    printf("%d ", source);

    node_t temp = graph._hash[position];
    visited[position] = source;

    while (temp->_next != NULL) {
        position = findPosition(graph, temp->_next->_vertex);
        if (visited[position] != -1) {
            temp = temp->_next;
            continue;
        }

        queue = enqueue(queue, temp->_next);
        temp = temp->_next;
    }

    if (isEmptyQueue(queue)) return;
    else {
        source = queue->_front->_vertex;
        queue = dequeue(queue);
        BFS(graph, source, queue, visited);
    }
}

void freeGraph(Graph graph) {
    free(graph._hash);
}