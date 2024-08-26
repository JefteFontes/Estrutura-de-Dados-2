#include <stdio.h>
#include <stdlib.h>

#define NUM_VERTICES 9
#define BRANCO 0  // Vértice não visitado
#define CINZA 1   // Vértice visitado, mas não totalmente explorado
#define PRETO 2   // Vértice completamente explorado

// Estrutura de um nodo na lista de adjacência
typedef struct Node {
    int vertice;
    struct Node* next;
} Node;

// Estrutura do grafo
typedef struct Grafo {
    Node* listaAdj[NUM_VERTICES];
} Grafo;

// Estrutura de uma fila simples
typedef struct {
    int items[NUM_VERTICES];
    int frente, traseira;
} Fila;

// Função para inicializar a fila
void inicializaFila(Fila* f) {
    f->frente = 0;
    f->traseira = -1;
}

// Função para verificar se a fila está vazia
int filaVazia(Fila* f) {
    return f->traseira < f->frente;
}

// Função para enfileirar um elemento
void enfileirar(Fila* f, int valor) {
    if (f->traseira < NUM_VERTICES - 1) {
        f->traseira++;
        f->items[f->traseira] = valor;
    }
}

// Função para desenfileirar um elemento
int desenfileirar(Fila* f) {
    if (!filaVazia(f)) {
        int valor = f->items[f->frente];
        f->frente++;
        return valor;
    }
    return -1;
}

// Função para criar um novo nodo na lista de adjacência
Node* criarNode(int vertice) {
    Node* novoNode = (Node*)malloc(sizeof(Node));
    novoNode->vertice = vertice;
    novoNode->next = NULL;
    return novoNode;
}

// Função para adicionar uma aresta ao grafo (não direcionado)
void adicionarAresta(Grafo* grafo, int origem, int destino) {
    Node* novoNode = criarNode(destino);
    novoNode->next = grafo->listaAdj[origem];
    grafo->listaAdj[origem] = novoNode;

    // Como o grafo é não direcionado, adicionamos também a aresta inversa
    novoNode = criarNode(origem);
    novoNode->next = grafo->listaAdj[destino];
    grafo->listaAdj[destino] = novoNode;
}

// Implementação da BFS para construir a árvore de caminhos mínimos
void BFS(Grafo* grafo, int s, int antecessor[NUM_VERTICES]) {
    int cor[NUM_VERTICES];    // Armazena a cor de cada vértice
    int d[NUM_VERTICES];      // Armazena a distância do vértice s

    Fila fila;
    inicializaFila(&fila);

    // Inicialização
    for (int i = 0; i < NUM_VERTICES; i++) {
        cor[i] = BRANCO;
        d[i] = -1;  // Infinito (desconhecido)
        antecessor[i] = -1; // NIL
    }

    cor[s] = CINZA;
    d[s] = 0;
    antecessor[s] = -1;  // NIL
    enfileirar(&fila, s);

    // Processamento da BFS
    while (!filaVazia(&fila)) {
        int u = desenfileirar(&fila);
        Node* temp = grafo->listaAdj[u];

        while (temp) {
            int v = temp->vertice;

            if (cor[v] == BRANCO) {  // Existe uma aresta (u, v) e v é BRANCO
                cor[v] = CINZA;
                d[v] = d[u] + 1;
                antecessor[v] = u;
                enfileirar(&fila, v);
            }
            temp = temp->next;
        }
        cor[u] = PRETO;  // u foi completamente explorado
    }

    printf("Vertice     Distancia     Antecessor\n");
    for (int i = 0; i < NUM_VERTICES; i++) {
        printf("%d\t\t%d\t\t%d\n", i, d[i], antecessor[i]);
    }
}

void imprimeGrafo(Grafo* grafo) {
    for (int i = 0; i < NUM_VERTICES; i++) {
        Node* adj = grafo->listaAdj[i];
        printf("Vertice %d:", i);
        while (adj) {
            printf(" -> %d", adj->vertice);
            adj = adj->next;
        }
        printf("\n");
    }
}

int main() {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));

    // Inicializando o grafo
    for (int i = 0; i < NUM_VERTICES; i++) {
        grafo->listaAdj[i] = NULL;
    }

    // Adicionando as arestas ao grafo
    adicionarAresta(grafo, 0, 1);
    adicionarAresta(grafo, 0, 2);
    adicionarAresta(grafo, 1, 3);
    adicionarAresta(grafo, 1, 4);
    adicionarAresta(grafo, 2, 5);
    adicionarAresta(grafo, 2, 6);
    adicionarAresta(grafo, 3, 7);
    adicionarAresta(grafo, 4, 8);
    adicionarAresta(grafo, 5, 6);
    adicionarAresta(grafo, 6, 8);
    adicionarAresta(grafo, 7, 8);


    int vertice_inicial = 0;  // Começa a BFS a partir do vértice 0
    int antecessor[NUM_VERTICES];

    // Executa a BFS para construir a árvore de caminhos mínimos
    BFS(grafo, vertice_inicial, antecessor);

    imprimeGrafo(grafo);
    // Imprime a árvore resultante

    return 0;
}
