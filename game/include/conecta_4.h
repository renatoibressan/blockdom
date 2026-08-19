#ifndef CONECTA_4_C
#define CONECTA_4_C

#include <stdbool.h>

#include "../include/jogador.h"
#include "../include/jogos_utils.h"

#define L 6
#define C 7

void inicializar_grade(char grade[L][C]);
void imprimir_grade(int jogadas, char grade[L][C], Jogador usuario);
bool soltar_peca(int coluna, char jogador, char grade[L][C], bool foi_marcado[L][C]);
bool teste_direcao(char jogador, char grade[L][C], int x, int y, int dx, int dy);
bool venceu_grade(char jogador, char grade[L][C]);

#endif