#include <stdio.h>
#include "utils.h" 

// Função de seleção por torneio
Solution* tournament_selection(Solution population[]) {
    // Implementação da seleção por torneio
    // Exemplo de código:
    int best_index = 0;
    for (int i = 1; i < POPULATION_SIZE; i++) {
        if (population[i].fitness > population[best_index].fitness) {
            best_index = i;
        }
    }
    return &population[best_index];
}

// Função para encontrar a melhor solução
Solution* find_best_solution(Solution population[]) {
    // Implementação para encontrar a melhor solução
    int best_index = 0;
    for (int i = 1; i < POPULATION_SIZE; i++) {
        if (population[i].fitness > population[best_index].fitness) {
            best_index = i;
        }
    }
    return &population[best_index];
}

// Função para imprimir a solução
void print_solution(Solution *solution, ProblemInstance *problem) {
    // Implementação de impressão da solução
    printf("Solução encontrada:\n");
    for (int i = 0; i < problem->num_coin_types; i++) {
        printf("Moeda %d: %d\n", i + 1, solution->coin_counts[i]);
    }
    printf("Valor total: %.2f\n", solution->total_value);
    printf("Fitness: %.2f\n", solution->fitness);
}
