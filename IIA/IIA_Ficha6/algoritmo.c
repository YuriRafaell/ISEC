#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

// Gera um vizinho
// Parametros: solucao actual, vizinho, numero de vertices
// swap two vertices
void gera_vizinho(int a[], int b[], int n)
{
    int i, p1, p2;

    for (i = 0; i < n; i++)
        b[i] = a[i];
    // Encontra posicao com valor 0
    do
        p1 = random_l_h(0, n - 1);
    while (b[p1] != 0);
    // Encontra posicao com valor 0
    do
        p2 = random_l_h(0, n - 1);
    while (b[p2] != 1);
    // Troca
    b[p1] = 1;
    b[p2] = 0;
}

// Trepa colinas first-choice
// Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
// Devolve o custo da melhor solucao encontrada
int recristalizacao(int sol[], int *mat, int vert, int num_iter, float tMax, float tMin, float alpha)
{
    int *nova_sol, custo, custo_viz, i;
    double t;
    float r, prob, delta_c;

    // Inicializar a temperatura no seu valor máximo
    t = tMax;

    nova_sol = malloc(sizeof(int) * vert);
    if (nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
    // Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);
    for (i = 0; i < num_iter; i++)
    {
        // Gera vizinho
        gera_vizinho(sol, nova_sol, vert);

        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, mat, vert);

        // Calcula a variação de custo:
        // Aceita vizinho se o custo diminuir (problema de minimizacao)
        delta_c = (custo_viz - custo);

        if (delta_c <= 0){
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }
        else{
            r = rand_01();
            prob = exp(-delta_c/t);

            if (r <= prob){
                substitui(sol, nova_sol, vert);
                custo = custo_viz;
            }
        }

        // Função de arrefecimento (escolher uma):
        // t = t - alpha;
        t = t * alpha;
        // t = t / (1 + alpha*t);

        // Critério de paragem
        if (t<tMin) {break;}
    }
    free(nova_sol);
    return custo;
}