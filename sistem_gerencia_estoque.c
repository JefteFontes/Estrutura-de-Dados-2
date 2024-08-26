/*
SISTEMA DE GERENCIAMENTO DE ESTOQUE COM ARVORE
DISCENTES - JEFTÉ FONTES DE ARAUJO E JOÃO VICTOR RODRIGUES TERTO
*/

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

//Struct para o no
typedef struct Node {
    int codigo;
    char nome[100];
    int quantidade;
    float preco;
    struct Node *left;
    struct Node *right;
} Node;

//Variaveis globais
Node* root = NULL;
int option;
int cod;
int quantity;
float minPrice;
float maxPrice;
bool notFound;

// Função para criar um novo nó
Node* createNode(int codigo);
// Função para obter o número de elementos na árvore
int treeSize(Node* root);
// Função para inserir os elementos existentes na árvore em um array
void insertToArray(Node* root, Node** arr, int *index);
// Função para construir uma nova árvore balanceada a partir de um array
Node* buildBalancedTreeFromArray(Node** arr, int start, int end);
// Funções para inserir elementos em uma árvore
Node* insertNode(Node* root, int codigo);
// Funções para excluir elementos de uma árvore
Node* minValueNode(Node* node);
Node* deleteNode(Node* root, int codigo);
// Funções para pesquisar elementos de uma árvore
Node* searchNode(Node* root, int codigo);
// Função para selecionar elementos com quantidade abaixo de uma quantidade informada pelo usuário
void listProductsBelowQuantity(Node* root, int quantity);
// Função para pesquisar elementos dentro de uma faixa de precos informada pelo usuário
void listProductsInRange(Node* root, float minPrice, float maxPrice);
// Função para calcular o valor total do estoque da árvore
float calculateTotalValue(Node* root);
// Função para gerar uma árvore aleatória
Node* generateRandomTree();
// Função para liberar a árvore
void freeTree(Node* root);
// Função para imprimir a árvore
void printTree(Node* root, int space);
// Função para imprimir os elementos da árvore
void printElements(Node* root);
// Funções para ordenar o array de nós
int compareNodes(const void *a, const void *b);
void sortNodesArray(Node** arr, int size);
//Menu principal do programa
void menuDisplay();


int main() {

    menuDisplay();
    return 0;
}

void menuDisplay() {
    while(1) {
        printf("\n      GERENCIADOR DE ESTOQUE       \n");
        printf("-------------------------------------\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Exibir produtos\n");
        printf("3 - Procurar produto\n");
        printf("4 - Excluir produto\n");
        printf("5 - Calcular valor total\n");
        printf("6 - Listar por quantia\n");
        printf("7 - Listar por faixa de preco\n");
        printf("8 - Gerar arvore aleatoria\n");
        printf("0 - Sair\n");
        printf("-------------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Digite o codigo do novo produto: ");
            scanf("%d", &cod);
            if (cod <= 0){
                printf("Codigo invalido. Tente novamente.\n");
            } else {
                root = insertNode(root, cod);
                printf("Inserido com sucesso!\n");
            }
            break;
        case 2:
            if (root == NULL) {
                printf("Nenhum produto cadastrado.\n");
                break;
            }
            printTree(root, 0);
            printf("\n--------------------------------------\n");
            printElements(root);
            break;
        case 3:
            if (root == NULL) {
                printf("Nenhum produto cadastrado.\n");
                break;
            }
            printf("Digite o codigo do produto que deseja procurar: ");
            scanf("%d", &cod);
            Node* foundNode = searchNode(root, cod);
            if (foundNode == NULL) {
                printf("Produto nao encontrado.\n");
                break;
            }
            printf("\n\nProduto encontrado:\n");
            printf("Codigo: %d \nNome: %s \nQuantidade: %d \nPreco: R$ %.2f\n\n", foundNode->codigo, foundNode->nome, foundNode->quantidade, foundNode->preco);
            break;
        case 4:
            if (root == NULL) {
                printf("Nenhum produto cadastrado.\n");
                break;
            }
            printf("Digite o codigo do produto que deseja excluir: ");
            scanf("%d", &cod);
            root = deleteNode(root, cod);
            printf("Excluido com sucesso!\n");
            break;
        case 5:
            if(root != NULL){
                printf("Total dos valores em estoque: R$ %.2f\n", calculateTotalValue(root));
            } else {
                printf("Nenhum item foi inserido.\n");
            }
            break;
        case 6:
            if (root == NULL) {
                printf("Nenhum produto cadastrado.\n");
                break;
            }
            printf("Digite a quantidade maxima desejada: ");
            scanf("%d", &quantity);
            printf("Produtos com quantidade abaixo de %d:\n", quantity);
            notFound = true;
            listProductsBelowQuantity(root, quantity);
            if (notFound) {
                printf("Nenhum produto encontrado com quantidade abaixo de %d.\n", quantity);
                break;
            }
            break;
        case 7:
            if (root == NULL) {
                printf("Nenhum produto cadastrado.\n");
                break;
            }
            printf("Digite o preco minimo: ");
            scanf("%f", &minPrice);
            printf("Digite o preco maximo: ");
            scanf("%f", &maxPrice);
            printf("Produtos na faixa de preco R$ %.2f - R$ %.2f:\n", minPrice, maxPrice);
            notFound = true;
            listProductsInRange(root, minPrice, maxPrice);
            if (notFound) {
                printf("Nenhum produto presente na faixa de precos R$ %.2f - R$ %.2f.\n", minPrice, maxPrice);
                break;
            }
            break;
        case 8:
            root = generateRandomTree();
            printTree(root, 0);
            printf("\n--------------------------------------\n");
            printElements(root);
            break;
        case 0:
            freeTree(root);
            return;
            break;
        default:
            break;
        }
    }
}

