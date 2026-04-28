/* Programa que resolve recursivamente o problema do cavalo. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // Biblioteca para manipular diretórios

typedef struct st_reg {
	int linha, coluna, valor;
} registro;

// ... (as funções le_matriz, encontraPosInicial e cavalo permanecem as mesmas) ...

/* LC* matriz quadrada de inteiros de arquivo de texto. */
int **le_matriz(char *nome, int **M, int *N) {
	FILE *arq = fopen(nome, "r");
	if (!arq) return NULL;

	if (fscanf(arq, "%d", N) != 1) {
		fclose(arq);
		return NULL;
	}

	M = (int **)malloc((*N) * sizeof(int *));
	for (int i = 0; i < *N; i++) {
		M[i] = (int *)malloc((*N) * sizeof(int));
		for (int j = 0; j < *N; j++) {
			fscanf(arq, "%d", &M[i][j]);
		}
	}
	fclose(arq);
	return M;
}

void encontraPosInicial(registro *r, int **M, int N) {
	int max_v = -1;
	r->linha = 0; r->coluna = 0; r->valor = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (M[i][j] > max_v) {
				max_v = M[i][j];
				r->linha = i; r->coluna = j; r->valor = max_v;
			}
		}
	}
}

int cavalo(int** M, int N, int x, int y, int valor) {
	static const int plin[8] = { 2,  1, -1, -2, -2, -1,  1,  2};
	static const int pcol[8] = { 1,  2,  2,  1, -1, -2, -2, -1};
	if (valor == N * N) return 1;
	for (int i = 0; i < 8; i++) {
		int nx = x + plin[i];
		int ny = y + pcol[i];
		if (nx >= 0 && nx < N && ny >= 0 && ny < N && M[nx][ny] == 0) {
			M[nx][ny] = valor + 1;
			if (cavalo(M, N, nx, ny, valor + 1) == 1) return 1;
			M[nx][ny] = 0;
		}
	}
	return -1;
}

int main() {
	char nome_arquivo[100];
	char *arquivos[50]; // Suporta até 50 arquivos .txt na pasta
	int total_arquivos = 0;
	int escolha, i, j, st, tamanho = 0;
	int** M = NULL;
	int *N = &tamanho;

	// --- Lógica para listar arquivos .txt ---
	DIR *d;
	struct dirent *dir;
	d = opendir("."); // Abre a pasta atual
	if (d) {
		printf("Arquivos .txt encontrados:\n");
		while ((dir = readdir(d)) != NULL) {
			// Verifica se o arquivo termina com .txt
			char *extensao = strrchr(dir->d_name, '.');
			if (extensao && strcmp(extensao, ".txt") == 0) {
				arquivos[total_arquivos] = strdup(dir->d_name);
				printf("[%d] %s\n", total_arquivos + 1, arquivos[total_arquivos]);
				total_arquivos++;
			}
		}
		closedir(d);
	}

	if (total_arquivos == 0) {
		printf("Nenhum arquivo .txt encontrado na pasta.\n");
		return 1;
	}

	printf("\nSelecione o numero do arquivo: ");
	if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > total_arquivos) {
		printf("Selecao invalida.\n");
		return 1;
	}

	strcpy(nome_arquivo, arquivos[escolha - 1]);
	// ----------------------------------------

	M = le_matriz(nome_arquivo, M, N);
	if (!M) {
		printf("Erro ao ler matriz de %s.\n", nome_arquivo);
		return 1;
	}

	registro *r = (registro *)malloc(sizeof(registro));
	encontraPosInicial(r, M, *N);

	st = cavalo(M, *N, r->linha, r->coluna, r->valor);

	if (st > 0) printf("Solucao encontrada para %s:\n", nome_arquivo);
	else printf("\nNao ha solucao para %s:\n", nome_arquivo);

	for (i = 0; i < *N; ++i) {
		for (j = 0; j < *N; ++j) printf("%3d ", M[i][j]);
		printf("\n");
	}

	// Limpeza
	for (i = 0; i < *N; i++) free(M[i]);
	free(M);
	free(r);
	for (i = 0; i < total_arquivos; i++) free(arquivos[i]);

	return 0;
}
