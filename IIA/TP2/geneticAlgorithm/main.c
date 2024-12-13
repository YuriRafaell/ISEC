#include <stdio.h>
#include "coin_change_ea.h"

int main() {
    // Exemplo de problema
    ProblemInstance problem;
    problem.num_coin_types = 3;
    problem.target_value = 12.0f;
    problem.coin_values[0] = 1.0f;
    problem.coin_values[1] = 2.0f;
    problem.coin_values[2] = 5.0f;

    evolutionary_algorithm(&problem);

    return 0;
}
