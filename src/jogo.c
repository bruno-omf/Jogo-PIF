#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "jogo.h"
#include <termios.h>

#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'

// Definindo as três fases do labirinto
char labirinto1[N][M] = {
    "##########",
    "#P       #",
    "# ###### #",
    "# #    # #",
    "# # ## # #",
    "# #    # #",
    "# ###### #",
    "#        #",
    "#      E #",
    "##########"
};

char labirinto2[N][M] = {
    "##########",
    "#P     # #",
    "### #### #",
    "#   #    #",
    "# ### ## #",
    "#   #    #",
    "# ### ####",
    "#        #",
    "#      E #",
    "##########"
};

char labirinto3[N][M] = {
    "##########",
    "#P     # #",
    "### ##   #",
    "#   #    #",
    "##### ## #",
    "#   #    #",
    "# #### ###",
    "#        #",
    "#      E #",
    "##########"
};

// Função para obter o labirinto correspondente à fase
char (*obterLabirinto(int fase))[M] {
    switch (fase) {
        case 1: return labirinto1;
        case 2: return labirinto2;
        case 3: return labirinto3;
        default: return NULL;
    }
}

// Função para exibir o labirinto atual
void exibirLabirinto(char labirinto[N][M]) {
    system("clear");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%c", labirinto[i][j]);
        }
        printf("\n");
    }
}

// Função para encontrar a posição inicial do jogador
void encontrarPosicaoInicial(char labirinto[N][M], int *x, int *y) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (labirinto[i][j] == 'P') {
                *x = i;
                *y = j;
                return;
            }
        }
    }
}

// Função para mover o jogador com base nas teclas do teclado
void moverJogador(char labirinto[N][M], int *x, int *y, int tecla) {
    int novoX = *x;
    int novoY = *y;

    if (tecla == KEY_UP) novoX--;
    else if (tecla == KEY_DOWN) novoX++;
    else if (tecla == KEY_LEFT) novoY--;
    else if (tecla == KEY_RIGHT) novoY++;

    // Verifica se a nova posição é um caminho livre ou a saída
    if (labirinto[novoX][novoY] == ' ' || labirinto[novoX][novoY] == 'E') {
        if (labirinto[*x][*y] != 'E') {
            labirinto[*x][*y] = ' ';
        }
        *x = novoX;
        *y = novoY;
        labirinto[*x][*y] = 'P';
    }
}

void configurarTerminal(int enable) {
    static struct termios oldt, newt;

    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt); // Salva configurações atuais
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // Desativa modo canônico e eco
        tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Aplica configurações
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restaura configurações
    }
}


// Função para executar cada fase do jogo
int executarFase(int fase) {
    char (*labirinto)[M] = obterLabirinto(fase);
    if (labirinto == NULL) {
        printf("Fase inválida!\n");
        return 0;
    }

    int saidaX = -1, saidaY = -1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (labirinto[i][j] == 'E') {
                saidaX = i;
                saidaY = j;
                printf("Saída `E` encontrada na posição (%d, %d) para a fase %d\n", saidaX, saidaY, fase);
                break;
            }
        }
    }

    int x, y;
    encontrarPosicaoInicial(labirinto, &x, &y);

    configurarTerminal(1); // Ativa o modo não canônico para capturar teclas sem Enter
    int tempoInicio = time(NULL);
    int tecla;
    bool faseCompleta = false;

    while (!faseCompleta) {
        exibirLabirinto(labirinto);
        
        tecla = getchar(); // Captura a entrada do usuário
        moverJogador(labirinto, &x, &y, tecla);

        if (x == saidaX && y == saidaY) {
            printf("Você encontrou a saída na fase %d!\n", fase);
            faseCompleta = true;
        }
    }

    configurarTerminal(0); // Restaura o terminal para o modo original

    int tempoFim = time(NULL);
    int tempoDecorrido = tempoFim - tempoInicio;

    printf("Parabéns! Você completou a fase %d em %d segundos!\n", fase, tempoDecorrido);
    sleep(2);

    return tempoDecorrido;
}




