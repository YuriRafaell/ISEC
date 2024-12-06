#ifndef TROCO_H
#define TROCO_H

// Define um limite de iterações para o algoritmo Trepa-Colinas
#define MAX_ITERACOES 1000

// Funções para leitura e manipulação de instância
void lerInstancia(const char *nomeArquivo, int *n, int *v, int **moedas);
void ordenarMoedasDecrescente(int *moedas, int n);

// Funções do algoritmo Trepa-Colinas
void gerarSolucaoInicial(int *solucao, int n, int *moedas, int v);
void gerarVizinho(int *solucao, int n, int *novaSolucao);
int calcularCusto(int *solucao, int n, int *moedas, int v);
void trepaColinas(int n, int v, int *moedas, int *melhorSolucao, int *melhorCusto);

#endif // TROCO_H
