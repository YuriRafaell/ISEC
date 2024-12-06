#include "troco.h"
#include <stdio.h>
#include <stdlib.h>

// Lê a instância a partir de um arquivo
void lerInstancia(const char *nomeArquivo, int *n, int *v, int **moedas) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }

    // Lê o número de tipos de moedas e o valor a ser trocado
    fscanf(arquivo, "%d %d", n, v);

    // Aloca memória para o array de moedas
    *moedas = (int *)malloc(*n * sizeof(int));
    if (!*moedas) {
        fprintf(stderr, "Erro ao alocar memória para moedas\n");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }

    // Lê os valores das moedas
    for (int i = 0; i < *n; i++) {
        fscanf(arquivo, "%d", &(*moedas)[i]);
    }

    fclose(arquivo);
}

// Ordena o array de moedas em ordem decrescente
void ordenarMoedasDecrescente(int *moedas, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (moedas[i] < moedas[j]) {
                int temp = moedas[i];
                moedas[i] = moedas[j];
                moedas[j] = temp;
            }
        }
    }
}

// Gera uma solução inicial
void gerarSolucaoInicial(int *solucao, int n, int *moedas, int v) {
    for (int i = 0; i < n; i++) {
        solucao[i] = 0; // Inicializa todas as posições com 0
    }

    for (int i = 0; i < n; i++) {
        while (v >= moedas[i]) {
            v -= moedas[i];
            solucao[i]++;
        }
    }
}

// Gera um vizinho aleatório
void gerarVizinho(int *solucao, int n, int *novaSolucao) {
    for (int i = 0; i < n; i++) {
        novaSolucao[i] = solucao[i];
    }

    int pos = rand() % n; // Escolhe uma posição aleatória para alterar
    if (novaSolucao[pos] > 0) {
        novaSolucao[pos]--;
    }
}

// Calcula o custo de uma solução
int calcularCusto(int *solucao, int n, int *moedas, int v)
 {
    int soma = 0;
    for (int i = 0; i < n; i++) {
        soma += solucao[i] * moedas[i];
    }

    if (soma > v) {
        return -1; // Solução inválida
    }

    int numeroMoedas = 0;
    for (int i = 0; i < n; i++) {
        numeroMoedas += solucao[i];
    }

    return numeroMoedas;
}

// Implementa o algoritmo Trepa-Colinas
void trepaColinas(int n, int v, int *moedas, int *melhorSolucao, int *melhorCusto) {
    int solucaoAtual[n];
    gerarSolucaoInicial(solucaoAtual, n, moedas, v);

    for (int i = 0; i < n; i++) {
        melhorSolucao[i] = solucaoAtual[i];
    }

    *melhorCusto = calcularCusto(melhorSolucao, n, moedas, v);

    for (int iteracao = 0; iteracao < MAX_ITERACOES; iteracao++) {
        int novaSolucao[n];
        gerarVizinho(solucaoAtual, n, novaSolucao);

        int custoAtual = calcularCusto(solucaoAtual, n, moedas, v);
        int custoVizinho = calcularCusto(novaSolucao, n, moedas, v);

        if (custoVizinho >= 0 && custoVizinho < custoAtual) {
            for (int i = 0; i < n; i++) {
                solucaoAtual[i] = novaSolucao[i];
            }
        }

        int custoMelhor = calcularCusto(melhorSolucao, n, moedas, v);
        if (custoVizinho >= 0 && custoVizinho < custoMelhor) {
            for (int i = 0; i < n; i++) {
                melhorSolucao[i] = novaSolucao[i];
            }
            *melhorCusto = custoVizinho;
        }
    }
}
