#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_FILA (20 * 2)

typedef struct No {
    int cidade;
    struct No* proximo;
} No;

typedef struct Grafo {
    No* lista_adj[20];
    bool visitado[20];
    int distancia[20];
    int predecessor[20]; // Vetor para armazenar o predecessor de cada cidade
    char* cidade[20];
} Grafo;

No* criar_no(int cidade) {
    No* no_Cidade = (No*)malloc(sizeof(No));
    no_Cidade->cidade = cidade;
    no_Cidade->proximo = NULL;
    return no_Cidade;
}

void inicializar_no(Grafo* gra, int num, char* cidades[]) {
    for (int i = 0; i < num; i++) {
        gra->lista_adj[i] = NULL;
        gra->visitado[i] = false;
        gra->distancia[i] = 99999;
        gra->predecessor[i] = -1;
        gra->cidade[i] = cidades[i];
    }
}

bool caminho_grafo(Grafo* g, int origem, int destino) { // procura a cidade na lista de adjacência
    No* temp = g->lista_adj[origem];
    while (temp) {
        if (temp->cidade == destino) {
            return true;
        }
        temp = temp->proximo;
    }
    return false;
}

void criar_caminho(Grafo* g, int origem, int destino) { // cria a aresta entre cidades adjacentes
    if (!caminho_grafo(g, origem, destino)) {
        No* No_cidade = criar_no(destino);
        No_cidade->proximo = g->lista_adj[origem];
        g->lista_adj[origem] = No_cidade;

        No_cidade = criar_no(origem);
        No_cidade->proximo = g->lista_adj[destino];
        g->lista_adj[destino] = No_cidade;
    }
}

void aresta_aleatoria(Grafo* g, int num, int numArestas) {  // gera indices aleatório para cada aresta
    srand(time(NULL));
    int arestas = 0;
    int maxAresta = num * (num - 1) / 2;

    if (numArestas > maxAresta) {
        numArestas = maxAresta;
    }

    while (arestas < numArestas) {
        int u = rand() % num;
        int v = rand() % num;

        if (u != v && !caminho_grafo(g, u, v)) {
            criar_caminho(g, u, v);
            arestas++;
        }
    }
}

void bfs(Grafo* g, int comeco, int numCidades) { // Demarca quem foi visitado 
    int fila[20];
    int frente = 0, final = 0;

    for (int i = 0; i < numCidades; i++) {
        g->visitado[i] = false;
        g->distancia[i] = 99999;
        g->predecessor[i] = -1;
    }

    g->visitado[comeco] = true;
    g->distancia[comeco] = 0;
    fila[final++] = comeco;

    while (frente < final) {
        int atual = fila[frente++];
        No* temp = g->lista_adj[atual];

        while (temp) {
            int vizinho = temp->cidade;
            if (!g->visitado[vizinho]) {
                g->visitado[vizinho] = true;
                g->distancia[vizinho] = g->distancia[atual] + 1;
                g->predecessor[vizinho] = atual;
                if (final < 20) {
                    fila[final++] = vizinho;
                }
            }
            temp = temp->proximo;
        }
    }
}

bool eh_conectado(Grafo* g, int num) { // verifica se um grafo é conectado
    for (int i = 0; i < num; i++) {
        if (g->distancia[i] == 99999) {
            return false;
        }
    }
    return true;
}

void printGrafo(Grafo* g, int num) {
    printf("Grafo:\n");
    for (int i = 0; i < num; i++) {
        No* temp = g->lista_adj[i];
        printf("Cidade %s:", g->cidade[i]);
        while (temp) {
            printf(" -> %s", g->cidade[temp->cidade]);
            temp = temp->proximo;
        }
        printf("\n");
    }
}

void printDistanciaMatrix(Grafo* g, int numCidades) {
    printf("Matriz de Distâncias:\n");
    for (int i = 0; i < numCidades; i++) {
        printf("Cidade %s: %d\n", g->cidade[i], g->distancia[i]);
    }
}

void printPredecessorMatrix(Grafo* g, int numCidades) {
    printf("Matriz de Predecessores:\n");
    for (int i = 0; i < numCidades; i++) {
        printf("Cidade %s: %s\n", g->cidade[i], g->predecessor[i] == -1 ? "N/A" : g->cidade[g->predecessor[i]]);
    }
}

