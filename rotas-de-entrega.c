/*
SISTEMA: Planejamento de Rotas de Entrega
DISCENTES - JEFTÉ FONTES DE ARAUJO E JOÃO VICTOR RODRIGUES TERTO
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_VERTICES 20   // Define o número máximo de vértices no grafo
#define NOT_REACHABLE 999  // Valor utilizado para representar vertices não acessíveis

// Estrutura de um nó na lista de adjacência
typedef struct No {
    int cidade;            
    struct No* proximo;    
} No;

// Estrutura que representa o grafo com listas de adjacência
typedef struct Grafo {
    No* listaAdj[MAX_VERTICES];  
} Grafo;

// Nomes das cidades
char* cidades[MAX_VERTICES] = {
    "Sao Paulo", "Rio de Janeiro", "Belo Horizonte", "Brasilia", "Salvador",
    "Fortaleza", "Recife", "Porto Alegre", "Curitiba", "Manaus",
    "Belem", "Goiania", "Campinas", "Vitoria", "Natal",
    "Maceio", "Teresina", "Joao Pessoa", "Sao Luis", "Florianopolis"
};

// Variáveis globais para armazenar dados do algoritmo
bool visitado[MAX_VERTICES] = { false };
int distancia[MAX_VERTICES];
int predecessor[MAX_VERTICES];
int caminho[MAX_VERTICES];
int maxCaminho[MAX_VERTICES];
int caminhoIndex = 0;
int maxDist = -1;
int maxCaminhoLen = 0;

// Funções do grafo
No* criarNo(int cidade);                    // Cria um novo nó
void inicializarGrafo(Grafo* g);           // Inicializa o grafo
bool arestaExiste(Grafo* g, int origem, int destino);  // Verifica se uma aresta existe
void adicionarAresta(Grafo* g, int origem, int destino); // Adiciona uma aresta ao grafo
void gerarArestasAleatorias(Grafo* g, int numArestas);   // Gera arestas aleatórias
void bfs(Grafo* g, int inicio, int distancia[], int predecessor[]); // Executa BFS
void exibirGrafo(Grafo* g);                // Exibe o grafo
void exibirMatrizD_A(int distancia[], int predecessor[]); // Exibe a tabela de distâncias e predecessores
void exibirMenorRota(int inicio, int fim, int predecessor[]); // Exibe a rota mais curta
void dfs(Grafo* g, int origem, int destino, bool visitado[], int caminho[], int caminhoIndex, int* maxDist, int* maxCaminho, int* maxCaminhoLen); // Executa DFS
void exibirRotaMaisLonga(int maxCaminho[], int maxCaminhoLen); // Exibe a rota mais longa
void exibirRotas(Grafo* g, int origem, int destino); // Exibe todas as rotas
void freeGrafo(Grafo* g); // Libera a memória alocada pelo grafo
void menu(); // Função principal do menu

int main() {
    menu(); 
    return 0;
}

No* criarNo(int cidade) {
    No* novoNo = (No*)malloc(sizeof(No)); 
    novoNo->cidade = cidade;              
    novoNo->proximo = NULL;              
    return novoNo;
}

void inicializarGrafo(Grafo* g) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->listaAdj[i] = NULL; 
    }
}

bool arestaExiste(Grafo* g, int origem, int destino) {
    No* temp = g->listaAdj[origem]; // Obtém a lista de adjacência do vértice origem
    while (temp) {
        if (temp->cidade == destino) { // Verifica se o destino está na lista
            return true;
        }
        temp = temp->proximo; // Avança para o próximo nó na lista
    }
    return false; // Retorna falso se o destino não for encontrado
}

void adicionarAresta(Grafo* g, int origem, int destino) {
    if (!arestaExiste(g, origem, destino)) { 
        No* novoNo = criarNo(destino);
        novoNo->proximo = g->listaAdj[origem];
        g->listaAdj[origem] = novoNo; 

        novoNo = criarNo(origem);
        novoNo->proximo = g->listaAdj[destino];
        g->listaAdj[destino] = novoNo; 
    }
}


void gerarArestasAleatorias(Grafo* g, int numArestas) {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    int arestas = 0;

    while (arestas < numArestas) { // Gera arestas até atingir o número desejado
        int origem = rand() % MAX_VERTICES;
        int destino = rand() % MAX_VERTICES;

        if (origem != destino && !arestaExiste(g, origem, destino)) {
            adicionarAresta(g, origem, destino);
            arestas++;
        }
    }
}

void bfs(Grafo* g, int inicio, int distancia[], int predecessor[]) {
    int fila[MAX_VERTICES];
    int frente = 0, tras = 0;
    
    for (int i = 0; i < MAX_VERTICES; i++) {
        visitado[i] = false;
        distancia[i] = NOT_REACHABLE; // Inicializa todas as distâncias como não alcançáveis
        predecessor[i] = -1; // Inicializa todos os predecessores como -1
    }

    visitado[inicio] = true; // Marca o vértice inicial como visitado
    distancia[inicio] = 0; // Define a distância do vértice inicial como 0
    fila[tras++] = inicio; // Adiciona o vértice inicial à fila

    while (frente < tras) { // Enquanto a fila não estiver vazia
        int atual = fila[frente++];
        No* temp = g->listaAdj[atual]; // Obtém a lista de adjacência do vértice atual

        while (temp) { // Percorre a lista de adjacência
            int vizinho = temp->cidade;
            if (!visitado[vizinho]) { // Se o vizinho ainda não foi visitado
                visitado[vizinho] = true; // Marca o vizinho como visitado
                distancia[vizinho] = distancia[atual] + 1; // Atualiza a distância
                predecessor[vizinho] = atual; // Define o predecessor
                fila[tras++] = vizinho; // Adiciona o vizinho à fila
            }
            temp = temp->proximo; // Avança para o próximo nó na lista
        }
    }
}

void exibirGrafo(Grafo* g) {
    printf("Grafo:\n");
    for (int i = 0; i < MAX_VERTICES; i++) {
        No* temp = g->listaAdj[i];
        printf("%d. Cidade %s:", i + 1, cidades[i]); // Exibe o vértice e o nome da cidade
        while (temp) { // Percorre a lista de adjacência
            printf(" -> %d. %s", temp->cidade + 1, cidades[temp->cidade]); // Exibe o vizinho
            temp = temp->proximo; // Avança para o próximo nó na lista
        }
        printf("\n");
    }
}

void exibirMatrizD_A(int distancia[], int predecessor[]) {
    printf("Vertice                        Distancia   Antecessor\n");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < MAX_VERTICES; i++) {
        char* predecessorNome = predecessor[i] == -1 ? "N/A" : cidades[predecessor[i]];// Uso de operador ternário para declarar se o vertice tem predecessor ou não
        printf("%-30s %10d   %s\n", cidades[i], distancia[i], predecessorNome);
    }
}

void exibirMenorRota(int inicio, int fim, int predecessor[]) {
    if (predecessor[fim] == -1) { // Se não houver caminho
        printf("Nao ha caminho de %d. %s para %d. %s\n", inicio + 1, cidades[inicio], fim + 1, cidades[fim]);
        return;
    }

    int caminho[MAX_VERTICES];
    int caminhoLen = 0;
    for (int v = fim; v != -1; v = predecessor[v]) {
        caminho[caminhoLen++] = v; // Monta o caminho a partir do destino até a origem
    }

    printf("Caminho mais curto de %d. %s para %d. %s: ", inicio + 1, cidades[inicio], fim + 1, cidades[fim]);
    for (int i = caminhoLen - 1; i >= 0; i--) {
        printf("%d. %s ", caminho[i] + 1, cidades[caminho[i]]);
        if (i != 0) {
            printf("-> ");
        }
    }
    printf("\n");
}

void dfs(Grafo* g, int origem, int destino, bool visitado[], int caminho[], int caminhoIndex, int* maxDist, int* maxCaminho, int* maxCaminhoLen) {
    visitado[origem] = true;
    caminho[caminhoIndex] = origem;
    caminhoIndex++;

    if (origem == destino) { // Se chegou ao destino
        int dist = caminhoIndex - 1;
        if (dist > *maxDist) { // Se a distância atual é maior que a máxima
            *maxDist = dist;
            *maxCaminhoLen = caminhoIndex;
            memcpy(maxCaminho, caminho, caminhoIndex * sizeof(int)); // Copia o caminho atual
        }

        for (int i = 0; i < caminhoIndex; i++) { // Exibe o caminho
            printf("%d. %s ", caminho[i] + 1, cidades[caminho[i]]);
            if (i != caminhoIndex - 1) printf("-> ");
        }
        printf("\n");

    } else {
        No* temp = g->listaAdj[origem];
        while (temp) { // Percorre a lista de adjacência
            int v = temp->cidade;
            if (!visitado[v]) {
                dfs(g, v, destino, visitado, caminho, caminhoIndex, maxDist, maxCaminho, maxCaminhoLen);
            }
            temp = temp->proximo; // Avança para o próximo nó na lista
        }
    }

    visitado[origem] = false; // Marca o vértice como não visitado para outras buscas
}

void exibirRotaMaisLonga(int maxCaminho[], int maxCaminhoLen) {
    printf("Caminho mais longo de %d. %s para %d. %s: ", maxCaminho[0] + 1, cidades[maxCaminho[0]], maxCaminho[maxCaminhoLen - 1] + 1, cidades[maxCaminho[maxCaminhoLen - 1]]);
    for (int i = 0; i < maxCaminhoLen; i++) {
        printf("%d. %s ", maxCaminho[i] + 1, cidades[maxCaminho[i]]); 
        if (i != maxCaminhoLen - 1) printf("-> ");
    }
    printf("\n");
}

void exibirRotas(Grafo* g, int origem, int destino) {
    if (origem < 0 || origem >= MAX_VERTICES || destino < 0 || destino >= MAX_VERTICES) { // Verifica se os vertices são validos
        printf("Vertice invalido!\n");
        return;
    }

    if (distancia[destino] == NOT_REACHABLE) { // Se não há caminho
        printf("Nao ha caminho de %d. %s para %d. %s\n", origem + 1, cidades[origem], destino + 1, cidades[destino]);
        return;
    } else {
        printf("Todas as rotas de %d. %s para %d. %s:\n", origem + 1, cidades[origem], destino + 1, cidades[destino]);
        bool visitado[MAX_VERTICES] = { false }; // Marca todos os vertices como não visitados
        caminhoIndex = 0; // Inicializa o indice do caminho
        maxDist = -1; // Inicializa a distância maxima como negativa
        dfs(g, origem, destino, visitado, caminho, caminhoIndex, &maxDist, maxCaminho, &maxCaminhoLen); // Executa o DFS
        printf("\n");
    }
}

// Função para liberar a memória alocada pelo grafo
void freeGrafo(Grafo* g) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        No* temp = g->listaAdj[i];
        while (temp) {
            No* paraLiberar = temp;
            temp = temp->proximo;
            free(paraLiberar); // Libera o nó atual
        }
    }
}

// Função principal do menu
void menu() {
    Grafo g;
    int inicio, fim, opcao, submenu;

    inicializarGrafo(&g); // Inicializa o grafo
    gerarArestasAleatorias(&g, 30); // Gera 30 arestas aleatórias

    while (true) {
        printf("\nMenu:\n");
        printf("1. Exibir o grafo\n");
        printf("2. Executar BFS\n");
        printf("3. Gerar novas arestas\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirGrafo(&g); // Exibe o grafo
                break;
            case 2:
                printf("Escolha a cidade inicial (1 a %d): ", MAX_VERTICES);
                scanf("%d", &inicio);
                inicio--;

                printf("Escolha a cidade final (1 a %d): ", MAX_VERTICES);
                scanf("%d", &fim);
                fim--;

                bfs(&g, inicio, distancia, predecessor); // Executa BFS
                exibirRotas(&g, inicio, fim); // Exibe todas as rotas

                bool condition = true;

                if (distancia[fim] == NOT_REACHABLE) {
                    condition = false;
                }
                while (condition){
                    printf("\nExibicao Rotas:\n");
                    printf("1. Exibir rota mais curta\n");
                    printf("2. Exibir rota mais longa\n");
                    printf("3. Exibir tabela com distancias e predecessor\n");
                    printf("4. Voltar ao menu principal\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &submenu);

                    switch (submenu) {
                        case 1:
                            exibirMenorRota(inicio, fim, predecessor); 
                            break;
                        case 2:
                            exibirRotaMaisLonga(maxCaminho, maxCaminhoLen); 
                            break;
                        case 3:
                            exibirMatrizD_A(distancia, predecessor); 
                            break;
                        case 4:
                            condition = false; 
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                    }
                }
                break;
            case 3:
                inicializarGrafo(&g); // Re-inicializa o grafo
                gerarArestasAleatorias(&g, 30); // Gera novas 30 arestas aleatórias
                printf("Arestas geradas com sucesso!\n");
                break;
            case 4:
                printf("Encerrando o programa...\n");
                freeGrafo(&g); // Libera a memória alocada
                return;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
}
