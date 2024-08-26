#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBROS 2
#define MAX_CLUBE 100

typedef struct Membro{
    int indice;
    char nome[100];
    struct Membro *padrinho;
    struct Membro *afilhados[MAX_MEMBROS];
    int num_afilhados;
} Membro;

Membro* clube[MAX_CLUBE];
int cont_Membros = 0;

Membro* criarMembro(Membro* padrinho) {
    Membro *novoMembro = (Membro*)malloc(sizeof(Membro));
    if (novoMembro == NULL) {
        printf("Erro ao alocar memória para novo membro.\n");
        exit(1);
    }

    char nome[100];
    printf("Digite o nome do novo membro: ");
    scanf("%s", nome);

    strcpy(novoMembro->nome, nome);
    novoMembro->padrinho = padrinho;    
    novoMembro->num_afilhados = 0;
    cont_Membros++;

    clube[cont_Membros - 1] = novoMembro; // Adiciona o novo membro ao vetor clube
    printf("Membro %s convidado com sucesso!\n", novoMembro->nome);
    return novoMembro;
}

void convidar(Membro *padrinho){
    int opcao;
    printf("Deseja convidar membros?\n");
    printf("1. Sim\n");
    printf("2. Não\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    if (opcao == 1 && padrinho->num_afilhados < MAX_MEMBROS) {
        padrinho->afilhados[padrinho->num_afilhados++] = criarMembro(padrinho);
        if (padrinho->num_afilhados < MAX_MEMBROS) {
            padrinho->afilhados[padrinho->num_afilhados++] = criarMembro(padrinho);
        }
    } else {
        printf("Padrinho já atingiu o limite de afilhados.\n");
    }
}

void criarPadrinho() {
    Membro *padrinho = (Membro*)malloc(sizeof(Membro));
    
    printf("Digite o nome do padrinho principal: ");
    scanf("%s", padrinho->nome);

    padrinho->indice = 0;
    padrinho->num_afilhados = 0;
    padrinho->padrinho = NULL;
    padrinho->afilhados[0] = NULL;

    clube[0] = padrinho;
    cont_Membros++;
    printf("Padrinho principal %s criado com sucesso!\n", padrinho->nome);
}

void mostrarMembros() {
    printf("Membros do clube:\n");
    for (int i = 0; i < cont_Membros; i++){
        if (clube[i]->num_afilhados != 0){
            printf("Membro %s\n", clube[i]->nome);
            printf("Afilhado 1: %s\n", clube[i]->afilhados[0]->nome);
            printf("Afilhado 2: %s\n", clube[i]->afilhados[1]->nome);
        }
        else{
            printf("Membro %s não tem afilhados\n", clube[i]->nome);
        }
        printf("\n");
    }
    return;
}

int main(void) {
    int opcao;
    int cont_convite = 0;
    criarPadrinho();
    do {
        printf("\n----- MENU -----\n");
        printf("1. Convidar membro\n");
        printf("2. Mostrar membros\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                convidar(clube[cont_convite]);
                cont_convite++;
                break;
            case 2:
                mostrarMembros();
                break;
            case 3:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 3);

    // Liberar a memória alocada para membros do clube
    for (int i = 0; i < cont_Membros; i++) {
        free(clube[i]);
    }

    return 0;
}
