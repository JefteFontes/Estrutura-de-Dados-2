#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct Grafo {
    int num_vertices;
    Node** vertices;
} Grafo;

Grafo* createGrafo(int num_vertices) {
    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));
    grafo->num_vertices = num_vertices;
    grafo->vertices = (Node**) malloc(num_vertices * sizeof(Node*));
    for (int i = 0; i < num_vertices; i++) {
        grafo->vertices[i] = NULL;
    }
    return grafo;
}

void insertNode(Grafo* grafo, int origem, int destino) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = destino;
    newNode->next = grafo->vertices[origem];
    grafo->vertices[origem] = newNode;
    
}

void printMatrizAdjacencia(Grafo* grafo) {
    printf("Matriz de Adjacência:\n");
    for (int i = 0; i < grafo->num_vertices; i++) {
        for (int j = 0; j < grafo->num_vertices; j++) {
            Node* current = grafo->vertices[i];
            int interacao = 0;
            while (current != NULL) {
                if (current->value == j) { 
                    interacao = 1;
                    break;
                }
                current = current->next;
            }
            printf("%d ", interacao);
        }
        printf("\n");
    }
}

void freeGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->num_vertices; i++) {
        Node* current = grafo->vertices[i];
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(grafo->vertices);
    free(grafo);
}

int main() {
    Grafo* grafo = createGrafo(5);

    insertNode(grafo, 0, 4);
    insertNode(grafo, 0, 1);
    insertNode(grafo, 1, 4);
    insertNode(grafo, 1, 0);
    insertNode(grafo, 1, 2);
    insertNode(grafo, 1, 3);
    insertNode(grafo, 2, 1);
    insertNode(grafo, 2, 3);
    insertNode(grafo, 3, 1);
    insertNode(grafo, 3, 4);
    insertNode(grafo, 3, 2);
    insertNode(grafo, 4, 3);
    insertNode(grafo, 4, 0);
    insertNode(grafo, 4, 1);

    printMatrizAdjacencia(grafo);

    freeGrafo(grafo);

    return 0;
}
