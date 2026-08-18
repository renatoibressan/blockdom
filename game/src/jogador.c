#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/jogador.h"
#include "../include/utils.h"

void cadastrar_jogador(Jogador **jogadores, const char *nome, int *qtd, int *capacidade) {
    if (*qtd >= *capacidade) {
        *capacidade *= 2;
        Jogador *temp = realloc(*jogadores, (*capacidade)*sizeof(Jogador));
        if (!temp) {
            printf("\nErro ao realocar memoria!\n");
            return;
        }
        *jogadores = temp;
    }
    strcpy((*jogadores)[*qtd].nome, nome);
    (*jogadores)[*qtd].score_atual = 0;
    (*jogadores)[*qtd].score_maximo = 0;
    converter_maiusculo((*jogadores)[*qtd].nome);
    printf("\nJogador %s cadastrado com sucesso!\n", (*jogadores)[*qtd].nome);
    (*qtd)++;
}

void trocar_jogadores(Jogador *jogador1, Jogador *jogador2) {
    Jogador temp = *jogador1;
    *jogador1 = *jogador2;
    *jogador2 = temp;
}

int particionar_vetor(Jogador **jogadores, int inicio, int fim) {
    int pos = inicio + rand() % (fim - inicio + 1);
    trocar_jogadores(&(*jogadores)[pos], &(*jogadores)[fim]);
    Jogador pivo = (*jogadores)[fim];
    int i = inicio - 1;
    for (int j = inicio; j < fim; j++) {
        if ((*jogadores)[j].score_maximo > pivo.score_maximo || ((*jogadores)[j].score_atual > pivo.score_atual && (*jogadores)[j].score_maximo == pivo.score_maximo)) {
            i++;
            trocar_jogadores(&(*jogadores)[i], &(*jogadores)[j]);
        }
    }
    trocar_jogadores(&(*jogadores)[i + 1], &(*jogadores)[fim]);
    return i + 1;
}

void ordenar_jogadores(Jogador **jogadores, int inicio, int fim) {
    if (inicio < fim) {
        int p = particionar_vetor(jogadores, inicio, fim);
        ordenar_jogadores(jogadores, inicio, p - 1);
        ordenar_jogadores(jogadores, p + 1, fim);
    }
}

void exibir_ranking(const char *mensagem, Jogador *jogadores, int qtd) {
    if (!jogadores || qtd == 0) {
        printf("\nNao ha jogadores a serem listados!\n");
        return;
    }
    printf("%s\n", mensagem);
    for (int i = 0; i < qtd; i++) {
        printf("%d. %s (MAX: %d)\n", i + 1, jogadores[i].nome, jogadores[i].score_maximo);
        if (i < qtd - 1) printf("========================================\n");
    }
    printf("\n");
}