#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define DEFAULT_RUNS 10

int main(int argc, char *argv[]){
	char nome_fich[100];
	struct info EA_param;
	pchrom pop = NULL, parents = NULL;
	chrom best_run, best_ever;
	int gen_actual, r, runs, i, inv, mat[MAX_OBJ][2];
	float mbf = 0.0;

	// Lê os argumentos de entrada
	if (argc == 3){
		runs = atoi(argv[2]);
		strcpy(nome_fich, argv[1]);
	}
	else if (argc == 2){ // Se apenas o nome do ficheiro foi colocado nos argumentos
		runs = DEFAULT_RUNS;
		strcpy(nome_fich, argv[1]);
	}
	else{ // Solicita o nome do ficheiro caso não tenha sido fornecido
		runs = DEFAULT_RUNS;
		printf("Nome do Ficheiro: ");
		fgets(nome_fich, sizeof(nome_fich), stdin);
		nome_fich[strcspn(nome_fich, "\n")] = 0; // Remove o '\n' da string
	}

	// Se o número de execuções for menor ou igual a 0, termina o programa
	if (runs <= 0)
		return 0;

	// Inicializa a geração de números aleatórios
	init_rand();

	// Preenche a matriz com dados dos objetos (peso e valor) e a estrutura EA_param com dados do ficheiro
	EA_param = init_data(nome_fich, mat);

	// Realiza as execuções definidas
	for (r = 0; r < runs; r++){
		printf("Repetição %d\n", r + 1);

		// Geração da população inicial
		pop = init_pop(EA_param);

		// Avalia a população inicial
		evaluate(pop, EA_param, mat);
		gen_actual = 1;

		// Define a melhor solução como a primeira da população inicialmente
		best_run = pop[0];

		// Encontra a melhor solução na população
		best_run = get_best(pop, EA_param, best_run);

		// Reserva espaço para os pais da próxima geração
		parents = malloc(sizeof(chrom) * EA_param.popsize);
		if (parents == NULL){ // Verifica alocação de memória
			printf("Erro na alocação de memória\n");
			exit(1);
		}

		// Ciclo de otimização
		while (gen_actual <= EA_param.numGenerations){
			// Torneio binário para selecionar progenitores
			tournament(pop, EA_param, parents);

			// Aplica operadores genéticos para gerar a nova população
			genetic_operators(parents, EA_param, pop);

			// Avalia a nova população
			evaluate(pop, EA_param, mat);

			// Atualiza a melhor solução encontrada
			best_run = get_best(pop, EA_param, best_run);
			gen_actual++;
		}

		// Conta soluções inválidas
		for (inv = 0, i = 0; i < EA_param.popsize; i++)
			if (pop[i].valido == 0)
				inv++;

		// Escreve resultados da repetição
		printf("\nRepetição %d:", r);
		write_best(best_run, EA_param);
		printf("\nPercentagem de Inválidos: %f\n", 100 * (float)inv / EA_param.popsize);
		mbf += best_run.fitness;

		// Atualiza a melhor solução global se necessário
		if (r == 0 || best_run.fitness > best_ever.fitness)
			best_ever = best_run;

		// Libera a memória alocada
		free(parents);
		free(pop);
	}

	// Escreve resultados globais
	printf("\n\nMBF: %f\n", mbf / r);
	printf("\nMelhor solução encontrada:");
	write_best(best_ever, EA_param);

	return 0;
}
