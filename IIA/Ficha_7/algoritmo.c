#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"

//TIPO 3
void repair(pchrom pop, struct info d, int mat[][2]){
	int i, object_to_remove;
	float current_w;

	for(i=0; i<d.popsize; i++){
		current_w = calcula_peso(pop[i].p, d, mat);

		while (current_w > d.capacity){
			do
			    object_to_remove=random_l_h(0, d.numGenes -1);
			while(pop[i].p[object_to_remove] != 1);
			

			pop[i].p[object_to_remove] = 0;

			current_w = calcula_peso(pop[i].p, d, mat);
		}
		
	}
}

// TIPO 4
void repair_sofrega(pchrom pop, struct info d, int mat[][2]){
	int i, j, object_to_remove = 1;
	float current_w, minimum_v;

	for(i=0; i<d.popsize; i++){
		current_w = calcula_peso(pop[i].p, d, mat);
		while(current_w > d.capacity){
			object_to_remove=-1; minimum_v = 100;
			for(j=0; j < d.numGenes; j++){
				if(pop[i].p[j] == 1){
					if(mat[j][1] < minimum_v){
						minimum_v = mat[j][1];
						object_to_remove = j;
					}
				}
			}

			pop[i].p[object_to_remove] = 0;

			current_w = calcula_peso(pop[i].p, d, mat);
		}
	}
}

// Preenche uma estrutura com os progenitores da pr�xima gera��o, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Par�metros de entrada: popula��o actual (pop), estrutura com par�metros (d) e popula��o de pais a encher
void tournament(pchrom pop, struct info d, pchrom parents)
{
	int i, x1, x2;

	// Realiza popsize torneios
	for(i=0; i<d.popsize;i++)
	{
		x1 = random_l_h(0, d.popsize-1);
		do
			x2 = random_l_h(0, d.popsize-1);
		while(x1==x2);
		if(pop[x1].fitness > pop[x2].fitness)		// Problema de maximizacao
			parents[i]=pop[x1];
		else
			parents[i]=pop[x2];
	}
}

// Operadores geneticos a usar na gera��o dos filhos
// Par�metros de entrada: estrutura com os pais (parents), estrutura com par�metros (d), estrutura que guardar� os descendentes (offspring)
void genetic_operators(pchrom parents, struct info d, pchrom offspring)
{
    // Recombina��o com um ponto de corte
	crossover(parents, d, offspring);
	// Muta��o bin�ria
	mutation(offspring, d);
}

// Preenche o vector descendentes com o resultado das opera��es de recombina��o
// Par�metros de entrada: estrutura com os pais (parents), estrutura com par�metros (d), estrutura que guardar� os descendentes (offspring)
void crossover(pchrom parents, struct info d, pchrom offspring)
{
	int i, j, point;

	for (i=0; i<d.popsize; i+=2)
	{
		if (rand_01() < d.pr)
		{
			point = random_l_h(0, d.numGenes-1);
			for (j=0; j<point; j++)
			{
				offspring[i].p[j] = parents[i].p[j];
				offspring[i+1].p[j] = parents[i+1].p[j];
			}
			for (j=point; j<d.numGenes; j++)
			{
				offspring[i].p[j]= parents[i+1].p[j];
				offspring[i+1].p[j] = parents[i].p[j];
			}
		}
		else
		{
			offspring[i] = parents[i];
			offspring[i+1] = parents[i+1];
		}
	}
}

// Muta��o bin�ria com v�rios pontos de muta��o
// Par�metros de entrada: estrutura com os descendentes (offspring) e estrutura com par�metros (d)
void mutation(pchrom offspring, struct info d)
{
	int i, j;

	for (i=0; i<d.popsize; i++)
		for (j=0; j<d.numGenes; j++)
			if (rand_01() < d.pm)
				offspring[i].p[j] = !(offspring[i].p[j]);
}

// TIPO 3

float calcula_peso(int sol[], struct info d, int mat[][2]) {
	int i;
	float sum_weight = 0.0;

	for (i=0; i < d.numGenes; i++){
		if(sol[i] == 1){
			sum_weight += mat[i][0];
		}
	}
	return sum_weight;
}
