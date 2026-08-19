#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/sistema.h"
#include "../include/conecta_4.h"
#include "../include/jogador.h"
#include "../include/jogos_utils.h"
#include "../include/utils.h"

void conecta_4(Jogador **jogadores, int *quantidade, int *capacidade, bool *ordenado) {
    char grade[L][C];
    bool foi_marcado[L][C];
    int marcados = 0, jogadas = 1;
    char nome[256];
    aplicar_delay(1);
    int escolha1 = 0;
    if (*quantidade > 0) {
        for (int i = 0; i < *quantidade; i++) {
            if (i == 0) printf("\nEscolha uma das opcoes abaixo:\n\n");
            printf("%d. %s (MAX: %d || ATUAL: %d)\n", i + 1, (*jogadores)[i].nome, (*jogadores)[i].score_maximo, (*jogadores)[i].score_atual);
            if (i == *quantidade - 1) printf("0. Criar novo jogador\n");
        }
        escolha1 = ler_inteiro("\nEscolha uma das opcoes acima: ");
        while (escolha1 < 0 || escolha1 > *quantidade) {
            printf("\nOpcao invalida! Por favor, tente novamente\n");
            escolha1 = ler_inteiro("Escolha uma das opcoes acima: ");
        }
    }
    if (escolha1 == 0) {
        ler_string("\nInsira o nome do jogador: ", nome, 256);
        cadastrar_jogador(jogadores, nome, quantidade, capacidade);
    }
    int i1 = (escolha1 == 0) ? *quantidade - 1 : escolha1 - 1;
    printf("\nJogador %s selecionado!\n", (*jogadores)[i1].nome);
    aplicar_delay(1);
    limpar_tela();
    int escolha2 = 0;
    if (*quantidade > 1) {
        for (int i = 0; i < *quantidade; i++) {
            if (i == 0) printf("\nEscolha uma das opcoes abaixo:\n\n");
            printf("%d. %s (MAX: %d || ATUAL: %d)\n", i + 1, (*jogadores)[i].nome, (*jogadores)[i].score_maximo, (*jogadores)[i].score_atual);
            if (i == *quantidade - 1) printf("0. Criar novo jogador\n");
        }
        escolha2 = ler_inteiro("\nEscolha uma das opcoes acima: ");
        while (escolha2 < 0 || escolha2 > *quantidade || (escolha2 == escolha1 && escolha2 != 0)) {
            printf("\nOpcao invalida! Por favor, tente novamente\n");
            escolha2 = ler_inteiro("Escolha uma das opcoes acima: ");
        }
    }
     if (escolha2 == 0) {
        ler_string("\nInsira o nome do jogador: ", nome, 256);
        cadastrar_jogador(jogadores, nome, quantidade, capacidade);
    }
    int i2 = (escolha2 == 0) ? *quantidade - 1 : escolha2 - 1;
    printf("\nJogador %s selecionado!\n", (*jogadores)[i2].nome);
    aplicar_delay(1);
    limpar_tela();
    int moeda = rand() % 2;
    if (moeda == 0) trocar_valores(&i1, &i2);
    printf("\n1o jogador: %s ('X')\n2o jogador: %s ('O')\n", (*jogadores)[i1].nome, (*jogadores)[i2].nome);
    aplicar_delay(1);
    limpar_tela();
    inicializar_grade(grade);
    inicializar_mapa_bool(L, C, foi_marcado);
    while (1) {
        // Jogador 1
        limpar_tela();
        imprimir_grade(jogadas, grade, (*jogadores)[i1]);
        int coluna1 = ler_inteiro("\nInsira a coluna desejada: ");
        while (!soltar_peca(coluna1, 'X', grade, foi_marcado)) coluna1 = ler_inteiro("\nInsira a coluna desejada: ");
        marcados++;
        jogadas++;
        if (venceu_grade('X', grade)) {
            limpar_tela();
            imprimir_grade(jogadas, grade, (*jogadores)[i1]);
            aplicar_delay(1);
            printf("\nO jogador %s venceu a partida!\n\n", (*jogadores)[i1].nome);
            (*jogadores)[i1].score_atual += 2;
            if ((*jogadores)[i1].score_atual > (*jogadores)[i1].score_maximo) (*jogadores)[i1].score_maximo = (*jogadores)[i1].score_atual;
            break;
        }
        if (marcados == L * C) {
            limpar_tela();
            imprimir_grade(jogadas, grade, (*jogadores)[i1]);
            printf("\nGRADE CHEIA!\n");
            aplicar_delay(1);
            inicializar_grade(grade);
            inicializar_mapa_bool(L, C, foi_marcado);
            (*jogadores)[i1].score_atual++;
            if ((*jogadores)[i1].score_atual > (*jogadores)[i1].score_maximo) (*jogadores)[i1].score_maximo = (*jogadores)[i1].score_atual;
            (*jogadores)[i2].score_atual++;
            if ((*jogadores)[i2].score_atual > (*jogadores)[i2].score_maximo) (*jogadores)[i2].score_maximo = (*jogadores)[i2].score_atual;
            trocar_valores(&i1, &i2);
            marcados = 0;
            continue;
        }
        // Jogador 2
        limpar_tela();
        imprimir_grade(jogadas, grade, (*jogadores)[i2]);
        int coluna2 = ler_inteiro("\nInsira a coluna desejada: ");
        while (!soltar_peca(coluna2, 'O', grade, foi_marcado)) coluna2 = ler_inteiro("\nInsira a coluna desejada: ");
        marcados++;
        jogadas++;
        if (venceu_grade('O', grade)) {
            limpar_tela();
            imprimir_grade(jogadas, grade, (*jogadores)[i2]);
            aplicar_delay(1);
            printf("\nO jogador %s venceu a partida!\n\n", (*jogadores)[i2].nome);
            (*jogadores)[i2].score_atual += 2;
            if ((*jogadores)[i2].score_atual > (*jogadores)[i2].score_maximo) (*jogadores)[i2].score_maximo = (*jogadores)[i2].score_atual;
            break;
        }
        if (marcados == L * C) {
            limpar_tela();
            imprimir_grade(jogadas, grade, (*jogadores)[i2]);
            printf("\nGRADE CHEIA!\n");
            aplicar_delay(1);
            inicializar_grade(grade);
            inicializar_mapa_bool(L, C, foi_marcado);
            (*jogadores)[i1].score_atual++;
            if ((*jogadores)[i1].score_atual > (*jogadores)[i1].score_maximo) (*jogadores)[i1].score_maximo = (*jogadores)[i1].score_atual;
            (*jogadores)[i2].score_atual++;
            if ((*jogadores)[i2].score_atual > (*jogadores)[i2].score_maximo) (*jogadores)[i2].score_maximo = (*jogadores)[i2].score_atual;
            trocar_valores(&i1, &i2);
            marcados = 0;
            continue;
        }
    }
    aplicar_delay(1);
}