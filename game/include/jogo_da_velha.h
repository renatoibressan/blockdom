#ifndef JOGO_DA_VELHA_H
#define JOGO_DA_VELHA_H

#include <stdbool.h>

#include "../include/jogador.h"
#include "../include/jogos_utils.h"

void inicializar_tabuleiro(char tabuleiro[M][M]);
void imprimir_tabuleiro(int jogadas, char tabuleiro[M][M], Jogador usuario);
bool venceu_partida(char jogador, char tabuleiro[M][M]);

#endif