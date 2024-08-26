#include <stdio.h>
#include <stdlib.h>

#define BRANCO 0
#define CINZENTO 1
#define PRETO 2
#define NIL -1

typedef struct Node {
    int destino;
    struct Node* prox;
} Node;

typedef struct Grafo {
    int numVertices;
    Node** listaAdj;
} Grafo;

int tempo;

// Função para criar um grafo com n vértices
Grafo* criarGrafo(int vertices) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = vertices;

    // Criar uma lista de adjacências para cada vértice
    grafo->listaAdj = (Node**)malloc(vertices * sizeof(Node*));

    // Inicializar a lista de adjacências de cada vértice como NULL
    for (int i = 0; i < vertices; i++) {
        grafo->listaAdj[i] = NULL;
    }

    return grafo;
}

// Função para adicionar uma aresta no grafo
void adicionarAresta(Grafo* grafo, int origem, int destino) {
    Node* novoNode = (Node*)malloc(sizeof(Node));
    novoNode->destino = destino;
    novoNode->prox = grafo->listaAdj[origem];
    grafo->listaAdj[origem] = novoNode;
}

// Função utilitária para a busca em profundidade e construção da estrutura parentizada
void DFSUtil(Grafo* grafo, int v, int* visitado, char* resultado, int* indice) {
    visitado[v] = 1;
    resultado[(*indice)++] = '(';
    resultado[(*indice)++] = '0' + v;

    Node* temp = grafo->listaAdj[v];
    while (temp != NULL) {
        int adj = temp->destino;
        if (!visitado[adj]) {
            DFSUtil(grafo, adj, visitado, resultado, indice);
        }
        temp = temp->prox;
    }

    resultado[(*indice)++] = '0' + v;
    resultado[(*indice)++] = ')';
}

// Busca em profundidade (DFS) e imprimir a estrutura parentizada
void DFS(Grafo* grafo) {
    int* visitado = (int*)malloc(grafo->numVertices * sizeof(int));
    char* resultado = (char*)malloc(2 * grafo->numVertices * sizeof(char));
    int indice = 0;

    for (int i = 0; i < grafo->numVertices; i++) {
        visitado[i] = 0;
    }

    // Caso de grafo não conexo
    for (int i = 0; i < grafo->numVertices; i++) {
        if (!visitado[i]) {
            DFSUtil(grafo, i, visitado, resultado, &indice);
        }
    }
    resultado[indice] = '\0';

    // Caso de grafo conexo
    // DFSUtil(grafo, verticeInicial, visitado, resultado, &indice);
    // resultado[indice] = '\0';

    printf("Estrutura parentizada: %s\n", resultado);

    free(visitado);
    free(resultado);
}

int main() {
    int numVertices = 9;
    Grafo* grafo = criarGrafo(numVertices);

    // Adicionar arestas ao grafo
    adicionarAresta(grafo, 0, 1);
    adicionarAresta(grafo, 0, 4);
    adicionarAresta(grafo, 1, 2);
    adicionarAresta(grafo, 1, 4);
    adicionarAresta(grafo, 2, 3);
    adicionarAresta(grafo, 3, 1);
    adicionarAresta(grafo, 4, 3);
    adicionarAresta(grafo, 5, 0);
    adicionarAresta(grafo, 5, 4);
    adicionarAresta(grafo, 6, 5);
    adicionarAresta(grafo, 6, 7);
    adicionarAresta(grafo, 6, 8);
    adicionarAresta(grafo, 7, 5);
    adicionarAresta(grafo, 7, 8);
    adicionarAresta(grafo, 8, 7);

    // Executar a busca em profundidade
    printf("Busca em Profundidade (DFS) com estrutura parentizada:\n");
    DFS(grafo);

    return 0;
}
