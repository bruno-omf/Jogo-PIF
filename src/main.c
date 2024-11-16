#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "ranking.h" // Inclui o sistema de ranking

// Dimensões do labirinto
#define ROWS 15
#define COLS 45

// Representação do labirinto
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

// Posição inicial do jogador
int playerX = 1, playerY = 1;

// Função para desenhar o labirinto
void desenhaLabirinto() {
    int startX = (MAXX - COLS) / 2; // Centraliza horizontalmente
    int startY = (MAXY - ROWS) / 2; // Centraliza verticalmente

    screenClear();
    screenInit(1); // Reexibe as bordas
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
        // Verifica se a nova posição é a saída antes de atualizar o jogador
        if (labirinto[newY][newX] == 'S') {
            labirinto[playerY][playerX] = ' '; // Remove o jogador da posição atual
            playerX = newX;
            playerY = newY;
            return; // Sai da função; o jogo será encerrado no loop principal
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
    char nome[50];
    Jogador ranking[MAX_JOGADORES];
    int numJogadores = 0;
    int tempoJogo;

    // Leitura do ranking do arquivo
    lerRanking(ranking, &numJogadores);

    // Solicita o nome do jogador
    printf("Digite seu nome: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove o caractere de nova linha

    // Exibe o ranking atual
    screenClear();
    exibirRanking(ranking, numJogadores);
    timerInit(5000); // Exibe por 5 segundos
    while (!timerTimeOver());

    // Inicializa o labirinto
    screenInit(1);     // Inicializa a tela com bordas
    keyboardInit();    // Inicializa o teclado
    timerInit(50);     // Inicializa o timer para o jogo
    desenhaLabirinto();
    timerInit(0);      // Inicia o cronômetro do jogo

    // Loop principal do jogo
    while (1) {
        // Checa se o jogador chegou à saída
        if (labirinto[playerY][playerX] == 'S') {
            tempoJogo = getTimeDiff() / 1000; // Calcula o tempo em segundos
            screenGotoxy((MAXX - 30) / 2, MAXY - 2);
            screenSetColor(YELLOW, BLACK);
            printf("Parabéns! Você venceu o jogo em %d segundos!\n", tempoJogo);
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

    // Atualiza e salva o ranking
    atualizarRanking(ranking, &numJogadores, nome, tempoJogo);
    salvarRanking(ranking, numJogadores);

    keyboardDestroy(); // Restaura o teclado

    return 0;
}
