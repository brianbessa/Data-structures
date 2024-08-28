#include <stdio.h> 
#include <stdlib.h> 
#include <locale.h> 
#include <unistd.h>

int op; 
int extensaoDaLista = 0;

struct Node { 
    int num; 
    struct Node *proximo; 
};

struct Node *novoNode(int num);
void menu();
void continuar();
void adicionarInicio(struct Node **LISTA, int num);
void adicionarfimlista(struct Node **LISTA, int num);
void AdicionarEmPontoEspecificolista(struct Node **LISTA, int num);
void listartodoselementoslista(struct Node *LISTA);
void listarUmElementoEspecifico(struct Node *LISTA);
void Excluiriniciodalista(struct Node **LISTA);
void Excluirfinaldalista(struct Node **LISTA);
void excluirPontoEspecifico(struct Node **LISTA);
void limparLista(struct Node **LISTA);

struct Node *novoNode(int num) {
    struct Node *novo = (struct Node*)malloc(sizeof(struct Node)); 
    novo->num = num; 
    novo->proximo = NULL; 
    return novo; 
}

void continuar() {
    printf("\n\n");
    system("PAUSE");
    system("CLS");
}

void menu() {
    printf("\n-------------------------------------------------\n");
    printf("%17sMENU DE OPððES\n", "");
    printf("-------------------------------------------------\n");
    printf(" [1] Adicionar no inðcio da lista\n");
    printf(" [2] Adicionar no final da lista\n");
    printf(" [3] Adicionar em um ponto especðfico da lista\n");
    printf(" [4] Listar todos os elementos da lista\n");
    printf(" [5] Listar um elemento especðfico da lista\n");
    printf(" [6] Excluir do inðcio da lista\n");
    printf(" [7] Excluir do final da lista\n");
    printf(" [8] Excluir de um ponto especðfico da lista\n");
    printf(" [9] Liberar os elementos e mostrar a lista vazia\n");
    printf(" [0] Terminar\n");
    printf("-------------------------------------------------\n");
    printf("Escolha uma opððo para prosseguir: ");
}

void adicionarInicio(struct Node **LISTA, int num) {
    struct Node *novo = novoNode(num); 
    novo->proximo = *LISTA;
    *LISTA = novo; 
    extensaoDaLista++; 
}

void adicionarfimlista(struct Node **LISTA, int num) {
    struct Node *novo = novoNode(num); 
    if (*LISTA == NULL) { 
        *LISTA = novo; 
    } else {
        struct Node *temp = *LISTA; 
        while (temp->proximo != NULL) { 
            temp = temp->proximo;
        }
        temp->proximo = novo;
    }
    extensaoDaLista++;
}

void AdicionarEmPontoEspecificolista(struct Node **LISTA, int num) {
    int posicao;
    printf("Digite a posiððo que vocð deseja inserir um nðmero [1 ð %d]: ", extensaoDaLista + 1);
    scanf("%d", &posicao);

    if (posicao > 0 && posicao <= extensaoDaLista + 1) {
        if (posicao == 1) { 
            adicionarInicio(LISTA, num);
            printf("> Nðmero %d adicionado no inðcio da lista.", num); 
        } else {
            struct Node *atual = *LISTA, *anterior = NULL; 
            struct Node *novo = novoNode(num); 
            for (int i = 1; i < posicao; i++) {
                anterior = atual;
                atual = atual->proximo;
            }
            anterior->proximo = novo; 
            novo->proximo = atual;
            extensaoDaLista++; 

            printf("> Nðmero %d adicionado na posiððo %d da lista.", num, posicao);
        }
    } else {
        printf("Posiððo invðlida.\n");
    }
}

void listartodoselementoslista(struct Node *LISTA) {
    system("CLS");
    if (LISTA == NULL) {
        printf("Nðo existem elementos presentes na lista. Portanto, ela estð vazia.");
    } else { 
        if (extensaoDaLista == 1) {
            printf("> Existe apenas um elemento existente na lista: ");
        } else {
            printf("> Existem [%d] elementos existentes na lista: ", extensaoDaLista);
        }
        while (LISTA != NULL) {
            printf("%d ", LISTA->num); 
            LISTA = LISTA->proximo;
        }
    }
    
    printf("\n");
}

