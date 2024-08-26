#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;

// Protótipos das funções
Node *createNode(int value, Node *parent);
void displayTree(Node *root, int nivel);
void displayTreeParent(Node *root, int level);
void insertNode(Node **root, int value, Node *parent);
Node *deleteNode(Node *root, int value);
Node *minValueNode(Node *node);
int menuDisplay();

Node *root = NULL;

int main() {
    menuDisplay();
    return 0;
}

int menuDisplay(){
    while (1) {
        int option;
        int value;

        printf("Insira o numero da acao desejada (1 - Inserir, 2 - Deletar, 3 - Exibir, 4 - Sair): ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            do {
                printf("Digite o numero a ser inserido: ");
                scanf("%d", &value);
                if (value > 0)
                    insertNode(&root, value, NULL);
            } while (value > 0);
            break;
        case 2: 
            printf("Digite o numero a ser deletado: ");
            scanf("%d", &value);
            root = deleteNode(root, value);
            break;
        case 3:
            displayTreeParent(root, 0);
            printf("\n");
            displayTree(root, 0);
            break;
        case 4:
            printf("Programa encerrado\n");
            free(root);
            return 0;
        default:
            printf("Opcao invalida\n");
            break;
        }
    }
}

Node *createNode(int value, Node *parent) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void displayTree(Node *root, int nivel) {
    if (root == NULL) return;

    displayTree(root->right, nivel + 1);
    for (int i = 0; i < nivel; i++) printf("   ");
    printf("%d\n", root->value);
    displayTree(root->left, nivel + 1);
}

void displayTreeParent(Node *root, int level) {
    if (root == NULL) return;

    displayTreeParent(root->right, level + 1);
    for (int i = 0; i < level; i++) printf("   ");
    if (root->parent != NULL) printf("%d(pai: %d)\n", root->value, root->parent->value);
    else printf("%d(pai: NULL)\n", root->value);
    displayTreeParent(root->left, level + 1);
}

void insertNode(Node **root, int value, Node *parent) {
    if (*root == NULL) {
        *root = createNode(value, parent);
    } else if (value < (*root)->value) {
        insertNode(&(*root)->left, value, *root);
    } else if (value > (*root)->value) {
        insertNode(&(*root)->right, value, *root);
    }
}

Node *deleteNode(Node *root, int value) {
    if (root == NULL) return root;

    if (value < root->value) root->left = deleteNode(root->left, value);
    else if (value > root->value) root->right = deleteNode(root->right, value);
    else {
        if (root->left == NULL || root->right == NULL) {    
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL) { // Caso não tenha filhos
                if (root->parent != NULL) {
                    if (root == root->parent->left)
                        root->parent->left = NULL;
                    else
                        root->parent->right = NULL;
                }   
                free(root);
                root = NULL;
            } else { // Caso tenha apenas um filho
                temp->parent = root->parent;
                if (root->parent != NULL) {
                    if (root == root->parent->left)
                        root->parent->left = temp;
                    else
                        root->parent->right = temp;
                }
                free(root);
                root = temp;
            }
        } else { // Caso tenha dois filhos
            Node *temp = minValueNode(root->right);

            root->value = temp->value;
            root->right = deleteNode(root->right, temp->value);
        }
    }

    return root;
}

Node *minValueNode(Node *node) {
    Node *current = node;
    while (current && current->left != NULL) current = current->left;
    return current;
}