void print_caminho(Grafo* g, int comeco, int fim) { // Imprime o caminho entre grafos
    if (g->distancia[fim] == 99999) {
        printf("Não há caminho de %s para %s\n", g->cidade[comeco], g->cidade[fim]);
        return;
    }

    int caminho[20];
    int tamanho_caminho = 0;
    for (int v = fim; v != -1; v = g->predecessor[v]) {
        caminho[tamanho_caminho++] = v;
    }

    printf("Caminho mais curto de %s para %s: ", g->cidade[comeco], g->cidade[fim]);
    for (int i = tamanho_caminho - 1; i >= 0; i--) {
        printf("%s > ", g->cidade[caminho[i]]);
    }
    printf("\n");
}

void dfs_todas_rotas(Grafo* g, int origem, int destino, bool visitado[], int caminho[], int indice) { // Busca todas as rotas
    visitado[origem] = true;
    caminho[indice] = origem;
    indice++;

    if (origem == destino) {
        for (int i = 0; i < indice; i++) {
            printf("%s ", g->cidade[caminho[i]]);
            if (i != indice - 1) printf("-> ");
        }
        printf("\n");
    } else {
        No* temp = g->lista_adj[origem];
        while (temp) {
            int v = temp->cidade;
            if (!visitado[v]) {
                dfs_todas_rotas(g, v, destino, visitado, caminho, indice);
            }
            temp = temp->proximo;
        }
    }

    visitado[origem] = false;
}

void print_todas_rotas(Grafo* g, int origem, int destino, int numCidades) {
    bool visitado[20] = { false };
    int caminho[20];
    int indice = 0;

    printf("Todas as rotas de %s para %s:\n", g->cidade[origem], g->cidade[destino]);
    dfs_todas_rotas(g, origem, destino, visitado, caminho, indice);
}

void menu() {
    Grafo g;
    int numCidades = 20;
    int numArestas = 30;
    int comeco, fim, opcao;

   char* nomesCidades[20] = {
        "Cidade 1 - Sao Luis", "Cidade 2 - Imperatriz", "Cidade 3 - Caxias", "Cidade 4 - Timon", "Cidade 5 - Bacabal",
        "Cidade 6 - Barra do Corda", "Cidade 7 - Balsas", "Cidade 8 - Chapadinha", "Cidade 9 - Codo", "Cidade 10 - Sao Jose de Ribamar",
        "Cidade 11 - Paço do Lumiar", "Cidade 12 - Araioses", "Cidade 13 - Alto Alegre do Maranhao", "Cidade 14 - Viana", "Cidade 15 - Acailandia",
        "Cidade 16 - Santa Ines", "Cidade 17 - Buriticupu", "Cidade 18 - Pinheiro", "Cidade 19 - Buritama", "Cidade 20 - Pedreiras"
    };



    inicializar_no(&g, numCidades, nomesCidades);
    aresta_aleatoria(&g, numCidades, numArestas);

    while (true) {
        printf("\nMenu:\n");
        printf("1. Imprimir o estado inicial do grafo\n");
        printf("2. Executar BFS e mostrar o caminho mais curto\n");
        printf("3. Exibir a matriz de distancias e a matriz de predecessores\n");
        printf("4. Exibir todas as rotas possiveis entre duas cidades\n");
        printf("5. Gerar um novo conjunto de arestas aleatorias\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nEstado inicial do grafo:\n");
                printGrafo(&g, numCidades);
                break;
            case 2:
                printf("Digite a cidade de origem (0-%d): ", numCidades-1);
                scanf("%d", &comeco);
                printf("Digite a cidade de destino (0-%d): ", numCidades-1);
                scanf("%d", &fim);
                bfs(&g, comeco, numCidades);
                printf("\nResultado da BFS:\n");
                print_caminho(&g, comeco, fim);
                break;
            case 3:
                printf("\nMatriz de Distancias e Matriz de Predecessores:\n");
                printDistanciaMatrix(&g, numCidades);
                printPredecessorMatrix(&g, numCidades);
                break;
            case 4:
                printf("Digite a cidade de origem (0-%d): ", numCidades-1);
                scanf("%d", &comeco);
                printf("Digite a cidade de destino (0-%d): ", numCidades-1);
                scanf("%d", &fim);
                print_todas_rotas(&g, comeco, fim, numCidades);
                break;
            case 5:
                printf("Digite o novo numero de arestas: ");
                scanf("%d", &numArestas);
                aresta_aleatoria(&g, numCidades, numArestas);
                break;
            case 6:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opção invalida! Tente novamente.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
