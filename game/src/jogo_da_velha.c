#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/jogo_da_velha.h"
#include "../include/jogador.h"
#include "../include/jogos_utils.h"

void inicializar_tabuleiro(char tabuleiro[M][M]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            tabuleiro[i][j] = '.';
        }
    }
}

void imprimir_tabuleiro(int jogadas, char tabuleiro[M][M], Jogador usuario) {
    printf("\n=============== TIC-TAC-TOE ===============\n");
    printf("\nJogador atual: %s\nScore atual: %d | Score maximo: %d\n\n", usuario.nome, usuario.score_atual, usuario.score_maximo);
    for (int i = 0; i < M; i++) {
        if (i == 0) printf("| # ");
        printf(" %d ", i);
        if (i == M - 1) printf("|\n");
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (j == 0) printf("| %d ", i);
            printf(" %c ", tabuleiro[i][j]);
            if (j == M - 1) printf("|\n");
        }
    }
    printf("\nJogada: %d\n", jogadas);
}

bool venceu_partida(char jogador, char tabuleiro[M][M]) {
    if (jogador != 'X' && jogador != 'O') return false;
    for (int i = 0; i < M; i++) {
        if ((tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) || 
            (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador)) 
            return true;
    }
    if ((tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) || 
        (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador)) return true;
    return false;
}