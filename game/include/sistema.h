#ifndef SISTEMA_H
#define SISTEMA_H

#include <stdbool.h>

#include "../include/jogador.h"

void executar();
void campo_minado(Jogador **jogadores, int *quantidade, int *capacidade, bool *ordenado);
void jogo_da_velha(Jogador **jogadores, int *quantidade, int *capacidade, bool *ordenado);
void consultar_ranking(Jogador **jogadores, int quantidade, bool *ordenado);

#endif