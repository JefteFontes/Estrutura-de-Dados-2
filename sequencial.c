#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;

Node *binarytree[7];

Node *createNode(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *constructBalancedTree(int *number, int start, int end, int next_index, Node *parent) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    Node *root = createNode(number[mid]);

    root->parent = parent;
    binarytree[next_index] = root;

    root->left = constructBalancedTree(number, start, mid - 1, (next_index * 2) + 1, root);
    root->right = constructBalancedTree(number, mid + 1, end, (next_index * 2) + 2, root);

    return root;
}

void displayTree(Node *root, int nivel) {
    if (root == NULL)
        return;

    displayTree(root->right, nivel + 1);

    for (int i = 0; i < nivel; i++)
        printf("   ");

    printf("%d\n", root->value);

    displayTree(root->left, nivel + 1);
}

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

int main() {
    int number[7] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(number) / sizeof(number[0]);

    constructBalancedTree(number, 0, size - 1, 0, NULL);

    printf("Arvore Binaria Balanceada (Ligada):\n");
    displayTree(binarytree[0], 0);

    for(int i = 0; i < 15; i++) {
        printf("%d: %d\n", i, binarytree[i]->value);
    }

    printf("\nVerificação de Nós e Pais:\n");
    displayTreeWithParent(binarytree[0], 0);
    return 0;
}
