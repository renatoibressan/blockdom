#ifndef CAMPO_MINADO_H
#define CAMPO_MINADO_H

#include <stdbool.h>

#include "../include/jogador.h"
#include "../include/jogos_utils.h"

void inicializar_campo(char campo[N][N]);
void inicializar_bombas(Coordenadas iniciais, Coordenadas bombas[N], bool tem_bomba[N][N]);
void imprimir_campo(int jogadas, int remanescentes, char campo[N][N], Jogador usuario);
void imprimir_bombas(Coordenadas bombas[N]);
int contar_adjacentes(Coordenadas atuais, bool tem_bomba[N][N]);
void modificar_campo(Coordenadas atuais, bool tem_bomba[N][N], bool foi_escavado[N][N], char campo[N][N], int *escavados);
void marcar_bombas_remanescentes(Coordenadas bombas[N], char campo[N][N], bool foi_escavado[N][N]);

#endif