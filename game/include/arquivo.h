#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdbool.h>

#include "../include/jogador.h"

bool salvar_dados(const char *caminho, Jogador *lista, int quantidade);
bool carregar_dados(const char *caminho, Jogador **lista, int *quantidade, int *capacidade);

#endif