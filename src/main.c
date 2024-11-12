
#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

// Dimensões do labirinto
#define ROWS 10
#define COLS 20

// Representação do labirinto
char labirinto[ROWS][COLS] = {
    "###################",
    "#J               S#",
    "# ####  #  ####   #",
    "# #     #     #   #",
    "# #  #####  ###   #",
    "# #        ####   #",
    "# #######     #   #",
    "#       #######   #",
    "#           #     #",
    "###################"
};

// Posição inicial do jogador
int playerX = 1, playerY = 1;

// Função para desenhar o labirinto
void desenhaLabirinto() {
    int startX = (MAXX - COLS) / 2; // Centraliza horizontalmente
    int startY = (MAXY - ROWS) / 2; // Centraliza verticalmente

    screenClear();
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            screenGotoxy(startX + j + 1, startY + i + 1); // Adiciona o deslocamento
            if (labirinto[i][j] == '#') {
                screenSetColor(WHITE, BLACK);
            } else if (labirinto[i][j] == 'J') {
                screenSetColor(YELLOW, BLACK);
            } else if (labirinto[i][j] == 'S') {
                screenSetColor(GREEN, BLACK);
            } else {
                screenSetColor(LIGHTGRAY, BLACK);
            }
            printf("%c", labirinto[i][j]);
        }
    }
    screenUpdate();
}

// Função para mover o jogador
void moveJogador(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    // Verifica se a nova posição é válida
    if (labirinto[newY][newX] == ' ' || labirinto[newY][newX] == 'S') {
        // Verifica se a nova posição é um espaço vazio ou a saída
        if (labirinto[newY][newX] == 'S') {
            labirinto[playerY][playerX] = ' ';
            playerX = newX;
            playerY = newY;
            return; // Sai da função    
        }

        // Atualiza a posição do jogador
        labirinto[playerY][playerX] = ' ';
        playerX = newX;
        playerY = newY;
        labirinto[playerY][playerX] = 'J';
    }
}

// Função principal
int main() {
    static int ch;

    screenInit(1);     // Inicializa a tela com bordas
    keyboardInit();    // Inicializa o teclado
    timerInit(50);     // Inicializa o timer com 50ms

    desenhaLabirinto();

    while (1) {
        // Checa se o jogador chegou à saída
        if (labirinto[playerY][playerX] == 'S') {
            screenGotoxy(1, ROWS + 2);
            screenSetColor(YELLOW, BLACK);
            printf("Parabéns! Você venceu o jogo!!!!!!!!!!!!!\n");
            screenUpdate();
            break;
        }

        // Captura a entrada do teclado
        if (keyhit()) {
            ch = readch();
            if (ch == 27) { // ESC para sair do jogo
                break;
            }
            switch (ch) {
                case 'w': moveJogador(0, -1); break; // Move para cima
                case 's': moveJogador(0, 1); break;  // Move para baixo
                case 'a': moveJogador(-1, 0); break; // Move para esquerda
                case 'd': moveJogador(1, 0); break;  // Move para direita
            }
            desenhaLabirinto();
        }
    }

    keyboardDestroy(); // Restaura o teclado
    //screenDestroy();   // Restaura a tela

    return 0;
}