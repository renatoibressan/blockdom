#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "../include/sistema.h"
#include "../include/campo_minado.h"
#include "../include/jogo_da_velha.h"
#include "../include/jogador.h"
#include "../include/arquivo.h"
#include "../include/jogos_utils.h"
#include "../include/utils.h"

void executar() {
    srand(time(NULL));
    limpar_tela();
    printf("\n============ BLOCKDOM ============\n");
    aplicar_delay(1);
    printf("\nDesenvolvido por Renato Bressan\n");
    aplicar_delay(1);
    limpar_tela();
    int jogos = 2;
    int capacidade[N], quantidade[N];
    bool ordenado[N];
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
    while (1) {
        bool encerrado = false;
        int idx = -1;
        limpar_tela();
        aplicar_delay(1);
        printf("\nExecutar:\n1. MINESWEEPER (1P)\n2. TIC-TAC-TOE (2P)\n");
        printf("\nConsultar ranking:\n3. MINESWEEPER\n4. TIC-TAC-TOE\n");
        printf("\nOutros:\n0. Encerrar o jogo\n");
        int jogo = ler_inteiro("Escolha uma das opcoes acima: ");
        switch (jogo) {
            case 1: {
                printf("\nIniciando MINESWEEPER...\n");
                aplicar_delay(1);
                printf("\n");
                limpar_tela();
                idx = 0;
                campo_minado(&jogadores[idx], &quantidade[idx], &capacidade[idx], &ordenado[idx]);
                break;
            }
            case 2: {
                printf("\nIniciando TIC-TAC-TOE...\n");
                aplicar_delay(1);
                printf("\n");
                limpar_tela();
                idx = 1;
                jogo_da_velha(&jogadores[idx], &quantidade[idx], &capacidade[idx], &ordenado[idx]);
                break;
            }
            case 3: {
                printf("\nAbrindo ranking de MINESWEEPER...\n");
                aplicar_delay(1);
                printf("\n");
                limpar_tela();
                idx = 0;
                consultar_ranking(&jogadores[idx], quantidade[idx], &ordenado[idx]);
                break;
            }
            case 4: {
                printf("\nAbrindo ranking de TIC-TAC-TOE...\n");
                aplicar_delay(1);
                printf("\n");
                limpar_tela();
                idx = 1;
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
            printf("\nSaindo do jogo...\n");
            aplicar_delay(1);
            printf("\n");
            break;
        }
    }
    limpar_tela();
    salvar_dados("data/campominado.csv", jogadores[0], quantidade[0]);
    salvar_dados("data/jogodavelha.csv", jogadores[1], quantidade[1]);
    printf("\n");
    for (int i = 0; i < jogos; i++) {
        free(jogadores[i]);
    }
    free(jogadores);
}

void campo_minado(Jogador **jogadores, int *quantidade, int *capacidade, bool *ordenado) {
    char campo[N][N];
    bool tem_bomba[N][N];
    bool foi_escavado[N][N];
    Coordenadas bombas[N];
    int escavados = 0, marcados = 0;
    int jogadas = 1, remanescentes = N;
    bool venceu = true;
    char nome[256];
    aplicar_delay(1);
    int escolha = 0;
    if (*quantidade > 0) {
        for (int i = 0; i < *quantidade; i++) {
            if (i == 0) printf("\nEscolha uma das opcoes abaixo:\n\n");
            printf("%d. %s (MAX: %d || ATUAL: %d)\n", i + 1, (*jogadores)[i].nome, (*jogadores)[i].score_maximo, (*jogadores)[i].score_atual);
            if (i == *quantidade - 1) printf("0. Criar novo jogador\n");
        }
        escolha = ler_inteiro("\nEscolha uma das opcoes acima: ");
        while (escolha < 0 || escolha > *quantidade) {
            printf("\nOpcao invalida! Por favor, tente novamente\n");
            escolha = ler_inteiro("Escolha uma das opcoes acima: ");
        }
    }
    if (escolha == 0) {
        ler_string("\nInsira o nome do jogador: ", nome, 256);
        cadastrar_jogador(jogadores, nome, quantidade, capacidade);
    }
    int idx = (escolha == 0) ? *quantidade - 1 : escolha - 1;
    while (1) {
        limpar_tela();
        if (venceu) {
            escavados = 0;
            marcados = 0;
            jogadas = 1;
            remanescentes = N;
            inicializar_campo(campo);
            inicializar_mapa_bool(N, tem_bomba);
            inicializar_mapa_bool(N, foi_escavado);
            imprimir_campo(jogadas, remanescentes, campo, (*jogadores)[idx]);
            Coordenadas iniciais = ler_coordenadas("\nInsira as coordenadas iniciais desejadas:\n");
            inicializar_bombas(iniciais, bombas, tem_bomba);
            modificar_campo(iniciais, tem_bomba, foi_escavado, campo, &escavados);
            foi_escavado[iniciais.x][iniciais.y] = true;
        }
        limpar_tela();
        venceu = false;
        bool explodiu = false;
        if (escavados == N * N - N) {
            remanescentes = 0;
            (*jogadores)[idx].score_atual++;
            if ((*jogadores)[idx].score_atual > (*jogadores)[idx].score_maximo) (*jogadores)[idx].score_maximo = (*jogadores)[idx].score_atual;
            marcar_bombas_remanescentes(bombas, campo, foi_escavado);
            imprimir_campo(jogadas, remanescentes, campo, (*jogadores)[idx]);
            aplicar_delay(1);
            printf("\nPARABENS! Voce desarmou todas as bombas!\n\n");
            aplicar_delay(1);
            venceu = true;
            continue;
        }
        imprimir_campo(jogadas, remanescentes, campo, (*jogadores)[idx]);
        printf("\n1. Escavar bloco\n2. Marcar/desmarcar bomba\n0. Sair do jogo\n");
        int opcao = ler_inteiro("Selecione uma das opcoes acima: ");
        while (opcao < 0 || opcao > 2) {
            printf("Opcao invalida! Por favor, tente novamente\n\n1. Escavar bloco\n2. Marcar/desmarcar bomba\n0. Sair do jogo\n");
            opcao = ler_inteiro("Selecione uma das opcoes acima: ");
        }
        if (opcao == 0) {
            printf("\nSaindo do jogo...\n");
            aplicar_delay(1);
            printf("\n");
            break;
        }
        Coordenadas atuais = ler_coordenadas("\nInsira as coordenadas desejadas:\n");
        if (foi_escavado[atuais.x][atuais.y]) {
            printf("\nBloco ja escavado\n(Entradas descartadas)\n");
            aplicar_delay(1);
            continue;
        }
        switch (opcao) {
            case 1: {
                if (campo[atuais.x][atuais.y] == '*') {
                    printf("\nBloco marcado\n(Entradas descartadas)\n");
                    aplicar_delay(1);
                    continue;
                }
                if (tem_bomba[atuais.x][atuais.y]) {
                    (*jogadores)[idx].score_atual = 0;
                    explodiu = true;
                    printf("\nKABOOM! Voce escavou uma bomba!\n");
                    aplicar_delay(1);
                    limpar_tela();
                    marcar_bombas_remanescentes(bombas, campo, foi_escavado);
                    imprimir_campo(jogadas, remanescentes, campo, (*jogadores)[idx]);
                    aplicar_delay(1);
                    imprimir_bombas(bombas);
                    break;
                }
                modificar_campo(atuais, tem_bomba, foi_escavado, campo, &escavados);
                jogadas++;
                break;
            }
            case 2: {
                if (campo[atuais.x][atuais.y] == '.') {
                    campo[atuais.x][atuais.y] = '*';
                    marcados++;
                    if (remanescentes > 0) remanescentes--;
                    jogadas++;
                } else {
                    campo[atuais.x][atuais.y] = '.';
                    if (marcados > 0) {
                        marcados--;
                        if (marcados < N) remanescentes++;
                    }
                }
                break;
            }
        }
        if (explodiu) break;
    }
    aplicar_delay(1);
}

void jogo_da_velha(Jogador **jogadores, int *quantidade, int *capacidade, bool *ordenado) {
    char tabuleiro[M][M];
    bool foi_marcado[M][M];
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
    inicializar_tabuleiro(tabuleiro);
    inicializar_mapa_bool(M, foi_marcado);
    while (1) {
        // Jogador 1
        limpar_tela();
        imprimir_tabuleiro(jogadas, tabuleiro, (*jogadores)[i1]);
        Coordenadas c1 = ler_coordenadas("\nInsira as coordenadas desejadas:\n");
        while (foi_marcado[c1.x][c1.y]) {
            printf("Bloco ja marcado\n(Entradas descartadas)\n");
            c1 = ler_coordenadas("\nInsira as coordenadas desejadas:\n");
        }
        tabuleiro[c1.x][c1.y] = 'X';
        foi_marcado[c1.x][c1.y] = true;
        marcados++;
        jogadas++;
        if (venceu_partida('X', tabuleiro)) {
            limpar_tela();
            imprimir_tabuleiro(jogadas, tabuleiro, (*jogadores)[i1]);
            aplicar_delay(1);
            printf("\nO jogador %s venceu a partida!\n\n", (*jogadores)[i1].nome);
            (*jogadores)[i1].score_atual += 2;
            if ((*jogadores)[i1].score_atual > (*jogadores)[i1].score_maximo) (*jogadores)[i1].score_maximo = (*jogadores)[i1].score_atual;
            break;
        }
        if (marcados == M * M) {
            limpar_tela();
            imprimir_tabuleiro(jogadas, tabuleiro, (*jogadores)[i1]);
            printf("\nVELHA!\n");
            aplicar_delay(1);
            inicializar_tabuleiro(tabuleiro);
            inicializar_mapa_bool(M, foi_marcado);
            (*jogadores)[i1].score_atual++;
            if ((*jogadores)[i1].score_atual > (*jogadores)[i1].score_maximo) (*jogadores)[i1].score_maximo = (*jogadores)[i1].score_atual;
            (*jogadores)[i2].score_atual++;
            if ((*jogadores)[i2].score_atual > (*jogadores)[i2].score_maximo) (*jogadores)[i2].score_maximo = (*jogadores)[i2].score_atual;
            trocar_valores(&i1, &i2);
            marcados = 0;
        }
        // Jogador 2
        limpar_tela();
        imprimir_tabuleiro(jogadas, tabuleiro, (*jogadores)[i2]);
        Coordenadas c2 = ler_coordenadas("\nInsira as coordenadas desejadas:\n");
        while (foi_marcado[c2.x][c2.y]) {
            printf("Bloco ja marcado\n(Entradas descartadas)\n");
            c2 = ler_coordenadas("\nInsira as coordenadas desejadas:\n");
        }
        tabuleiro[c2.x][c2.y] = 'O';
        foi_marcado[c2.x][c2.y] = true;
        marcados++;
        jogadas++;
        if (venceu_partida('O', tabuleiro)) {
            limpar_tela();
            imprimir_tabuleiro(jogadas, tabuleiro, (*jogadores)[i2]);
            aplicar_delay(1);
            printf("\nO jogador %s venceu a partida!\n\n", (*jogadores)[i2].nome);
            (*jogadores)[i2].score_atual += 2;
            if ((*jogadores)[i2].score_atual > (*jogadores)[i2].score_maximo) (*jogadores)[i2].score_maximo = (*jogadores)[i2].score_atual;
            break;
        }
        if (marcados == M * M) {
            limpar_tela();
            imprimir_tabuleiro(jogadas, tabuleiro, (*jogadores)[i2]);
            printf("\nVELHA!\n");
            aplicar_delay(1);
            inicializar_tabuleiro(tabuleiro);
            inicializar_mapa_bool(M, foi_marcado);
            (*jogadores)[i1].score_atual++;
            if ((*jogadores)[i1].score_atual > (*jogadores)[i1].score_maximo) (*jogadores)[i1].score_maximo = (*jogadores)[i1].score_atual;
            (*jogadores)[i2].score_atual++;
            if ((*jogadores)[i2].score_atual > (*jogadores)[i2].score_maximo) (*jogadores)[i2].score_maximo = (*jogadores)[i2].score_atual;
            trocar_valores(&i1, &i2);
            marcados = 0;
        }
    }
    aplicar_delay(1);
}

void consultar_ranking(Jogador **jogadores, int quantidade, bool *ordenado) {
    if (!(*ordenado)) {
        ordenar_jogadores(jogadores, 0, quantidade - 1);
        *ordenado = true;
    }
    exibir_ranking("RANKING ATUAL:\n", *jogadores, quantidade);
    aplicar_delay(1);
}