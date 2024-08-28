#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct noGrafo {
    int info;
    struct noGrafo *proxNo;
    struct noArco *arcos;
};

typedef struct noGrafo *PtrNoGrafo;

struct noArco {
    int peso;
    struct noGrafo *no;
    struct noArco *proxArco;
};

typedef struct noArco *PtrNoArco;

void menu();
void continuar();
void insertnode(PtrNoGrafo *g, int info);
void joinwtInfo(PtrNoGrafo g, int x1, int x2, int p);
int adjacent(PtrNoGrafo g, int x1, int x2);
void exibirGrafo(PtrNoGrafo g);
void removerVertice(PtrNoGrafo *g, int info);
void removerAresta(PtrNoGrafo g, int x1, int x2);
PtrNoGrafo procurarVertice(PtrNoGrafo g, int info);

int opcao;

void continuar() {
    printf("\n");
    system("PAUSE");
    system("CLS");
}

void menu() {
    printf("===================================\n");
    printf("                MENU               \n");
    printf("===================================\n");
    printf("1. Inserir v�rtices\n");
    printf("2. Inserir arestas\n");
    printf("3. Visualizar grafo\n");
    printf("4. Remover v�rtices\n");
    printf("5. Remover arestas\n");
    printf("6. Sair\n");
    printf("Escolha uma opcao: ");
    scanf(" %d", &opcao);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    system("CLS");

    PtrNoGrafo grafo = NULL;
    int info, x1, x2, p;

    do {
        menu();

        switch (opcao) {
            case 1:
                printf("Insira o valor do v�rtice: ");
                scanf("%d", &info);
                insertnode(&grafo, info);
                continuar();
                break;
            case 2:
                printf("Informe o v�rtice de origem x1: ");
                scanf(" %d", &x1);
                printf("Informe o v�rtice de destino x2: ");
                scanf(" %d", &x2);
                printf("Informe o peso da aresta: ");
                scanf(" %d", &p);
                joinwtInfo(grafo, x1, x2, p);
                continuar();
                break;
            case 3:
                exibirGrafo(grafo);
                continuar();
                break;
            case 4:
                if (!grafo) {
                    printf("Grafo n�o possui v�rtice para ser removido.\n");
                } else {
                    PtrNoGrafo sortedList = NULL;
                    PtrNoGrafo current = grafo;

                    while (current) {
                        PtrNoGrafo novo = (PtrNoGrafo)malloc(sizeof(struct noGrafo));
                        novo->info = current->info;
                        novo->arcos = current->arcos;
                        novo->proxNo = NULL;

                        if (!sortedList || novo->info < sortedList->info) {
                            novo->proxNo = sortedList;
                            sortedList = novo;
                        } else {
                            PtrNoGrafo temp = sortedList;
                            while (temp->proxNo && temp->proxNo->info < novo->info) {
                                temp = temp->proxNo;
                            }
                            novo->proxNo = temp->proxNo;
                            temp->proxNo = novo;
                        }
                        current = current->proxNo;
                    }

                    printf("V�rtices existentes no grafo: ");
                    PtrNoGrafo temp = sortedList;
                    while (temp) {
                        printf("%d ", temp->info);
                        temp = temp->proxNo;
                    }
                    printf("\n");

                    while (sortedList) {
                        PtrNoGrafo temp = sortedList;
                        sortedList = sortedList->proxNo;
                        free(temp);
                    }

                    printf("Digite o valor do v�rtice a ser removido: ");
                    scanf("%d", &info);
                    removerVertice(&grafo, info);
                }
                continuar();
                break;
            case 5:
                if (!grafo) {
                    printf("Grafo n�o possui aresta para ser removida.\n");
                } else {
                    printf("Informe o v�rtice x1 da aresta a ser removida: ");
                    scanf(" %d", &x1);
                    printf("Informe o v�rtice x2 da aresta a ser removida: ");
                    scanf(" %d", &x2);
                    removerAresta(grafo, x1, x2);
                }
                continuar();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opc�o inv�lida!\n");
        }
    } while (opcao != 6);

    return 0;
}

void insertnode(PtrNoGrafo *g, int info) {
    if (procurarVertice(*g, info)) {
        printf("V�rtice %d j� existe no grafo.\n", info);
    } else {
        PtrNoGrafo novoVertice = (PtrNoGrafo)malloc(sizeof(struct noGrafo));
        novoVertice->info = info;
        novoVertice->proxNo = *g;
        novoVertice->arcos = NULL;
        *g = novoVertice;
        printf("V�rtice %d criado com sucesso.\n", info);
    }
}

