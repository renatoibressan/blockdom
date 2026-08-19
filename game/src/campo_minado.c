#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "../include/campo_minado.h"
#include "../include/jogador.h"
#include "../include/jogos_utils.h"
#include "../include/utils.h"

void inicializar_campo(char campo[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            campo[i][j] = '.';
        }
    }
}

void inicializar_bombas(Coordenadas iniciais, Coordenadas bombas[N], bool tem_bomba[N][N]) {
    for (int i = 0; i < N;) {
        int x = rand() % N;
        int y = rand() % N;
        bool adjacente = abs(x - iniciais.x) <= 1 && abs(y - iniciais.y) <= 1;
        if (adjacente) continue;
        if (tem_bomba[x][y]) continue;
        bombas[i].x = x;
        bombas[i].y = y;
        tem_bomba[x][y] = true;
        i++;
    }
}

void imprimir_campo(int jogadas, int remanescentes, char campo[N][N], Jogador usuario) {
    printf("\n=============== MINESWEEPER ===============\n");
    printf("\nJogador atual: %s\nScore atual: %d | Score maximo: %d\n\n", usuario.nome, usuario.score_atual, usuario.score_maximo);
    for (int i = 0; i < N; i++) {
        if (i == 0) printf("| # ");
        printf(" %d ", i);
        if (i == N - 1) printf("|\n");
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j == 0) printf("| %d ", i);
            printf(" %c ", campo[i][j]);
            if (j == N - 1) printf("|\n");
        }
    }
    printf("\nJogada: %d\nBombas remanescentes: %d\n", jogadas, remanescentes);
}

void imprimir_bombas(Coordenadas bombas[N]) {
    for (int i = 0; i < N; i++) {
        if (i == 0) printf("\nCoordenadas das bombas:\n");
        if (i > 0) printf(", ");
        printf("(%d,%d)", bombas[i].x, bombas[i].y);
        if (i == N - 1) printf("\n\nTente novamente outra vez\n");
    }
}

int contar_adjacentes(Coordenadas atuais, bool tem_bomba[N][N]) {
    int adjacentes = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = atuais.x + dx;
            int ny = atuais.y + dy;
            if (nx >= 0 && nx < N && ny >= 0 && ny < N && tem_bomba[nx][ny]) adjacentes++;
        }
    }
    return adjacentes;
}

void modificar_campo(Coordenadas atuais, bool tem_bomba[N][N], bool foi_escavado[N][N], char campo[N][N], int *escavados) {
    if (!eh_coordenada_valida(atuais.x, N) || !eh_coordenada_valida(atuais.y, N)) return;
    if (foi_escavado[atuais.x][atuais.y]) return;
    if (tem_bomba[atuais.x][atuais.y]) return;
    foi_escavado[atuais.x][atuais.y] = true;
    (*escavados)++;
    int adjacentes = contar_adjacentes(atuais, tem_bomba);
    campo[atuais.x][atuais.y] = (adjacentes == 0) ? ' ' : adjacentes + '0';
    if (adjacentes == 0) {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                Coordenadas vizinho = {atuais.x + dx, atuais.y + dy};
                modificar_campo(vizinho, tem_bomba, foi_escavado, campo, escavados);
            }
        }
    }
}

void marcar_bombas_remanescentes(Coordenadas bombas[N], char campo[N][N], bool foi_escavado[N][N]) {
    for (int i = 0; i < N; i++) {
        int x = bombas[i].x;
        int y = bombas[i].y;
        if (!foi_escavado[x][y]) campo[x][y] = '*';
    }
}