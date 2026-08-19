#include <stdio.h>
#include <stdbool.h>

#include "../include/conecta_4.h"
#include "../include/jogador.h"
#include "../include/jogos_utils.h"

void inicializar_grade(char grade[L][C]) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            grade[i][j] = '.';
        }
    }
}

void imprimir_grade(int jogadas, char grade[L][C], Jogador usuario) {
    printf("\n=============== CONNECT-4 ===============\n");
    printf("\nJogador atual: %s\nScore atual: %d | Score maximo: %d\n\n", usuario.nome, usuario.score_atual, usuario.score_maximo);
    for (int i = 0; i < C; i++) {
        if (i == 0) printf("|");
        printf(" %d ", i);
        if (i == C - 1) printf("|\n");
    }
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            if (j == 0) printf("|");
            printf(" %c ", grade[i][j]);
            if (j == C - 1) printf("|\n");
        }
    }
    printf("\nJogada: %d\n", jogadas);
}

bool soltar_peca(int coluna, char jogador, char grade[L][C], bool foi_marcado[L][C]) {
    if (coluna < 0 || coluna >= C) {
        printf("\nColuna inexistente!\nPor favor, tente novamente.\n");
        return false;
    }
    for (int i = L - 1; i >= 0; i--) {
        if (!foi_marcado[i][coluna]) {
            grade[i][coluna] = jogador;
            foi_marcado[i][coluna] = true;
            return true;
        }
    }
    printf("\nColuna %d cheia! Por favor, escolha outra.\n", coluna);
    return false;
}

bool teste_direcao(char jogador, char grade[L][C], int x, int y, int dx, int dy) {
    for (int i = 0; i < 4; i++) {
        int novo_x = x + (dx * i);
        int novo_y = y + (dy * i);
        if (novo_x < 0 || novo_x >= L || novo_y < 0 || novo_y >= C) return false;
        if (grade[novo_x][novo_y] != jogador) return false;
    }
    return true;
}

bool venceu_grade(char jogador, char grade[L][C]) {
    for (int x = 0; x < L; x++) {
        for (int y = 0; y < C; y++) {
            if (grade[x][y] == jogador) {
                if (teste_direcao(jogador, grade, x, y, 0, 1)) return true;
                if (teste_direcao(jogador, grade, x, y, 1, 0)) return true;
                if (teste_direcao(jogador, grade, x, y, 1, 1)) return true;
                if (teste_direcao(jogador, grade, x, y, -1, 1)) return true;
            }
        }
    }
    return false;
}