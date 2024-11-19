#include "ranking.h"
#include "screen.h"

// Função para ler o ranking do arquivo
void lerRanking(Jogador ranking[], int *numJogadores) {
    FILE *file = fopen(RANKING_FILE, "r");
    if (!file) {
        // Arquivo não existe, inicializa vazio
        *numJogadores = 0;
        return;
    }

    // Lê os jogadores do arquivo
    *numJogadores = 0;
    while (fscanf(file, "%49[^:]:%d\n", ranking[*numJogadores].nome, &ranking[*numJogadores].tempo) == 2) {
        (*numJogadores)++;
        if (*numJogadores >= MAX_JOGADORES) break; // Limita ao máximo de jogadores
    }

    fclose(file);
}

// Função para salvar o ranking no arquivo
void salvarRanking(Jogador ranking[], int numJogadores) {
    FILE *file = fopen(RANKING_FILE, "w");
    if (!file) {
        perror("Erro ao abrir arquivo para salvar o ranking");
        return;
    }

    for (int i = 0; i < numJogadores; i++) {
        fprintf(file, "%s:%d\n", ranking[i].nome, ranking[i].tempo);
    }

    fclose(file);
}

// Função para exibir o ranking no terminal
void exibirRanking(Jogador ranking[], int numJogadores) {
    screenSetColor(YELLOW, BLACK);
    printf("RANKING:\n");
    for (int i = 0; i < numJogadores; i++) {
        printf("%d. %s - %ds\n", i + 1, ranking[i].nome, ranking[i].tempo);
    }
    printf("\n");
}

// Função para atualizar o ranking com um novo jogador
void atualizarRanking(Jogador ranking[], int *numJogadores, const char *nome, int tempo) {
    // Adiciona o novo jogador ao final
    if (*numJogadores < MAX_JOGADORES) {
        strcpy(ranking[*numJogadores].nome, nome);
        ranking[*numJogadores].tempo = tempo;
        (*numJogadores)++;
    } else if (tempo < ranking[*numJogadores - 1].tempo) {
        // Substitui o último jogador se o novo tempo for melhor
        strcpy(ranking[*numJogadores - 1].nome, nome);
        ranking[*numJogadores - 1].tempo = tempo;
    }

    // Ordena o ranking por tempo (menor tempo primeiro)
    for (int i = 0; i < *numJogadores - 1; i++) {
        for (int j = i + 1; j < *numJogadores; j++) {
            if (ranking[i].tempo > ranking[j].tempo) {
                Jogador temp = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = temp;
            }
        }
    }
}
