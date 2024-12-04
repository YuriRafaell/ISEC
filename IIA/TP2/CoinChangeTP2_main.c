#include <stdio.h>
#include <stdlib.h>

void lerInstancia(const char *nomeArquivo, int *n, double *v, double **moedas) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fscanf(arquivo, "%d %lf", n, v);
    *moedas = (double *)malloc((*n) * sizeof(double));

    for (int i = 0; i < *n; i++) {
        fscanf(arquivo, "%lf", &(*moedas)[i]);
    }

    fclose(arquivo);
}

void resolverTroco(int n, double v, double *moedas, int *solucao, int *totalMoedas) {
    double restante = v;
    *totalMoedas = 0;

    for (int i = 0; i < n; i++) {
        solucao[i] = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (moedas[j] < moedas[j + 1]) {
                double temp = moedas[j];
                moedas[j] = moedas[j + 1];
                moedas[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        while (restante >= moedas[i]) {
            restante -= moedas[i];
            solucao[i]++;
            (*totalMoedas)++;
        }
    }

    if (restante > 0.0001) {
        printf("Não foi possível encontrar uma solução válida.\n");
    }
}

int main() {
    int n;
    double v;
    double *moedas;
    int *solucao;
    int totalMoedas;

    lerInstancia("file1.txt", &n, &v, &moedas);

    solucao = (int *)malloc(n * sizeof(int));
    resolverTroco(n, v, moedas, solucao, &totalMoedas);

    printf("Solução encontrada:\n");
    for (int i = 0; i < n; i++) {
        printf("Moeda de %.2lf: %d\n", moedas[i], solucao[i]);
    }
    printf("Número total de moedas: %d\n", totalMoedas);

    free(moedas);
    free(solucao);

    return 0;
}
