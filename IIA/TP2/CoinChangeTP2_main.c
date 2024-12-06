#include "troco.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, v ;                 // Quantidade de moedas e valor a ser trocado
    int *moedas = NULL;       // Array de moedas
    int melhorSolucao[100];   // Melhor solução encontrada
    int melhorCusto;          // Custo associado à melhor solução

    // Lê a instância do arquivo
    lerInstancia("file1.txt", &n, &v, &moedas);

    // Ordena as moedas em ordem decrescente
    ordenarMoedasDecrescente(moedas, n);

    // Executa o algoritmo Trepa-Colinas
    trepaColinas(n, v, moedas, melhorSolucao, &melhorCusto);

    // Imprime o resultado
    printf("Melhor solução encontrada:\n");
    for (int i = 0; i < n; i++) {
        printf("Moeda %d: %d\n", moedas[i], melhorSolucao[i]);
    }
    printf("Custo total (número de moedas): %d\n", melhorCusto);

    free(moedas); // Libera a memória alocada
    return 0;
}
