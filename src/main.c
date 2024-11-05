#include <stdio.h>
#include <string.h>
#include "ranking.h"
#include "jogo.h"

int main() {
    char nomeJogador[MAX_NOME];
    int tempoTotal = 0;

    // Inicializa o ranking antes de começar o jogo
    inicializarRanking();

    printf("Bem-vindo ao Labirinto!!\n\n");
    
    // Exibe o ranking atual antes de pedir o nome do jogador
    exibirRanking();

    printf("\nDigite seu nome para iniciar: ");
    fgets(nomeJogador, MAX_NOME, stdin);
    nomeJogador[strcspn(nomeJogador, "\n")] = '\0';

    Jogador jogadorAtual;
    strcpy(jogadorAtual.nome, nomeJogador);

    // Inicia o jogo e soma os tempos das fases
    printf("\nFase 1:\n");
    tempoTotal += executarFase(1);

    printf("Fase 2:\n");
    tempoTotal += executarFase(2);

    printf("Fase 3:\n");
    tempoTotal += executarFase(3);

    // Atualiza o tempo total do jogador e insere no ranking
    jogadorAtual.tempo = tempoTotal;
    atualizarRanking(jogadorAtual);

    printf("\nParabéns, %s! Você completou o jogo em %d segundos!\n", jogadorAtual.nome, tempoTotal);

    // Exibe o ranking atualizado ao final do jogo
    exibirRanking();

    return 0;
}