void joinwtInfo(PtrNoGrafo g, int x1, int x2, int p) {
    PtrNoGrafo no1 = procurarVertice(g, x1);
    PtrNoGrafo no2 = procurarVertice(g, x2);

    if (no1 && no2) {
        PtrNoArco newArco1 = (PtrNoArco)malloc(sizeof(struct noArco));
        newArco1->peso = p;
        newArco1->no = no2;
        newArco1->proxArco = no1->arcos;
        no1->arcos = newArco1;
    } else {
        printf("Um ou ambos os v�rtices n�o existem.\n");
    }
}

int adjacent(PtrNoGrafo g, int x1, int x2) {
    PtrNoGrafo no = procurarVertice(g, x1);
    if (no) {
        PtrNoArco arco = no->arcos;
        while (arco) {
            if (arco->no->info == x2) {
                return 1;
            }
            arco = arco->proxArco;
        }
    }
    return 0;
}

void exibirGrafo(PtrNoGrafo g) {
    PtrNoGrafo sortedList = NULL;
    PtrNoGrafo current = g;

    while (current) {
        PtrNoGrafo novo = (PtrNoGrafo)malloc(sizeof(struct noGrafo));
        novo->info = current->info;
        novo->arcos = current->arcos;
        novo->proxNo = NULL;

        if (!sortedList || novo->info < sortedList->info) {
            novo->proxNo = sortedList;
            sortedList = novo;
        } else {
            PtrNoGrafo temp = sortedList;
            while (temp->proxNo && temp->proxNo->info < novo->info) {
                temp = temp->proxNo;
            }
            novo->proxNo = temp->proxNo;
            temp->proxNo = novo;
        }
        current = current->proxNo;
    }

    PtrNoGrafo no = sortedList;
    if (!no) {
        printf("Grafo n�o encontrado. Voc� precisa definir v�rtices e arestas para a cria��o de um grafo.\n");
        return;
    }

    while (no) {
        printf("V�rtice %d ----->", no->info);
        PtrNoArco arco = no->arcos;
        while (arco) {
            printf(" %d(%d) ->", arco->no->info, arco->peso);
            arco = arco->proxArco;
        }
        printf("\n");
        no = no->proxNo;
    }

    while (sortedList) {
        PtrNoGrafo temp = sortedList;
        sortedList = sortedList->proxNo;
        free(temp);
    }
}

void removerVertice(PtrNoGrafo *g, int info) {
    PtrNoGrafo current = *g;
    PtrNoGrafo prev = NULL;

    while (current && current->info != info) {
        prev = current;
        current = current->proxNo;
    }

    if (current) {
        if (prev) {
            prev->proxNo = current->proxNo;
        } else {
            *g = current->proxNo;
        }

        PtrNoArco arco = current->arcos;
        while (arco) {
            PtrNoArco tempArco = arco;
            arco = arco->proxArco;
            free(tempArco);
        }

        free(current);
    } else {
        printf("V�rtice n�o encontrado.\n");
    }

    printf("V�rtices restantes no grafo: ");
    PtrNoGrafo temp = *g;
    while (temp) {
        printf("%d ", temp->info);
        temp = temp->proxNo;
    }
    printf("\n");
}

void removerAresta(PtrNoGrafo g, int x1, int x2) {
    PtrNoGrafo no = procurarVertice(g, x1);
    int encontrado = 0;

    if (no) {
        PtrNoArco arco = no->arcos;
        PtrNoArco prevArco = NULL;

        while (arco && arco->no->info != x2) {
            prevArco = arco;
            arco = arco->proxArco;
        }

        if (arco) {
            if (prevArco) {
                prevArco->proxArco = arco->proxArco;
            } else {
                no->arcos = arco->proxArco;
            }
            free(arco);
            encontrado = 1;
        }
    }

    no = procurarVertice(g, x2);

    if (no) {
        PtrNoArco arco = no->arcos;
        PtrNoArco prevArco = NULL;

        while (arco && arco->no->info != x1) {
            prevArco = arco;
            arco = arco->proxArco;
        }

        if (arco) {
            if (prevArco) {
                prevArco->proxArco = arco->proxArco;
            } else {
                no->arcos = arco->proxArco;
            }
            free(arco);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Aresta n�o encontrada.\n");
    }
}

PtrNoGrafo procurarVertice(PtrNoGrafo g, int info) {
    PtrNoGrafo no = g;
    while (no && no->info != info) {
        no = no->proxNo;
    }
    return no;
}
