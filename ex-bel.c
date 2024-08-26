#include <stdio.h>
#include <stdlib.h>

#define NUM_VERTICES 6
#define BRANCO 0
#define CINZA 1
#define PRETO 2

// Estrutura para uma lista encadeada de adjacência
typedef struct Nodo {
    int vertice;
    struct Nodo* proximo;
} Nodo;

// Estrutura para o grafo com lista de adjacências
typedef struct {
    Nodo* listaAdj[NUM_VERTICES];
    int cor[NUM_VERTICES];
    int distancia[NUM_VERTICES];
    int predecessor[NUM_VERTICES];
} Grafo;

// Estrutura de uma fila simples
typedef struct {
    int items[NUM_VERTICES];
    int frente, traseira;
} Fila;

// Função para inicializar a fila
void inicializaFila(Fila *f) {
    f->frente = 0;
    f->traseira = -1;
}

// Função para verificar se a fila está vazia
int filaVazia(Fila *f) {
    return f->traseira < f->frente;
}

// Função para enfileirar um elemento
void enfileirar(Fila *f, int valor) {
    if (f->traseira < NUM_VERTICES - 1) {
        f->traseira++;
        f->items[f->traseira] = valor;
    }
}

// Função para desenfileirar um elemento
int desenfileirar(Fila *f) {
    if (!filaVazia(f)) {
        int valor = f->items[f->frente];
        f->frente++;
        return valor;
    }
    return -1;
}

// Função para inicializar o grafo
void inicializaGrafo(Grafo* g) {
    for (int i = 0; i < NUM_VERTICES; i++) {
        g->listaAdj[i] = NULL;
        g->cor[i] = BRANCO;
        g->distancia[i] = -1;
        g->predecessor[i] = -1;
    }
}

// Função para adicionar uma aresta ao grafo
void adicionaAresta(Grafo* g, int origem, int destino) {
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    novoNodo->vertice = destino;
    novoNodo->proximo = g->listaAdj[origem];
    g->listaAdj[origem] = novoNodo;

    // Adicionar também a aresta na direção oposta, já que o grafo é não direcionado
    novoNodo = (Nodo*)malloc(sizeof(Nodo));
    novoNodo->vertice = origem;
    novoNodo->proximo = g->listaAdj[destino];
    g->listaAdj[destino] = novoNodo;
}

// Função BFS que constrói a árvore de busca em largura
void BFS(Grafo* g, int s) {
    Fila fila;
    inicializaFila(&fila);

    g->cor[s] = CINZA;
    g->distancia[s] = 0;
    enfileirar(&fila, s);

    while (!filaVazia(&fila)) {
        int u = desenfileirar(&fila);
        Nodo* temp = g->listaAdj[u];
        while (temp != NULL) {
            int v = temp->vertice;
            if (g->cor[v] == BRANCO) {
                g->cor[v] = CINZA;
                g->distancia[v] = g->distancia[u] + 1;
                g->predecessor[v] = u;
                enfileirar(&fila, v);
            }
            temp = temp->proximo;
        }
        g->cor[u] = PRETO;
    }
}

// Função para imprimir a árvore de busca em largura
void imprimeArvoreBFS(Grafo* g) {
    printf("Vértice   Distância   Predecessor\n");
    for (int i = 0; i < NUM_VERTICES; i++) {
        printf("%d\t\t%d\t\t%d\n", i, g->distancia[i], g->predecessor[i]);
    }
}

int main() {
    Grafo g;
    inicializaGrafo(&g);

    // Adicionar arestas ao grafo
    adicionaAresta(&g, 0, 1);
    adicionaAresta(&g, 0, 2);
    adicionaAresta(&g, 1, 3);
    adicionaAresta(&g, 1, 4);
    adicionaAresta(&g, 2, 4);
    adicionaAresta(&g, 3, 4);
    adicionaAresta(&g, 3, 5);

    int vertice_inicial = 0;
    printf("Busca em Largura (BFS) a partir do vértice %d:\n", vertice_inicial);
    BFS(&g, vertice_inicial);
    imprimeArvoreBFS(&g);

    return 0;
}
