#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/jogador.h"
#include "../include/utils.h"

bool salvar_dados(const char *caminho, Jogador *lista, int quantidade) {
    FILE *arquivo = fopen(caminho, "w");
    if (!arquivo) {
        printf("\nNao foi possivel abrir o arquivo!\n");
        aplicar_delay(1);
        return false;
    }
    fprintf(arquivo, "Nome,Score atual,Score maximo\n");
    for (int i = 0; i < quantidade; i++) {
        if (lista) fprintf(arquivo, "%s,%d,%d\n", lista[i].nome, lista[i].score_atual, lista[i].score_maximo);
    }
    fclose(arquivo);
    printf("\nDados de %d jogadores salvos em '%s' com sucesso!\n", quantidade, caminho);
    aplicar_delay(1);
    return true;
}

bool carregar_dados(const char *caminho, Jogador **lista, int *quantidade, int *capacidade) {
    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo) {
        printf("\nNao foi possivel abrir o arquivo!\n");
        aplicar_delay(1);
        return false;
    }
    fscanf(arquivo, "%*[^\n]\n");
    for (int i = 0;; i++) {
        if (*quantidade >= *capacidade) {
            *capacidade *= 2;
            Jogador *temp = realloc(*lista, (*capacidade)*sizeof(Jogador));
            if (!temp) {
                printf("\nErro ao realocar memoria!\n");
                aplicar_delay(1);
                fclose(arquivo);
                return false;
            }
            *lista = temp;
        }
        if (fscanf(arquivo, "%255[^,],%d,%d\n", (*lista)[i].nome, &(*lista)[i].score_atual, &(*lista)[i].score_maximo) != 3) break;
        (*quantidade)++;
    }
    fclose(arquivo);
    printf("\nDados de %d jogadores carregados de '%s' com sucesso!\n", (*quantidade), caminho);
    aplicar_delay(1);
    return true;
}