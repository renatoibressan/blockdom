#ifndef JOGOS_UTILS_H
#define JOGOS_UTILS_H

#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Coordenadas;

void inicializar_vetor(int v[], int n, int val);
void inicializar_vetor_bool(bool v[], int n, bool status);
void inicializar_mapa_bool(int l, int c, bool mapa[l][c]);
bool eh_coordenada_valida(int c, int n);
Coordenadas ler_coordenadas(const char *mensagem, int n);

#endif