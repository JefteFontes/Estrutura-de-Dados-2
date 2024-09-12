#include <stdio.h>
#include <stdlib.h>

// Definições de cores para os nós
#define RED 0
#define BLACK 1

// Estrutura de um nó da árvore Red-Black
typedef struct RBNode {
    int start;              // Início do extent (bloco inicial)
    int end;                // Fim do extent (bloco final)
    int color;              // Cor do nó (RED ou BLACK)
    struct RBNode *left;    // Filho esquerdo
    struct RBNode *right;   // Filho direito
    struct RBNode *parent;  // Pai
} RBNode;

// Estrutura da árvore Red-Black
typedef struct RBTree {
    RBNode *root;
    RBNode *NIL;  // Nó sentinela (nó folha vazio)
} RBTree;

// Função para criar um novo nó da árvore Red-Black
RBNode* createNode(RBTree *tree, int start, int end) {
    RBNode *node = (RBNode*)malloc(sizeof(RBNode));
    node->start = start;
    node->end = end;
    node->color = RED;
    node->left = tree->NIL;
    node->right = tree->NIL;
    node->parent = tree->NIL;
    return node;
}

// Função para criar uma nova árvore Red-Black
RBTree* createTree() {
    RBTree *tree = (RBTree*)malloc(sizeof(RBTree));
    tree->NIL = (RBNode*)malloc(sizeof(RBNode));
    tree->NIL->color = BLACK;  // Nós folha são pretos
    tree->root = tree->NIL;
    return tree;
}

// Função para realizar a rotação à esquerda
void leftRotate(RBTree *tree, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != tree->NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == tree->NIL) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// Função para realizar a rotação à direita
void rightRotate(RBTree *tree, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right != tree->NIL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == tree->NIL) {
        tree->root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

// Função para corrigir a árvore após inserção
void insertFixup(RBTree *tree, RBNode *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode *y = z->parent->parent->right;  // Tio de z
            if (y->color == RED) {  // Caso 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {  // Caso 2
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = BLACK;  // Caso 3
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            RBNode *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

// Função para inserir um novo extent na árvore
void insert(RBTree *tree, int start, int end) {
    RBNode *z = createNode(tree, start, end);
    RBNode *y = tree->NIL;
    RBNode *x = tree->root;
    
    while (x != tree->NIL) {
        y = x;
        if (z->start < x->start) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    z->parent = y;
    if (y == tree->NIL) {
        tree->root = z;
    } else if (z->start < y->start) {
        y->left = z;
    } else {
        y->right = z;
    }
    
    z->left = tree->NIL;
    z->right = tree->NIL;
    z->color = RED;
    
    insertFixup(tree, z);
}

// Função para imprimir a árvore Red-Black (in-order traversal)
void inorderTraversal(RBTree *tree, RBNode *node) {
    if (node != tree->NIL) {
        inorderTraversal(tree, node->left);
        printf("Extent [%d - %d] | Color: %s\n", node->start, node->end, node->color == RED ? "Red" : "Black");
        inorderTraversal(tree, node->right);
    }
}

int main() {
    // Criando a árvore Red-Black
    RBTree *tree = createTree();
    
    // Inserindo extents (intervalos de blocos)
    insert(tree, 10, 20);
    insert(tree, 30, 40);
    insert(tree, 15, 25);
    insert(tree, 50, 60);
    
    // Imprimindo a árvore
    printf("Extents na Árvore Red-Black:\n");
    inorderTraversal(tree, tree->root);
    
    return 0;
}
