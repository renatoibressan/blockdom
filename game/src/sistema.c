#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../include/sistema.h"
#include "../include/campo_minado.h"
#include "../include/jogo_da_velha.h"
#include "../include/conecta_4.h"
#include "../include/jogador.h"
#include "../include/arquivo.h"
#include "../include/jogos_utils.h"
#include "../include/utils.h"

void executar() {
    srand(time(NULL));
    limpar_tela();
    aplicar_delay(1000);
    printf("\n================== BLOCKDOM ==================\n");
    aplicar_delay(1000);
    printf("\nDesenvolvido por Renato Ikeda Bressan\n");
    aplicar_delay(1000);
    limpar_tela();
    int jogos = 3;
    int capacidade[T], quantidade[T];
    bool ordenado[T];
    inicializar_vetor(capacidade, jogos, 10);
    inicializar_vetor(quantidade, jogos, 0);
    inicializar_vetor_bool(ordenado, jogos, false);
    Jogador **jogadores = (Jogador **)malloc(jogos*sizeof(Jogador *));
    if (!jogadores) {
        printf("\nErro ao alocar memoria!\n");
        return;
    }
    for (int i = 0; i < jogos; i++) {
        jogadores[i] = (Jogador *)malloc(capacidade[i]*sizeof(Jogador));
    }
    carregar_dados("data/campominado.csv", &jogadores[0], &quantidade[0], &capacidade[0]);
    carregar_dados("data/jogodavelha.csv", &jogadores[1], &quantidade[1], &capacidade[1]);
    carregar_dados("data/conecta4.csv", &jogadores[2], &quantidade[2], &capacidade[2]);
    while (1) {
        bool encerrado = false;
        int idx = -1;
        limpar_tela();
        aplicar_delay(1000);
        printf("\nExecutar:\n1. MINESWEEPER (1P)\n2. TIC-TAC-TOE (2P)\n3. CONNECT-4 (2P)\n");
        printf("\nConsultar ranking:\n4. MINESWEEPER\n5. TIC-TAC-TOE\n6. CONNECT-4\n");
        printf("\nOutros:\n0. Encerrar o jogo\n");
        int jogo = ler_inteiro("\nEscolha uma das opcoes acima: ");
        switch (jogo) {
            case 1: {
                printf("\nIniciando MINESWEEPER");
                imprimir_com_delay("...", 500);
                printf("\n");
                limpar_tela();
                idx = 0;
                campo_minado(&jogadores[idx], &quantidade[idx], &capacidade[idx], &ordenado[idx]);
                break;
            }
            case 2: {
                printf("\nIniciando TIC-TAC-TOE");
                imprimir_com_delay("...", 500);
                printf("\n");
                limpar_tela();
                idx = 1;
                jogo_da_velha(&jogadores[idx], &quantidade[idx], &capacidade[idx], &ordenado[idx]);
                break;
            }
            case 3: {
                printf("\nIniciando CONNECT-4");
                imprimir_com_delay("...", 500);
                printf("\n");
                limpar_tela();
                idx = 2;
                conecta_4(&jogadores[idx], &quantidade[idx], &capacidade[idx], &ordenado[idx]);
                break;
            }
            case 4: {
                printf("\nAbrindo ranking de MINESWEEPER");
                imprimir_com_delay("...", 500);
                printf("\n");
                limpar_tela();
                idx = 0;
                consultar_ranking(&jogadores[idx], quantidade[idx], &ordenado[idx]);
                break;
            }
            case 5: {
                printf("\nAbrindo ranking de TIC-TAC-TOE");
                imprimir_com_delay("...", 500);
                printf("\n");
                limpar_tela();
                idx = 1;
                consultar_ranking(&jogadores[idx], quantidade[idx], &ordenado[idx]);
                break;
            }
            case 6: {
                printf("\nAbrindo ranking de CONNECT-4");
                imprimir_com_delay("...", 500);
                printf("\n");
                limpar_tela();
                idx = 2;
                consultar_ranking(&jogadores[idx], quantidade[idx], &ordenado[idx]);
                break;
            }
            case 0: {
                encerrado = true;
                break;
            }
            default: { 
                printf("Opcao invalida!\nPor favor, tente novamente\n");
                continue; 
            }
        }
        if (encerrado) {
            printf("\nSaindo do jogo");
            imprimir_com_delay("...", 500);
            printf("\n");
            break;
        }
    }
    limpar_tela();
    for (int i = 0; i < jogos; i++) {
        if (!ordenado[i]) {
            ordenar_jogadores(&jogadores[i], 0, quantidade[i] - 1);
            ordenado[i] = true;
        }
    }
    salvar_dados("data/campominado.csv", jogadores[0], quantidade[0]);
    salvar_dados("data/jogodavelha.csv", jogadores[1], quantidade[1]);
    salvar_dados("data/conecta4.csv", jogadores[2], quantidade[2]);
    aplicar_delay(1000);
    limpar_tela();
    for (int i = 0; i < jogos; i++) {
        free(jogadores[i]);
    }
    free(jogadores);
}

void consultar_ranking(Jogador **jogadores, int quantidade, bool *ordenado) {
    if (!(*ordenado)) {
        ordenar_jogadores(jogadores, 0, quantidade - 1);
        *ordenado = true;
    }
    exibir_ranking("RANKING ATUAL:\n", *jogadores, quantidade);
    aplicar_delay(1000);
}