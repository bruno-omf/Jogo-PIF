#include "ranking.h"
#include "screen.h"

void lerRanking(Jogador ranking[], int *numJogadores) {
    FILE *file = fopen(RANKING_FILE, "r");
    if (!file) {
        *numJogadores = 0;
        return;
    }

    *numJogadores = 0;
    while (fscanf(file, "%49[^:]:%d\n", ranking[*numJogadores].nome, &ranking[*numJogadores].tempo) == 2) {
        (*numJogadores)++;
        if (*numJogadores >= MAX_JOGADORES) break; 
    }

    fclose(file);
}


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


void exibirRanking(Jogador ranking[], int numJogadores) {
    screenSetColor(YELLOW, BLACK);
    printf("RANKING:\n");
    for (int i = 0; i < numJogadores; i++) {
        printf("%d. %s - %ds\n", i + 1, ranking[i].nome, ranking[i].tempo);
    }
    printf("\n");
}


void atualizarRanking(Jogador ranking[], int *numJogadores, const char *nome, int tempo) {

    if (*numJogadores < MAX_JOGADORES) {
        strcpy(ranking[*numJogadores].nome, nome);
        ranking[*numJogadores].tempo = tempo;
        (*numJogadores)++;
    } else if (tempo < ranking[*numJogadores - 1].tempo) {
       
        strcpy(ranking[*numJogadores - 1].nome, nome);
        ranking[*numJogadores - 1].tempo = tempo;
    }

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
