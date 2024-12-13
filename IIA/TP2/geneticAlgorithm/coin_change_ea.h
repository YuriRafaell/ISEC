#ifndef COIN_CHANGE_EA_H
#define COIN_CHANGE_EA_H

#include <stdbool.h>

#define MAX_COINS 10
#define POPULATION_SIZE 100
#define MAX_GENERATIONS 50

// Estrutura para representar uma solução
typedef struct {
    int coin_counts[MAX_COINS];  // Quantidade de cada tipo de moeda
    float total_value;           // Valor total da solução
    float fitness;               // Qualidade da solução
} Solution;

// Estrutura para armazenar informações das moedas
typedef struct {
    int num_coin_types;           // Número de tipos de moedas
    float target_value;           // Valor objetivo
    float coin_values[MAX_COINS];  // Valores de cada tipo de moeda
} ProblemInstance;

// Funções principais do algoritmo evolutivo
float calculate_fitness(Solution *sol, ProblemInstance *problem);
void initialize_population(Solution population[], ProblemInstance *problem);
void crossover(Solution *parent1, Solution *parent2, Solution *child, ProblemInstance *problem);
void mutate(Solution *sol, ProblemInstance *problem, float mutation_rate);
void evolutionary_algorithm(ProblemInstance *problem);

// Funções auxiliares
Solution* tournament_selection(Solution population[]);
Solution* find_best_solution(Solution population[]);
void print_solution(Solution *solution, ProblemInstance *problem);
void repair_solution(Solution *sol, ProblemInstance *problem);

#endif // COIN_CHANGE_EA_H