Node* createNode(int codigo) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->codigo = codigo;
    printf("Nome do produto: ");
    scanf("%s", newNode->nome);
    printf("Quantidade: ");
    scanf("%d", &newNode->quantidade);
    printf("Preco: ");
    scanf("%f", &newNode->preco);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int treeSize(Node* root) {
    if (root == NULL) {
        return 0;
    }

    return treeSize(root->left) + treeSize(root->right) + 1;
}

void insertToArray(Node* root, Node** arr, int *index) {
    if (root == NULL) {
        return;
    }   

    insertToArray(root->left, arr, index);
    arr[(*index)++] = root;
    insertToArray(root->right, arr, index);
}

Node* buildBalancedTreeFromArray(Node** arr, int start, int end) {
    if (start > end) {
        return NULL;
    }

    int mid = (start + end) / 2;
    Node* root = arr[mid];

    root->left = buildBalancedTreeFromArray(arr, start, mid - 1);
    root->right = buildBalancedTreeFromArray(arr, mid + 1, end);

    return root;
}

Node* insertNode(Node* root, int codigo) {
    if (root == NULL) {
        Node *newProd = createNode(codigo);
        if (newProd->quantidade < 0 || newProd->preco < 0)
        {
            printf("Valores invalidos encontrados! Nao e possivel inserir.\n");
            return root;
        }
        return newProd;
    }

    if (codigo < root->codigo) {
        root->left = insertNode(root->left, codigo);
    } else if (codigo > root->codigo) {
        root->right = insertNode(root->right, codigo);
    } else {
        printf("Codigo de produto duplicado! Nao e possivel inserir.\n");
        return root;
    }

    // Pegando todos os elementos da árvore e inserindo em um array
    int size = treeSize(root);
    Node** arr = (Node**)malloc(size * sizeof(Node*));
    int index = 0;
    insertToArray(root, arr, &index);

    // Reconstruindo a árvore a partir do array para balanceá-la
    root = buildBalancedTreeFromArray(arr, 0, size - 1);

    // Liberando memória alocada para o array
    free(arr);

    return root;
}

