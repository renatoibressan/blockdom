#ifndef JOGOS_UTILS_H
#define JOGOS_UTILS_H

#include <stdbool.h>

#define M 3
#define N 10

typedef struct {
    int x;
    int y;
} Coordenadas;

void inicializar_vetor(int v[N], int n, int val);
void inicializar_vetor_bool(bool v[N], int n, bool status);
void inicializar_mapa_bool(int n, bool mapa[n][n]);
bool eh_coordenada_valida(int c);
Coordenadas ler_coordenadas(const char *mensagem);

#endif