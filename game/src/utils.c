#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include "../include/utils.h"

void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void aplicar_delay(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

void imprimir_com_delay(const char *mensagem, int ms) {
    for (int i = 0; mensagem[i] != '\0'; i++) {
        printf("%c", mensagem[i]);
        fflush(stdout);
        aplicar_delay(ms);
    }
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ler_inteiro(const char *mensagem) {
    printf("%s", mensagem);
    int i;
    while (scanf("%d", &i) != 1) {
        printf("Entrada invalida!\n%s", mensagem);
        limpar_buffer();
    }
    limpar_buffer();
    return i;
}

void ler_string(const char *mensagem, char *destino, int tamanho) {
    printf("%s", mensagem);
    fgets(destino, tamanho, stdin);
    int pos = strcspn(destino, "\n");
    (pos != -1) ? destino[pos] = '\0' : printf("Erro ao ler texto!\n");
}

void converter_maiusculo(char *texto) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] >= 'a' && texto[i] <= 'z') texto[i] -= 32;
    }
}

void trocar_valores(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}