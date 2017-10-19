#include "stdafx.h"
#include "indiv.h"
#include "util.h"
#include <cstdlib>

indiv::indiv() {
	for (int i = 0; i < genomeLength; i++) {
		// initial health is between 1 and the max initial health
		genome[i] = 1 + rand() % (maxInitHealth);
	}
}

void indiv::copy(indiv source) {
	// deep copy
	for (int i = 0; i < genomeLength; i++) {
		genome[i] = source.genome[i];
	}
	fitness = source.fitness;
}

void indiv::calcFit() {
	switch (attackType)
	{
	case 0:
		//attackType == 0 means fixed damage, so take the ceiling of 
		//the number of time health is divisable by damage
		fitness = ceil((double)genome[0] / (double)damageAmount);
		break;
	case 1:
		//attackType == 1 means uniformly distributed random damage,
		calcFit(uniformDistDamage, meanDamage, rangeDamage);
		break;
	case 2:
		//attackType == 2 means Gaussian distributed random damage
		//similar to case 1 with a different approach to random number generation

		//mean = 3; stdDev = 1 -- shifts normal distribution so that 99.7% of 
		//values are positive
		calcFit(gaussianDamage, 3, 1);
		break;
	default:
		break;
	}
}
/**
 * Calculates the fitness of the individual when using a variable amount of damage
 * (currently either uniform or gaussian distributions). Loop doing the variable
 * amount of damage until the health is gone to determine the fitness.
 * @param calcDamage pointer to damage function
 * @param arg1 first argument to calcDamage
 * @param arg2 second argument to calcDamage
 */
void indiv::calcFit(double(*calcDamage)(double, double), double arg1, double arg2)
{
	float health = genome[0];
	float damage;
	fitness = 0;
	while (health > 0) {
		damage = calcDamage(arg1, arg2);
		//on the off chance it is negative, flip the sign
		damage = (damage < 0 ? -1 * damage : damage);
		health -= damage;
		fitness++; // one fitness per hit
	}
}

void indiv::print() {
	for (int i = 0; i < genomeLength; i++) {
		printf("%d ", genome[i]);
	}
	printf(" : %f\n", fitness);
}

void indiv::mutate() {
	int m;
	for (int i = 0; i < genomeLength; i++) {
		if (mutateType == 0) {  // 0 - uniform, may have different kind of mutation later
			m = (rand() % uniformMutateRange - (uniformMutateRange / 2));
			genome[i] += m;
		}
	}
}