#ifndef RANKING_H
#define RANKING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os dados do jogador
struct {
    char nome[50]; // Nome do jogador
    int tempo;     // Tempo em segundos
} typedef Jogador;

// Constantes
#define MAX_JOGADORES 10  // Máximo de jogadores no ranking
#define RANKING_FILE "ranking.txt" // Nome do arquivo de ranking

// Funções para manipular o ranking
void lerRanking(Jogador ranking[], int *numJogadores); // Lê o ranking do arquivo
void salvarRanking(Jogador ranking[], int numJogadores); // Salva o ranking no arquivo
void exibirRanking(Jogador ranking[], int numJogadores); // Exibe o ranking no terminal
void atualizarRanking(Jogador ranking[], int *numJogadores, const char *nome, int tempo); // Atualiza o ranking com novo jogador

#endif // RANKING_H
