#include <stdio.h>
#include <stdlib.h>

// Enum para as cores dos nós
typedef enum { RED, BLACK } Color;

// Estrutura do nó da árvore Red-Black
typedef struct Node {
    int data;
    Color color; // Usando o enum para representar a cor
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

// Declaração da árvore Red-Black
Node* root;
Node* NIL; // Nó NIL (nó folha vazio)

// Função para inicializar a árvore Red-Black
void initialize() {
    NIL = (Node*)malloc(sizeof(Node));
    NIL->data = 0;
    NIL->color = BLACK;
    NIL->left = NULL;
    NIL->right = NULL;
    NIL->parent = NULL;
    root = NIL;
}

// Função para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;
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
    while (k != root && k->parent->color == RED) {
        if (k->parent == k->parent->parent->left) {
            Node* u = k->parent->parent->right; // Tio
            if (u->color == RED) {
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        } else {
            Node* u = k->parent->parent->left; // Tio
            if (u->color == RED) {
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        }
    }
    root->color = BLACK;
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
        newNode->color = BLACK;
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

// Função auxiliar para encontrar o menor valor mais próximo da raiz da árvore
Node* treeMinimum(Node* node) { 
    while (node->right != NIL) {
        node = node->right;
    }
    return node;
}

// Função para corrigir a árvore após exclusão
void fixDelete(Node* x) {
    Node* s;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->right->color == BLACK) {
                    s->left->color = BLACK;
                    s->color = RED;
                    rightRotate(s);
                    s = x->parent->right;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            s = x->parent->left;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->left->color == BLACK) {
                    s->right->color = BLACK;
                    s->color = RED;
                    leftRotate(s);
                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

// Função para excluir um nó
void deleteNode(Node* z) {
    Node* y = z;
    Node* x;
    Color yOriginalColor = y->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = treeMinimum(z->left); // Encontrar o predecessor
        yOriginalColor = y->color;
        x = y->left;

        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->left);
            y->left = z->left;
            y->left->parent = y;
        }

        transplant(z, y);
        y->right = z->right;
        y->right->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK) {
        fixDelete(x);
    }
}

// Função para deletar pelo valor
void deleteValue(int data) {
    Node* z = root;
    while (z != NIL) {
        if (data == z->data) {
            deleteNode(z); // Chama a função de exclusão
            break; // Interrompe após encontrar o nó
        } else if (data < z->data) {
            z = z->left;
        } else {
            z = z->right;
        }
    }

    if (z == NIL) {
        printf("Valor nao encontrado.\n");
    }
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

// Função para imprimir a cor do nó
const char* getColor(Color color) {
    return (color == RED) ? "RED" : "BLACK";
}

// Função para imprimir a árvore in-order
void inorder(Node* node) {
    if (node != NIL) {
        inorder(node->left);
        printf("%d (%s) ", node->data, getColor(node->color));
        inorder(node->right);
    }
}

// Função para imprimir a árvore em formato visual
void printTree(Node* root, int space, int height) {
    if (root == NIL) return;

    space += height;

    printTree(root->right, space, height);

    printf("\n");
    for (int i = height; i < space; i++)
        printf(" ");
    printf("%d(%s)\n", root->data, getColor(root->color));

    printTree(root->left, space, height);
}

void visualTree() {
    printf("\nArvore RB Visual:\n");
    printTree(root, 0, 10);
}


// Função para o menu principal
void menu() {
    int option, value;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir valor\n");
        printf("2. Buscar valor\n");
        printf("3. Excluir valor\n");
        printf("4. Mostrar arvore in-order\n");
        printf("5. Visualizar arvore\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &value);
                // Aqui você precisa implementar a função insert()
                insert(value);
                break;

            case 2:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &value);
                Node* found = search(value); // Implementar a função search()
                if (found != NIL) {
                    printf("Valor encontrado: %d (%s)\n", found->data, getColor(found->color));
                } else {
                    printf("Valor nao encontrado.\n");
                }
                break;

            case 3:
                printf("Digite o valor a ser excluido: ");
                scanf("%d", &value);
                // Implementar a função deleteValue()
                deleteValue(value);
                break;

            case 4:
                printf("Arvore in-order: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                visualTree();
                break;

            case 6:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (option != 6);
}
// Função principal
int main() {
    initialize();
    menu();
    return 0;
}
