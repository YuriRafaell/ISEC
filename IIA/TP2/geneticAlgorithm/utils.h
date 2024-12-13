#ifndef UTILS_H
#define UTILS_H

#include "coin_change_ea.h"  // Inclui as definições necessárias

// Declarações das funções auxiliares
Solution* tournament_selection(Solution population[]);
Solution* find_best_solution(Solution population[]);
void print_solution(Solution *solution, ProblemInstance *problem);

#endif // UTILS_H
