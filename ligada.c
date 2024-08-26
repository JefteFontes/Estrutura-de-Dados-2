#include <stdio.h>
#include <stdlib.h>

//Estutura dos nós
typedef struct Node {
    int value;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;

//Funções utilizadas
Node *createNode(int value, Node *parent);
Node *constructBalancedTree(int *number, int start, int end, Node *parent);
void displayTree(Node *root, int nivel);
void displayTreeWithParent(Node *root, int level);

int main() {
    int number[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(number) / sizeof(number[0]);

    Node *root = constructBalancedTree(number, 0, size - 1, NULL);

    printf("Árvore Binária Balanceada (Ligada):\n");
    displayTree(root, 0);

    printf("\nVerificação de Nós e Pais:\n");
    displayTreeWithParent(root, 0);

    return 0;
}

//Inicializa o nó da árvore
Node *createNode(int value, Node *parent) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;
    return node;
}

//Constroi a árvore a partir do array enviado
Node *constructBalancedTree(int *number, int start, int end, Node *parent) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    Node *root = createNode(number[mid], parent);

    root->left = constructBalancedTree(number, start, mid - 1, root);
    root->right = constructBalancedTree(number, mid + 1, end, root);

    return root;
}

//Exibição da árvore
void displayTree(Node *root, int nivel) {
    if (root == NULL)
        return;

    displayTree(root->right, nivel + 1);

    for (int i = 0; i < nivel; i++)
        printf("   ");

    printf("%d\n", root->value);

    displayTree(root->left, nivel + 1);
}

//Exibição dos nós juntamente com os respectivos parents
void displayTreeWithParent(Node *root, int level) {
    if (root == NULL)
        return;

    displayTreeWithParent(root->right, level + 1);

    for (int i = 0; i < level; i++)
        printf("   ");

    if (root->parent != NULL)
        printf("%d(pai: %d)\n", root->value, root->parent->value);
    else
        printf("%d(pai: NULL)\n", root->value);

    displayTreeWithParent(root->left, level + 1);
}