#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/sistema.h"
#include "../include/campo_minado.h"
#include "../include/jogador.h"
#include "../include/jogos_utils.h"
#include "../include/utils.h"

void campo_minado(Jogador **jogadores, int *quantidade, int *capacidade, bool *ordenado) {
    char campo[N][N];
    bool tem_bomba[N][N];
    bool foi_escavado[N][N];
    Coordenadas bombas[N];
    int escavados = 0, marcados = 0;
    int jogadas = 1, remanescentes = N;
    bool venceu = true;
    char nome[256];
    aplicar_delay(1000);
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
            inicializar_mapa_bool(N, N, tem_bomba);
            inicializar_mapa_bool(N, N, foi_escavado);
            imprimir_campo(jogadas, remanescentes, campo, (*jogadores)[idx]);
            Coordenadas iniciais = ler_coordenadas("\nInsira as coordenadas iniciais desejadas:\n", N);
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
            aplicar_delay(1000);
            printf("\nPARABENS! Voce desarmou todas as bombas!\n\n");
            aplicar_delay(1000);
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
            aplicar_delay(1000);
            printf("\n");
            break;
        }
        Coordenadas atuais = ler_coordenadas("\nInsira as coordenadas desejadas:\n", N);
        if (foi_escavado[atuais.x][atuais.y]) {
            printf("\nBloco ja escavado\n(Entradas descartadas)\n");
            aplicar_delay(1000);
            continue;
        }
        switch (opcao) {
            case 1: {
                if (campo[atuais.x][atuais.y] == '*') {
                    printf("\nBloco marcado\n(Entradas descartadas)\n");
                    aplicar_delay(1000);
                    continue;
                }
                if (tem_bomba[atuais.x][atuais.y]) {
                    (*jogadores)[idx].score_atual = 0;
                    explodiu = true;
                    printf("\nKABOOM! Voce escavou uma bomba!\n");
                    aplicar_delay(1000);
                    limpar_tela();
                    marcar_bombas_remanescentes(bombas, campo, foi_escavado);
                    imprimir_campo(jogadas, remanescentes, campo, (*jogadores)[idx]);
                    aplicar_delay(1000);
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
    aplicar_delay(1000);
}