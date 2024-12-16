#include "coin_change_ea.h"
#include "utils.h"  
#include <math.h>   
#include <stdlib.h> 
#include <stdio.h>
#include <time.h>

// Função para calcular o fitness de uma solução
float calculate_fitness(Solution *sol, ProblemInstance *problem) {
    sol->total_value = 0;
    for (int i = 0; i < problem->num_coin_types; i++) {
        sol->total_value += sol->coin_counts[i] * problem->coin_values[i];
    }
    
    // Fitness aprimorado: penaliza soluções que excedem ou ficam muito abaixo do valor-alvo
    float diff = fabs(problem->target_value - sol->total_value);
    return 1.0f / (1.0f + diff);
}

// Função para inicializar a população
void initialize_population(Solution population[], ProblemInstance *problem) {
    // Inicializa a semente para geração aleatória
    srand(time(NULL));
    
    for (int i = 0; i < POPULATION_SIZE; i++) {
        // Gera solução inicial mais inteligente
        float remaining = problem->target_value;
        for (int j = problem->num_coin_types - 1; j >= 0; j--) {
            population[i].coin_counts[j] = (int)(remaining / problem->coin_values[j]);
            remaining -= population[i].coin_counts[j] * problem->coin_values[j];
        }
        
        // Adiciona variação aleatória
        for (int j = 0; j < problem->num_coin_types; j++) {
            population[i].coin_counts[j] += rand() % 3 - 1;  // Varia ±1
            population[i].coin_counts[j] = fmax(0, population[i].coin_counts[j]);
        }
        
        population[i].fitness = calculate_fitness(&population[i], problem);
    }
}

// Função para realizar o crossover (cruzamento) com ponto de corte
void crossover(Solution *parent1, Solution *parent2, Solution *child, ProblemInstance *problem) {
    // Crossover de ponto único
    int crossover_point = rand() % problem->num_coin_types;
    
    for (int i = 0; i < problem->num_coin_types; i++) {
        child->coin_counts[i] = (i < crossover_point) ? 
            parent1->coin_counts[i] : parent2->coin_counts[i];
    }
    child->fitness = calculate_fitness(child, problem);
}

// Função para realizar a mutação mais controlada
void mutate(Solution *sol, ProblemInstance *problem, float mutation_rate) {
    for (int i = 0; i < problem->num_coin_types; i++) {
        if ((rand() / (float)RAND_MAX) < mutation_rate) {
            // Mutação inteligente: incrementa, decrementa ou mantém
            int delta = (rand() % 3) - 1;  // -1, 0 ou 1
            sol->coin_counts[i] = fmax(0, fmin(10, sol->coin_counts[i] + delta));
        }
    }
    sol->fitness = calculate_fitness(sol, problem);
}

// Função principal do algoritmo evolutivo
void evolutionary_algorithm(ProblemInstance *problem) {
    Solution population[POPULATION_SIZE];
    Solution new_population[POPULATION_SIZE];
    
    // Inicializa população
    initialize_population(population, problem);

    printf("Evolução do Algoritmo Genético:\n");
    
    // Loop de gerações
    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        printf("\nGeração %d:\n", generation + 1);
        
        // Elitismo: mantém a melhor solução
        Solution best_solution = *find_best_solution(population);
        
        // Cria nova população
        for (int i = 0; i < POPULATION_SIZE; i++) {
            Solution *parent1 = tournament_selection(population);
            Solution *parent2 = tournament_selection(population);
            
            crossover(parent1, parent2, &new_population[i], problem);
            mutate(&new_population[i], problem, 0.1f);  // Taxa de mutação ajustada
        }
        
        // Substitui população
        for (int i = 0; i < POPULATION_SIZE; i++) {
            population[i] = new_population[i];
        }
        
        // Mostra melhor solução da geração
        printf("Melhor solução da geração:\n");
        print_solution(&best_solution, problem);
    }
}