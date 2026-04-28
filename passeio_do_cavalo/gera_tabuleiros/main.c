#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, startL, startC;
    char nome_arquivo[100];

    printf("--- Gerador de Tabuleiro para o Cavalo ---\n");
    
    // Entrada do tamanho
    printf("Digite o tamanho do tabuleiro (N x N): ");
    scanf("%d", &N);

    // Entrada da posição inicial (1-indexado para facilitar ao usuário, ou 0-indexado)
    printf("Digite a linha inicial (0 a %d): ", N - 1);
    scanf("%d", &startL);
    printf("Digite a coluna inicial (0 a %d): ", N - 1);
    scanf("%d", &startC);

    // Nome do arquivo
    sprintf(nome_arquivo, "tabuleiro_%dx%d_pos_%d_%d.txt", N, N, startL, startC);

    FILE *arq = fopen(nome_arquivo, "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }

    // Grava o tamanho N na primeira linha (conforme esperado pelo seu programa)
    fprintf(arq, "%d\n", N);

    // Gera a matriz com '1' na posição escolhida e '0' no restante
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == startL && j == startC) {
                fprintf(arq, "1 ");
            } else {
                fprintf(arq, "0 ");
            }
        }
        fprintf(arq, "\n");
    }

    fclose(arq);

    printf("\nSucesso! Arquivo '%s' gerado.\n", nome_arquivo);
    printf("Agora voce pode rodar o programa principal e seleciona-lo.\n");

    return 0;
}
