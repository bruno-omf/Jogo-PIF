#include <stdio.h>
#include <string.h>
#include "ranking.h"

Jogador ranking[MAX_JOGADORES];

void inicializarRanking() {
    for (int i = 0; i < MAX_JOGADORES; i++) {
        ranking[i].nome[0] = '\0'; // Define o nome como vazio
        ranking[i].tempo = -1;      // Define o tempo como -1 para indicar "não definido"
    }
}

void exibirRanking() {
    printf("Ranking dos 10 Melhores Tempos:\n");
    for (int i = 0; i < MAX_JOGADORES; i++) {
        // Verifica se o tempo é -1 e o nome está vazio
        if (ranking[i].tempo == -1 && ranking[i].nome[0] == '\0') {
            printf("%d. vazio\n", i + 1);
        } else {
            printf("%d. %s - %d segundos\n", i + 1, ranking[i].nome, ranking[i].tempo);
        }
    }
}

void atualizarRanking(Jogador jogador) {
    for (int i = 0; i < MAX_JOGADORES; i++) {
        if (ranking[i].tempo == -1 || jogador.tempo < ranking[i].tempo) {
            // Desloca os jogadores para baixo para dar lugar ao novo jogador
            for (int j = MAX_JOGADORES - 1; j > i; j--) {
                ranking[j] = ranking[j - 1];
            }
            ranking[i] = jogador; // Insere o novo jogador na posição correta
            break;
        }
    }
}
