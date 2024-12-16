#include <stdio.h>
#include <stdlib.h>
#include "utils.h" 

// Função de seleção por torneio com mais aleatoriedade
Solution* tournament_selection(Solution population[]) {
    int k = 5;  // Tamanho do torneio
    int best_index = rand() % POPULATION_SIZE;
    
    for (int i = 1; i < k; i++) {
        int candidate_index = rand() % POPULATION_SIZE;
        if (population[candidate_index].fitness > population[best_index].fitness) {
            best_index = candidate_index;
        }
    }
    return &population[best_index];
}

// Função para encontrar a melhor solução global
Solution* find_best_solution(Solution population[]) {
    int best_index = 0;
    for (int i = 1; i < POPULATION_SIZE; i++) {
        if (population[i].fitness > population[best_index].fitness) {
            best_index = i;
        }
    }
    return &population[best_index];
}

// Função para imprimir a solução com mais detalhes
void print_solution(Solution *solution, ProblemInstance *problem) {
    printf("Solução encontrada:\n");
    for (int i = 0; i < problem->num_coin_types; i++) {
        printf("Moeda %d: %d ", i + 1, solution->coin_counts[i]);
    }
    printf("\nValor total: %.2f ", solution->total_value);
    printf("Fitness: %.2f\n\n", solution->fitness);
}