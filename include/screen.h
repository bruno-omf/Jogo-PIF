#ifndef SCREEN_H
#define SCREEN_H

#define N 10
#define M 10
#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'

int executarFase(int fase);


void exibirLabirinto(char labirinto[N][M]);
void encontrarPosicaoInicial(char labirinto[N][M], int *x, int *y);
void moverJogador(char labirinto[N][M], int *x, int *y, int tecla);
char (*obterLabirinto(int fase))[M];
int executarFase(int fase);

#endif // SCREEN_H
