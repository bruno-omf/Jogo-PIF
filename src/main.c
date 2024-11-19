#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "ranking.h" 
#define ROWS 15
#define COLS 45

char labirinto[ROWS][COLS] = {
    "#############################################",
    "#      #      #     #   ### # ## ##   ###   #",
    "###### # #### ## ##  ## ##   ## # #   #     #",
    "#    # # #  #    #   #  #### ## ### # #     #",
    "#        #  ######## #  #  #   # ##   ## ####",
    "#    #####       ##  #       # ## # ###     #",
    "# #### #    ### #### # # ### ##  ## #       #",
    "#      # ##   #        #  ##  # ##  #  #  ###",
    "### ####    # ### ## ## #  #  #  ## #  ##   #",
    "##       #  # #      ## #### ##### # ##     #",
    "# ###### ## # ##   # #     #   #      ##### #",
    "#      ###  # #  ### # # ### #   # #        #",
    "#####  # # ##   #  # # #     ### ######  ## #",
    "#        #  ###   ###  ####    #            S",
    "#############################################"
};

int playerX = 1, playerY = 1;

void desenhaLabirinto() {
    int startX = (MAXX - COLS) / 2; 
    int startY = (MAXY - ROWS) / 2; 

    screenClear(); 
    screenInit(1);

    for (int i = 0; i < ROWS; i++) { 
        for (int j = 0; j < COLS; j++) {
            screenGotoxy(startX + j + 1, startY + i + 1); 
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


void moveJogador(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    if (labirinto[newY][newX] == ' ' || labirinto[newY][newX] == 'S') {
       
        if (labirinto[newY][newX] == 'S') {
            labirinto[playerY][playerX] = ' '; 
            playerX = newX;
            playerY = newY;
            return; 
        }

       
        labirinto[playerY][playerX] = ' ';
        playerX = newX;
        playerY = newY;
        labirinto[playerY][playerX] = 'J';
    }
}


int main() {
    static int ch;
    char nome[50];
    Jogador ranking[MAX_JOGADORES];
    int numJogadores = 0;
    int tempoJogo;

 
    lerRanking(ranking, &numJogadores);

   
    printf("Digite seu nome: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0'; 

 
    screenClear();
    exibirRanking(ranking, numJogadores);
    timerInit(5000); 
    while (!timerTimeOver());

   
    screenInit(1);    
    keyboardInit(); 
    timerInit(0); 
    desenhaLabirinto();

   
    while (1) {
       
        if (labirinto[playerY][playerX] == 'S') {
            tempoJogo = getTimeDiff() / 1000;

            
            screenGotoxy((MAXX - 30) / 2, MAXY - 2);
            screenSetColor(YELLOW, BLACK);
            printf("Parabéns! Você venceu o jogo em %d segundos!\n", tempoJogo);
            screenUpdate();

            atualizarRanking(ranking, &numJogadores, nome, tempoJogo);
            salvarRanking(ranking, numJogadores);


            screenClear();
            exibirRanking(ranking, numJogadores);

            
            timerInit(5000);
            while (!timerTimeOver());

           
            break;
        }


        if (keyhit()) {
            ch = readch();
            if (ch == 27) { 
                break;
            }
            switch (ch) {
                case 119: // 'w' minuculo
                case 87:  // 'W' maiusculo
                    moveJogador(0, -1); break; // Move para cima
                case 115: // 's' minuculo
                case 83:  // 'S' maiusculo
                    moveJogador(0, 1); break;  // Move para baixo
                case 97:  // 'a' minuculo
                case 65:  // 'A' maiusculo
                    moveJogador(-1, 0); break; // Move para esquerda
                case 100: // 'd' minuculo
                case 68:  // 'D' maiusculo
                    moveJogador(1, 0); break;  // Move para direita
            }
            desenhaLabirinto();
        }
    }

    keyboardDestroy(); 
    return 0;
}
