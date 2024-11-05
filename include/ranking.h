#ifndef RANKING_H
#define RANKING_H

#define MAX_JOGADORES 10
#define MAX_NOME 20

// Estrutura do jogador com nome e tempo
typedef struct {
    char nome[MAX_NOME];
    int tempo;
} Jogador;

// Funções para inicializar, exibir e atualizar o ranking
void inicializarRanking();
void exibirRanking();
void atualizarRanking(Jogador jogador);

#endif // RANKING_H