#ifndef JOGO_H
#define JOGO_H

#define N 10
#define M 10

// Declaração das funções usadas em jogo.c
char (*obterLabirinto(int fase))[M];
void exibirLabirinto(char labirinto[N][M]);
void encontrarPosicaoInicial(char labirinto[N][M], int *x, int *y);
void moverJogador(char labirinto[N][M], int *x, int *y, int tecla);
int executarFase(int fase);

#endif // JOGO_H
