#include "coin_change_ea.h"
#include "utils.h"  
#include <math.h>   
#include <stdlib.h> 
#include <stdio.h>

// Função para calcular o fitness de uma solução
float calculate_fitness(Solution *sol, ProblemInstance *problem) {
    // Implementação para calcular o fitness (qualidade da solução)
    sol->total_value = 0;
    for (int i = 0; i < problem->num_coin_types; i++) {
        sol->total_value += sol->coin_counts[i] * problem->coin_values[i];
    }
    // O fitness é a proximidade do valor objetivo
    return 1.0f / (1.0f + fabs(problem->target_value - sol->total_value)); // Usando fabs()
}

// Função para inicializar a população
void initialize_population(Solution population[], ProblemInstance *problem) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < problem->num_coin_types; j++) {
            population[i].coin_counts[j] = rand() % 10;  // Número aleatório de moedas
        }
        population[i].fitness = calculate_fitness(&population[i], problem);  // Calcula o fitness
    }
}

// Função para realizar o crossover (cruzamento) entre dois pais
void crossover(Solution *parent1, Solution *parent2, Solution *child, ProblemInstance *problem) {
    for (int i = 0; i < problem->num_coin_types; i++) {
        child->coin_counts[i] = (rand() % 2) ? parent1->coin_counts[i] : parent2->coin_counts[i];
    }
    child->fitness = calculate_fitness(child, problem);  // Recalcula o fitness da criança
}

// Função para realizar a mutação
void mutate(Solution *sol, ProblemInstance *problem, float mutation_rate) {
    for (int i = 0; i < problem->num_coin_types; i++) {
        if ((rand() / (float)RAND_MAX) < mutation_rate) {  // Usando RAND_MAX
            sol->coin_counts[i] = rand() % 10;  // Mutação aleatória
        }
    }
    sol->fitness = calculate_fitness(sol, problem);  // Recalcula o fitness
}

// Função principal do algoritmo evolutivo
void evolutionary_algorithm(ProblemInstance *problem) {
    Solution population[POPULATION_SIZE];
    Solution new_population[POPULATION_SIZE];
    initialize_population(population, problem);

    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        for (int i = 0; i < POPULATION_SIZE; i++) {
            Solution *parent1 = tournament_selection(population);
            Solution *parent2 = tournament_selection(population);
            crossover(parent1, parent2, &new_population[i], problem);
            mutate(&new_population[i], problem, 0.05f);  // Taxa de mutação
        }
        for (int i = 0; i < POPULATION_SIZE; i++) {
            population[i] = new_population[i];
        }
        Solution *best = find_best_solution(population);
        print_solution(best, problem);
    }
}