void listarUmElementoEspecifico(struct Node *LISTA) {
    int posicao;

    if (LISTA == NULL) {
        printf("A lista nðo possui elementos para serem consultados.");
    } else {
        printf("Digite a posiððo do elemento que deseja listar [1 ð %d]: ", extensaoDaLista);
        scanf("%d", &posicao);

        if (posicao > 0 && posicao <= extensaoDaLista) { 
            for (int i = 1; i < posicao; i++) {
                LISTA = LISTA->proximo;
            }
            printf("Elemento na posiððo %d: %d\n", posicao, LISTA->num);
        } else {
            printf("Posiððo invðlida.\n");
        }
    }
}

void Excluiriniciodalista(struct Node **LISTA) {
    struct Node *temp = *LISTA; 
    *LISTA = (*LISTA)->proximo; 
    free(temp);
    extensaoDaLista--;
}

void Excluirfinaldalista(struct Node **LISTA) {
    if (*LISTA == NULL) { 
        printf("A lista estð vazia. Portanto, nðo tem como excluir elementos.\n"); 
    } else {
        struct Node *temp = *LISTA, *anterior = NULL;
        while (temp->proximo != NULL) { 
            anterior = temp; 
            temp = temp->proximo; 
        }
        if (anterior == NULL) { 
            *LISTA = NULL; 
        } else {
            anterior->proximo = NULL;
        }
        free(temp); 
        extensaoDaLista--;

        printf("Elemento da ðltima posiððo excluðdo da lista.");
    }
}

void excluirPontoEspecifico(struct Node **LISTA) {
    int posicao;
    if (*LISTA == NULL) { 
        printf("A lista estð vazia. Portanto, nðo tem como excluir elementos.\n"); 
    } else {
        printf("Digite a posiððo do elemento que deseja excluir [1 ð %d]: ", extensaoDaLista);
        scanf("%d", &posicao);

        if (posicao > 0 && posicao <= extensaoDaLista) { 
            if (posicao == 1) { 
                Excluiriniciodalista(LISTA); 
                printf("Elemento do inðcio da lista excluðdo com sucesso.");
            } else {
                struct Node *atual = *LISTA, *anterior = NULL; 
                for (int i = 1; i < posicao; i++) { 
                    anterior = atual; 
                    atual = atual->proximo; 
                }
                anterior->proximo = atual->proximo; 
                free(atual); 
                extensaoDaLista--; 

                printf("Elemento da posiððo %d excluðdo com sucesso.", posicao);
            }
        } else {
            printf("Posiððo invðlida.\n");
        }
    }
}

void limparLista(struct Node **LISTA) {
    while (*LISTA != NULL) { 
        Excluiriniciodalista(LISTA); 
    }
}

int main() {

    setlocale(LC_ALL, "Portuguese");
    struct Node *LISTA = NULL; 
    int num;

    do {
        menu();
        scanf(" %d", &op); 

        switch(op) { 
            case 1:
                printf("Digite o nðmero a ser adicionado no inðcio da lista: ");
                scanf("%d", &num);
                adicionarInicio(&LISTA, num);
                printf("> Nðmero %d adicionado ao inðcio da lista.", num);
                continuar();
                break;
            case 2:
                printf("Digite o nðmero a ser adicionado no final da lista: ");
                scanf("%d", &num);
                adicionarfimlista(&LISTA, num);
                printf("> Nðmero %d adicionado ao final da lista.", num);
                continuar();
                break;
            case 3:
                printf("Digite o nðmero a ser adicionado: ");
                scanf("%d", &num);
                AdicionarEmPontoEspecificolista(&LISTA, num);
                continuar();
                break;
            case 4:
                listartodoselementoslista(LISTA);
                continuar();
                break;
            case 5:
                listarUmElementoEspecifico(LISTA);
                continuar();
                break;
            case 6:
                if (LISTA == NULL) { 
                    printf("A lista estð vazia. Portanto, nðo tem como excluir elementos.\n");
                } else {
                    Excluiriniciodalista(&LISTA);
                    printf("Elemento da primeira posiððo excluðdo da lista.");
                } 
                continuar();
                break;
            case 7:
                Excluirfinaldalista(&LISTA);
                continuar();
                break;
            case 8:
                excluirPontoEspecifico(&LISTA);
                continuar();
                break;
            case 9:
                limparLista(&LISTA);
                printf("Elementos da lista liberados. Portanto, a lista agora estð vazia.");
                continuar();
                break;
            case 0:
                printf("Programa sendo finalizado.\n");
                break;
            default:
                printf("\nOpððo invðlida. Por favor, tente novamente.\n");
                continuar();
        }

        while (getchar() != '\n'); 

    } while (op != 0); 

    return 0; 
}