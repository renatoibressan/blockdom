#ifndef JOGADOR_H
#define JOGADOR_H

typedef struct {
    char nome[256];
    int score_atual;
    int score_maximo;
} Jogador;

void cadastrar_jogador(Jogador **jogadores, const char *nome, int *qtd, int *capacidade);
void trocar_jogadores(Jogador *jogador1, Jogador *jogador2);
int particionar_vetor(Jogador **jogadores, int inicio, int fim);
void ordenar_jogadores(Jogador **jogadores, int inicio, int fim);
void exibir_ranking(const char *mensagem, Jogador *jogadores, int qtd);

#endif