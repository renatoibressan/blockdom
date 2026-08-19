#ifndef SISTEMA_H
#define SISTEMA_H

#include <stdbool.h>

#include "../include/jogador.h"

#define T 20

void executar();
void campo_minado(Jogador **jogadores, int *quantidade, int *capacidade, bool *ordenado);
void jogo_da_velha(Jogador **jogadores, int *quantidade, int *capacidade, bool *ordenado);
void conecta_4(Jogador **jogadores, int *quantidade, int *capacidade, bool *ordenado);
void consultar_ranking(Jogador **jogadores, int quantidade, bool *ordenado);

#endif