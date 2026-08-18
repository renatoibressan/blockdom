#ifndef UTILS_H
#define UTILS_H

void aplicar_delay(int s);
void limpar_tela();
void limpar_buffer();
int ler_inteiro(const char *mensagem);
void ler_string(const char *mensagem, char *destino, int tamanho);
void converter_maiusculo(char *texto);
void trocar_valores(int *a, int *b);

#endif