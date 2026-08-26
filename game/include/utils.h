#ifndef UTILS_H
#define UTILS_H

void limpar_tela();
void aplicar_delay(int ms);
void imprimir_com_delay(const char *mensagem, int texto);
void limpar_buffer();
int ler_inteiro(const char *mensagem);
void ler_string(const char *mensagem, char *destino, int tamanho);
void converter_maiusculo(char *texto);
void trocar_valores(int *a, int *b);

#endif