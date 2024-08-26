#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *constructBalancedTree(int *number, int start, int end) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    Node *root = createNode(number[mid]);

    root->left = constructBalancedTree(number, start, mid - 1);
    root->right = constructBalancedTree(number, mid + 1, end);

    return root;
}

void displayTree(Node *root, int nivel) {
    if (root == NULL)
        return;

    displayTree(root->right, nivel + 1);

    for (int i = 0; i < nivel - 1; i++)
        printf("   ");

    if (nivel > 0)
        printf("   |--");

    printf("%d\n", root->value);

    displayTree(root->left, nivel + 1);
}

int main() {
    int number[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int size = sizeof(number) / sizeof(number[0]);

    Node *root = constructBalancedTree(number, 0, size - 1);

    printf("Árvore Binária Balanceada:\n");
    displayTree(root, 0);

    return 0;
}
