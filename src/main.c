#include <stdio.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define MAX_NOME 50

int main() {
    char nomeJogador[MAX_NOME];
    int tempoTotal = 0;

    printf("Bem-vindo ao Labirinto!\n\n");
    printf("Digite seu nome para iniciar: ");
    fgets(nomeJogador, MAX_NOME, stdin);
    nomeJogador[strcspn(nomeJogador, "\n")] = '\0';

    printf("\nFase 1:\n");
    tempoTotal += executarFase(1);  // Executa a fase 1 e acumula o tempo

    printf("Fase 2:\n");
    tempoTotal += executarFase(2);  // Executa a fase 2 e acumula o tempo

    printf("Fase 3:\n");
    tempoTotal += executarFase(3);  // Executa a fase 3 e acumula o tempo

    printf("\nParabéns, %s! Você completou o jogo em %d segundos!\n", nomeJogador, tempoTotal);

    return 0;
}
