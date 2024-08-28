#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANHO 15
#define MAX_PALAVRAS 100

typedef struct No {
    char palavra[TAMANHO + 1];  
    int quantidade;
    struct No *esquerda;
    struct No *direita;
} No;

No* criarNo(char *palavra);
No* inserir(No *raiz, char *palavra);
void percorrendoOrdemAlfabetica(No *raiz);
void processaPalavras(char *str[]);
void liberarArvore(No *raiz);
void removerEspacos(char *str);

No* criarNo(char *palavra) {
    No *novoNo = (No*)malloc(sizeof(No));
    if (novoNo != NULL) {
        strcpy(novoNo->palavra, palavra);
        novoNo->quantidade = 1;
        novoNo->esquerda = novoNo->direita = NULL;
    } else {
        printf("Erro de mem�ria.\n");
    }
    return novoNo;
}

No* inserir(No *raiz, char *palavra) {
    if (raiz == NULL)
        return criarNo(palavra);

    int comparacao = strcmp(palavra, raiz->palavra);
    if (comparacao < 0)
        raiz->esquerda = inserir(raiz->esquerda, palavra);
    else if (comparacao > 0)
        raiz->direita = inserir(raiz->direita, palavra);
    else
        raiz->quantidade++;

    return raiz;
}

void percorrendoOrdemAlfabetica(No *raiz) {
    if (raiz != NULL) {
        percorrendoOrdemAlfabetica(raiz->esquerda);
        printf(" %s (%d)\n", raiz->palavra, raiz->quantidade);
        percorrendoOrdemAlfabetica(raiz->direita);
    }
}

void processaPalavras(char *str[]) {
    No *raiz = NULL;
    for (int i = 0; str[i][0] != '\0'; i++) {
        if (strlen(str[i]) > TAMANHO) {
            printf("A palavra '%s' deve conter at�, no m�ximo, 15 letras.\n", str[i]);
            continue;
        }
        removerEspacos(str[i]);
        raiz = inserir(raiz, str[i]);
    }

    printf("\n---------------------------------------\n");
    printf("Palavras digitadas em ordem alfab�tica:\n");
    printf("---------------------------------------\n\n");

    percorrendoOrdemAlfabetica(raiz);

    liberarArvore(raiz);
}

void liberarArvore(No *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

void removerEspacos(char *spcBranco) {
    int i, j;
    for (i = 0, j = 0; spcBranco[i] != '\0'; i++) {
        if (spcBranco[i] != ' ') {
            spcBranco[j++] = spcBranco[i];
        }
    }
    spcBranco[j] = '\0';
}

int main() {
    system("CLS");
    setlocale(LC_ALL, "Portuguese");

    char *palavras[MAX_PALAVRAS];
    for (int i = 0; i < MAX_PALAVRAS; i++) {
        palavras[i] = (char *)malloc((TAMANHO + 2) * sizeof(char));
    }

    printf("Digite as palavras [\"parar\" encerra o programa]:\n");
    int i = 0;
    while (1) {
        printf("- ");
        if (fgets(palavras[i], TAMANHO + 2, stdin) == NULL) {
            printf("Erro.");
            break;
        }

        palavras[i][strcspn(palavras[i], "\n")] = '\0';

        removerEspacos(palavras[i]);
        if (strcasecmp(palavras[i], "parar") == 0) {
            palavras[i][0] = '\0';
            break;
        }

        if (strlen(palavras[i]) > TAMANHO) {
            printf("A palavra deve conter at�, no m�ximo, 15 letras. Tente novamente.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        i++;
        if (i >= MAX_PALAVRAS - 1) {
            printf("N�mero m�ximo de palavras atingido.\n");
            break;
        }
    }

    processaPalavras(palavras);

    for (int j = 0; j < MAX_PALAVRAS; j++) {
        free(palavras[j]);
    }

    printf("\n");

    return 0;
}
