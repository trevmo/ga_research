/**
 * This file contains the implementations of the methods for the Individual class.
 *
 * @author tsoule
 * @author trevmo
 */

#include "stdafx.h"
#include "indiv.h"
#include "util.h"
#include <cstdlib>

/**
 * Base constructor for the Individual class. Initializes an 
 * individual with a random genome.
 */
Individual::Individual() {
	for (int i = 0; i < genomeLength; i++) {
		//genome[0] is the individual's health value
		//genome[1] is the individual's armor value
		genome[i] = 1 + rand() % maxInitGeneVal;
	}
}
/**
 * Make a copy of an individual.
 * @param source original individual to copy
 */
void Individual::copy(Individual source) {
	// deep copy
	for (int i = 0; i < genomeLength; i++) {
		genome[i] = source.genome[i];
	}
	fitness = source.fitness;
}
/**
 * Calculate the fitness of the individual. This depends on the attack type
 * as the fitness is the measure of how long the health lasts while undergoing
 * a particular attack.
 */
void Individual::calcFit() {
	switch (attackType)
	{
	case 0:
		//attackType == 0 means fixed damage, so take the ceiling of 
		//the number of time health is divisable by damage
		fitness = ceil((double)genome[0] / (double)damageAmount);
		break;
	case 1:
		//attackType == 1 means uniformly distributed random damage,
		calcFit(uniformDistDamage);
		break;
	case 2:
		//attackType == 2 means Gaussian distributed random damage
		//similar to case 1 with a different approach to random number generation
		calcFit(gaussianDamage);
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
 */
void Individual::calcFit(double(*calcDamage)(double, double))
{
	float health = genome[0];
	float armor = (genomeLength > 1 ? genome[1] * armorScale : 0);
	//if using a Gaussian attack type, and the armor is greater than two
	//std. dev. from the mean damage, treat the individual as having
	//impenetrable armor
	if (attackType == 2 &&
		armor > ((2 * rangeDamage) + meanDamage))
	{
		fitness = highFitness;
		return;
	}
	float damage;
	fitness = 0;
	while (health > 0) {
		damage = calcDamage(meanDamage, rangeDamage);
		//on the off chance it is negative, flip the sign
		damage = (damage < 0 ? -1 * damage : damage);
		//if there is armor in play, subtract that value from the damage
		//and then apply the damage to the health
		damage -= armor;
		if (damage > 0) {
			//if the armor has not completely eliminated the damage
			//then count the number of hits the individual can take
			health -= damage;
			// one fitness per hit
			fitness++;
		} else {
			//if the armor completely blocks the damage, then set
			//the fitness to a high value
			fitness = highFitness;
			break;
		}
	}
}
/**
 * Print out the genome and fitness of the individual.
 */
void Individual::print() {
	for (int i = 0; i < genomeLength; i++) {
		printf("%d ", genome[i]);
	}
	printf(" : %f\n", fitness);
}
/**
 * Mutate the genome of the individual. Currently, the only option is to perform
 * uniform mutation, but this could be expanded to allow for other types as well.
 */
void Individual::mutate() {
	int m;
	for (int i = 0; i < genomeLength; i++) {
		// 0 - uniform, may have different kind of mutation later
		if (mutateType == 0) {
			m = (rand() % uniformMutateRange - (uniformMutateRange / 2));
			genome[i] += m;
		}
	}
}