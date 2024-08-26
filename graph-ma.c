#include <stdio.h>
#include <stdlib.h>

// Tamanho máximo da matriz de adjacências
#define MAX_VERTICES 10

// Estrutura para representar o grafo
struct Graph {
    int numVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
};

// Inicializa a estrutura de representação do grafo
// Neste caso, inicializamos a matriz de adjacências com zeros
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;

    // Inicializa a matriz de adjacências com zeros
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

// Adiciona uma aresta entre dois vértices
// Como é um grafo não direcionado, criamos nos dois sentidos
void addEdge(struct Graph* graph, int src, int dest) {
    // Aresta do vértice src para dest
    graph->adjMatrix[src][dest] = 1;

    // Aresta do vértice dest para src
    graph->adjMatrix[dest][src] = 1;
}

// Imprime o grafo
void printGraph(struct Graph* graph) {
    printf("Matriz de adjacências:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d  ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    struct Graph* graph = createGraph(6);

    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 3, 1);
    addEdge(graph, 4, 5);
    addEdge(graph, 5, 5);

    printGraph(graph);

    return 0;
}