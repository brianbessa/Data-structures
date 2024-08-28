#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_CARROS 5
#define TAM_PLACA 8

void continuar() {
    printf("\n\n");
    system("PAUSE");
    system("CLS");
}

typedef struct {
    char placa[TAM_PLACA];
    int mov;
} Carro;

typedef struct {
    Carro carros[MAX_CARROS];
    int top;
} Stack;

char entrada[MAX_CARROS * 10][TAM_PLACA];
char saida[MAX_CARROS * 10][TAM_PLACA];
int entradaCount = 0;
int saidaCount = 0;

void initializeStack(Stack* stack) {
    stack->top = -1;
}

int cheio(Stack* stack) {
    return stack->top == MAX_CARROS - 1;
}

int vazio(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, Carro car) {
    if (!cheio(stack)) {
        stack->carros[++stack->top] = car;
    }
}

Carro pop(Stack* stack) {
    if (!vazio(stack)) {
        return stack->carros[stack->top--];
    }
    Carro carrosVaz;
    strncpy(carrosVaz.placa, "", TAM_PLACA);
    carrosVaz.mov = 0;
    return carrosVaz;
}

Carro peek(Stack* stack) {
    if (!vazio(stack)) {
        return stack->carros[stack->top];
    }
    Carro carrosVaz;
    strncpy(carrosVaz.placa, "", TAM_PLACA);
    carrosVaz.mov = 0;
    return carrosVaz;
}

int acharCar(Stack* stack, char placa[TAM_PLACA]) {
    for (int i = 0; i <= stack->top; i++) {
        if (strcmp(stack->carros[i].placa, placa) == 0) {
            return i;
        }
    }
    return -1;
}

void gerarPlaca(char placa[TAM_PLACA]) {
    for (int i = 0; i < 3; i++) {
        placa[i] = 'A' + rand() % 26;
    }

    for (int i = 3; i < 7; i++) {
        placa[i] = '0' + rand() % 10;
    }

    placa[7] = '\0';
}

void entradas(Stack* stack) {
    if (cheio(stack)) {
        printf("Estacionamento cheio. N•À?o •À? poss•À?vel adicionar mais carros.\n");
    } else {
        Carro car;
        gerarPlaca(car.placa);
        car.mov = 0;
        push(stack, car);
        strncpy(entrada[entradaCount++], car.placa, TAM_PLACA);
        printf("Carro com placa %s entrou no estacionamento.\n", car.placa);
    }
}

void saidas(Stack* stack, char placa[TAM_PLACA]) {
    printf("Carros atualmente no estacionamento:\n");
    if (vazio(stack)) {
        printf("Nenhum carro no estacionamento.\n");
    } else {
        for (int i = stack->top; i >= 0; i--) {
            printf("%s\n", stack->carros[i].placa);
        }

        printf("\nDigite a placa do carro (7 d•À?gitos): ");
        scanf("%s", placa);

        int index = acharCar(stack, placa);
    
        if (index == -1) {
            printf("Carro %s n•À?o est•À? no estacionamento.\n", placa);
            return;
        }

        Stack tempStack;
        initializeStack(&tempStack);

        Carro car;
        Carro carroSaindo;
        int found = 0;

        while (!vazio(stack)) {
            car = pop(stack);
            if (strcmp(car.placa, placa) == 0) {
                car.mov++;
                strncpy(saida[saidaCount++], car.placa, TAM_PLACA);
                carroSaindo = car;
                found = 1;
                printf("Carro %s saiu do estacionamento.\n", car.placa);
                break;
            } else {
                car.mov++;
                push(&tempStack, car);
            }
        }

        while (!vazio(&tempStack)) {
            car = pop(&tempStack);
            push(stack, car);
        }

        if (found) {
            printf("O carro %s foi manobrado um total de %d vezes.\n", carroSaindo.placa, carroSaindo.mov);
        }        
    }
}

void relatorio(Stack* stack) {
    printf("\nRelat•À?rio de Estacionamento\n");
    if (vazio(stack)) {
        printf("N•À?o h•À? carros no estacionamento.\n");
    } else {
        printf("\nCarros atualmente no estacionamento (do •À?ltimo para o primeiro):\n");
        for (int i = stack->top; i >= 0; i--) {
            printf("Placa: %s, Manobras: %d\n", stack->carros[i].placa, stack->carros[i].mov);
        }
    }
}

int main() {
    setlocale(LC_ALL, "");
    Stack estacionamento;
    initializeStack(&estacionamento);
    srand(time(NULL));

    int escolha;
    char placa[TAM_PLACA];

    do {
        printf("\n------------------------------------------------------------------\n");
        printf("MENU DE OP•À?•À?ES\n");
        printf("------------------------------------------------------------------\n");
        printf("[1] Entrada de um carro\n");
        printf("[2] Sa•À?da de um carro\n");
        printf("[3] Relat•À?rio\n");
        printf("[0] Terminar\n");
        printf("------------------------------------------------------------------\n");
        printf("Qual a sua op•À?•À?o? ");

        if (scanf("%d", &escolha) != 1) {
            printf("Entrada inv•À?lida. Por favor, tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (escolha) {
            case 1:
                entradas(&estacionamento);
                continuar();
                break;
            case 2:
                saidas(&estacionamento, placa);
                continuar();
                break;
            case 3:
                relatorio(&estacionamento);
                continuar();
                break;
            case 0:
                printf("Programa terminado.\n");
                break;
            default:
                printf("Op•À?•À?o inv•À?lida\n");
        }
    } while (escolha != 0);

    return 0;
}