Node* minValueNode(Node* node) {
    Node* current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

Node* deleteNode(Node* root, int codigo) {
    if (root == NULL) {
        return root;
    }

    if (codigo < root->codigo) {
        root->left = deleteNode(root->left, codigo);
    } else if (codigo > root->codigo) {
        root->right = deleteNode(root->right, codigo);
    } else {
        // Nó com apenas um filho ou nenhum filho
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Nó com dois filhos, obtemos o sucessor (o menor nó na subárvore direita)
        Node* temp = minValueNode(root->right);

        // Copia os dados do sucessor para este nó
        root->codigo = temp->codigo;
        strcpy(root->nome, temp->nome);
        root->quantidade = temp->quantidade;
        root->preco = temp->preco;

        // Removendo o sucessor
        root->right = deleteNode(root->right, temp->codigo);
    }

    return root;
}

Node* searchNode(Node* root, int codigo) {
    if (root == NULL || root->codigo == codigo) {
        return root;
    }

    if (root->codigo < codigo) {
        return searchNode(root->right, codigo);
    }

    return searchNode(root->left, codigo);
}

void listProductsBelowQuantity(Node* root, int quantity) {
    if (root == NULL) {
        return;
    }

    listProductsBelowQuantity(root->left, quantity);

    if (root->quantidade < quantity) {
        printf("Codigo: %d \nNome: %s \nQuantidade: %d \nPreco: R$ %.2f\n\n", root->codigo, root->nome, root->quantidade, root->preco);
        notFound = false;
    } 

    listProductsBelowQuantity(root->right, quantity);
}

void listProductsInRange(Node* root, float minPrice, float maxPrice) {
    if (root == NULL) {
        return;
    }

    listProductsInRange(root->left, minPrice, maxPrice);

    if (root->preco >= minPrice && root->preco <= maxPrice) {
        printf("Código: %d \nNome: %s \nQuantidade: %d \nPreço: R$ %.2f\n\n", root->codigo, root->nome, root->quantidade, root->preco);
        notFound = false;
    }

    listProductsInRange(root->right, minPrice, maxPrice);
}

float calculateTotalValue(Node* root) {
    if (root == NULL) {
        return 0;
    }

    return (root->quantidade * root->preco) + calculateTotalValue(root->left) + calculateTotalValue(root->right);
}

int compareNodes(const void *a, const void *b) {
    Node *nodeA = *(Node **)a;
    Node *nodeB = *(Node **)b;
    return (nodeA->codigo - nodeB->codigo);
}

void sortNodesArray(Node** arr, int size) {
    qsort(arr, size, sizeof(Node*), compareNodes);
}

Node* generateRandomTree() {
    const int numNodes = 7;
    const int maxQuantity = 100;
    const float maxPrice = 100.0;
    Node** arr = (Node**)malloc(7 * sizeof(Node*));

    // Cria uma árvore vazia

    // Semente para a função de números aleatórios
    srand(time(NULL));

    // Gerar e inserir 7 elementos aleatórios na árvore
    for (int i = 0; i < numNodes; ++i) {
        Node* root = (Node*)malloc(sizeof(Node));
        root->left = NULL;
        root->right = NULL;
        root->codigo = rand() % 1000 + 1; // Código aleatório entre 1 e 1000
        sprintf(root->nome, "Produto %d", root->codigo); // Nome baseado no código
        root->quantidade = rand() % maxQuantity + 1; // Quantidade aleatória entre 1 e maxQuantity
        root->preco = (float)(rand() % (int)(maxPrice * 100)) / 100.0; // Preço aleatório entre 0 e maxPrice

        arr[i] = root;
    }

    sortNodesArray(arr, numNodes);

    root = buildBalancedTreeFromArray(arr, 0, numNodes - 1);
    free(arr);

    return root;
}

void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void printTree(Node* root, int space) {
    if (root == NULL) {
        return;
    }

    space += 5;

    printTree(root->right, space);
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d - %s\n", root->codigo, root->nome);
    printTree(root->left, space);
}

void printElements(Node *root) {
    if (root == NULL) {
        return;
    }

    printf("Codigo: %d \nNome: %s \nQuantidade: %d \nPreco: R$ %.2f\n\n", root->codigo, root->nome, root->quantidade, root->preco);
    printElements(root->left);
    printElements(root->right);
}