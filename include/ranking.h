#ifndef RANKING_H
#define RANKING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct {
    char nome[50]; 
    int tempo;     
} typedef Jogador;

// Constantes
#define MAX_JOGADORES 20  
#define RANKING_FILE "ranking.txt" 


void lerRanking(Jogador ranking[], int *numJogadores); 
void salvarRanking(Jogador ranking[], int numJogadores); 
void exibirRanking(Jogador ranking[], int numJogadores); 
void atualizarRanking(Jogador ranking[], int *numJogadores, const char *nome, int tempo); 

#endif // RANKING_H
