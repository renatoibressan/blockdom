#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/jogos_utils.h"
#include "../include/utils.h"

void inicializar_vetor(int v[], int n, int val) {
    for (int i = 0; i < n; i++) {
        v[i] = val;
    }
}

void inicializar_vetor_bool(bool v[], int n, bool status) {
    for (int i = 0; i < n; i++) {
        v[i] = status;
    }
}

void inicializar_mapa_bool(int l, int c, bool mapa[l][c]) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            mapa[i][j] = false;
        }
    }
}

bool eh_coordenada_valida(int c, int n) {
    return c >= 0 && c < n;
}

Coordenadas ler_coordenadas(const char *mensagem, int n) {
    printf("%s", mensagem);
    int x = ler_inteiro("X (Horizontal): ");
    while(!eh_coordenada_valida(x, n)) {
        printf("Coordenada invalida! Por favor, tente novamente\n");
        x = ler_inteiro("X (Horizontal): ");
    }
    int y = ler_inteiro("Y (Vertical): ");
    while(!eh_coordenada_valida(y, n)) {
        printf("Coordenada invalida! Por favor, tente novamente\n");
        y = ler_inteiro("Y (Vertical): ");
    }
    return (Coordenadas){.x = x, .y = y};
}