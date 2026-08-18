# BLOCKDOM

## O que é?

Coleção de replicações de diversos jogos na linguagem C, contando com recursos nativos e bibliotecas auxiliares próprias da linguagem.

## Quais são os jogos?

- Campo minado (1 jogador)
- Jogo da velha (2 jogadores)
- Mais por vir...

## Quais outros recursos estão presentes?

- Armazenamento de jogadores para diferentes jogos
- Consulta de ranking de jogadores para cada jogo
- Persistência de jogadores em arquivos CSV

## O que você precisa?

- Sistema operacional Linux
- Compilador C (recomendado: GCC)
- Terminal para compilar e executar
- Git para clonar o repositório

## Como utilizar?

- Primeiramente, baixe ou clone o repositório para o ambiente local.

- Navegação ao diretório do programa:
```
cd blockdom/game
```
- Compilação via GCC:
```
gcc -I include src/*.c -o bin/main
```
- Execução:
```
./bin/main
```
- Se divirta.