#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da árvore Red-Black
typedef struct Node {
    int data;
    char color[6]; // "RED" ou "BLACK"
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

// Declaração da árvore Red-Black
Node* root;
Node* NIL; // Nó NIL (nó folha vazio)

// Função para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    strcpy(newNode->color, "RED");
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->parent = NULL;
    return newNode;
}

// Função para fazer rotação à esquerda
void leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// Função para fazer rotação à direita
void rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NIL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

// Função para corrigir as propriedades da árvore após inserção
void fixInsert(Node* k) {
    while (k != root && strcmp(k->parent->color, "RED") == 0) {
        if (k->parent == k->parent->parent->left) {
            Node* u = k->parent->parent->right; // Tio
            if (strcmp(u->color, "RED") == 0) {
                strcpy(k->parent->color, "BLACK");
                strcpy(u->color, "BLACK");
                strcpy(k->parent->parent->color, "RED");
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                strcpy(k->parent->color, "BLACK");
                strcpy(k->parent->parent->color, "RED");
                rightRotate(k->parent->parent);
            }
        } else {
            Node* u = k->parent->parent->left; // Tio
            if (strcmp(u->color, "RED") == 0) {
                strcpy(k->parent->color, "BLACK");
                strcpy(u->color, "BLACK");
                strcpy(k->parent->parent->color, "RED");
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                strcpy(k->parent->color, "BLACK");
                strcpy(k->parent->parent->color, "RED");
                leftRotate(k->parent->parent);
            }
        }
    }
    strcpy(root->color, "BLACK");
}

// Função de inserção
void insert(int data) {
    Node* newNode = createNode(data);
    Node* parent = NULL;
    Node* current = root;

    // Inserção estilo BST
    while (current != NIL) {
        parent = current;
        if (newNode->data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent;

    if (parent == NULL) {
        root = newNode;
    } else if (newNode->data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    if (newNode->parent == NULL) {
        strcpy(newNode->color, "BLACK");
        return;
    }

    if (newNode->parent->parent == NULL) {
        return;
    }

    fixInsert(newNode);
}

// Função para substituir um nó por outro
void transplant(Node* u, Node* v) {
    if (u->parent == NULL) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// Função auxiliar para encontrar o mínimo da subárvore
Node* treeMinimum(Node* node) {
    while (node->left != NIL) {
        node = node->left;
    }
    return node;
}

// Função para corrigir a árvore após exclusão
void fixDelete(Node* x) {
    Node* s;
    while (x != root && strcmp(x->color, "BLACK") == 0) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (strcmp(s->color, "RED") == 0) {
                strcpy(s->color, "BLACK");
                strcpy(x->parent->color, "RED");
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (strcmp(s->left->color, "BLACK") == 0 && strcmp(s->right->color, "BLACK") == 0) {
                strcpy(s->color, "RED");
                x = x->parent;
            } else {
                if (strcmp(s->right->color, "BLACK") == 0) {
                    strcpy(s->left->color, "BLACK");
                    strcpy(s->color, "RED");
                    rightRotate(s);
                    s = x->parent->right;
                }

                strcpy(s->color, x->parent->color);
                strcpy(x->parent->color, "BLACK");
                strcpy(s->right->color, "BLACK");
                leftRotate(x->parent);
                x = root;
            }
        } else {
            s = x->parent->left;
            if (strcmp(s->color, "RED") == 0) {
                strcpy(s->color, "BLACK");
                strcpy(x->parent->color, "RED");
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (strcmp(s->left->color, "BLACK") == 0 && strcmp(s->right->color, "BLACK") == 0) {
                strcpy(s->color, "RED");
                x = x->parent;
            } else {
                if (strcmp(s->left->color, "BLACK") == 0) {
                    strcpy(s->right->color, "BLACK");
                    strcpy(s->color, "RED");
                    leftRotate(s);
                    s = x->parent->left;
                }

                strcpy(s->color, x->parent->color);
                strcpy(x->parent->color, "BLACK");
                strcpy(s->left->color, "BLACK");
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    strcpy(x->color, "BLACK");
}

// Função para excluir um nó
void deleteNode(Node* z) {
    Node* y = z;
    Node* x;
    char yOriginalColor[6];
    strcpy(yOriginalColor, y->color);

    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = treeMinimum(z->right);
        strcpy(yOriginalColor, y->color);
        x = y->right;

        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        strcpy(y->color, z->color);
    }

    if (strcmp(yOriginalColor, "BLACK") == 0) {
        fixDelete(x);
    }
}

// Função para deletar pelo valor
void deleteValue(int data) {
    Node* z = root;
    while (z != NIL && z->data != data) {
        if (data < z->data) {
            z = z->left;
        } else {
            z = z->right;
        }
    }

    if (z == NIL) {
        printf("Valor nao encontrado.\n");
        return;
    }

    deleteNode(z);
}

// Função para buscar um nó pelo valor
Node* search(int data) {
    Node* current = root;
    while (current != NIL && current->data != data) {
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current;
}

// Função para inicializar a árvore Red-Black
void initialize() {
    NIL = (Node*)malloc(sizeof(Node));
    NIL->data = 0;
    strcpy(NIL->color, "BLACK");
    NIL->left = NULL;
    NIL->right = NULL;
    NIL->parent = NULL;
    root = NIL;
}

// Função para imprimir a árvore in-order
void inorder(Node* node) {
    if (node != NIL) {
        inorder(node->left);
        printf("%d (%s) ", node->data, node->color);
        inorder(node->right);
    }
}

// Menu principal
void menu() {
    int option, value;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir valor\n");
        printf("2. Buscar valor\n");
        printf("3. Excluir valor\n");
        printf("4. Mostrar árvore in-order\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &value);
                insert(value);
                break;

            case 2:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &value);
                Node* found = search(value);
                if (found != NIL) {
                    printf("Valor encontrado: %d (%s)\n", found->data, found->color);
                } else {
                    printf("Valor nao encontrado.\n");
                }
                break;

            case 3:
                printf("Digite o valor a ser excluido: ");
                scanf("%d", &value);
                deleteValue(value);
                break;

            case 4:
                printf("Árvore in-order: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (option != 5);
}

// Função principal
int main() {
    initialize();
    menu();
    return 0;
}
