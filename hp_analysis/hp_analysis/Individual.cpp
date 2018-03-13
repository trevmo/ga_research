/**
 * This file contains the implementations of the methods for the Individual class.
 *
 * @author tsoule
 * @author trevmo
 */

#include "stdafx.h"
#include "Individual.h"
#include "util.h"
#include <cstdlib>


const double Individual::ARMOR_SCALE = 0.1;

/**
 * Base constructor for the Individual class.
 */
Individual::Individual() {
	genome = NULL;
}
/**
 * Parameterized constructor for the Individual class. Initializes an 
 * individual with a random genome.
 */
Individual::Individual(int genomeLength) {
	this->genomeLength = genomeLength;
	genome = new int[genomeLength];
	int modVal = 0;
	//if the max init val is <= this threshold, randomly initialize
	//otherwise, simply set to the max init val
	int randInitThreshold = 10;
	for (int i = 0; i < genomeLength; i++) {
		modVal = (i == HEALTH_GENE ? MAX_INIT_HEALTH : MAX_INIT_ARMOR);
		if (modVal > randInitThreshold)
			genome[i] = modVal;
		else
			genome[i] = 1 + rand() % modVal;
	}
}
/**
 * Deconstruct an individual.
 */
Individual::~Individual() {
	delete[] genome;
}
/**
 * Make a copy of the current object and return the reference
 * to the new Individual.
 * @return pointer to a new Individual object
 */
Individual* Individual::copy() {
	Individual *newInd = new Individual(genomeLength);
	for (int i = 0; i < genomeLength; i++)
		newInd->genome[i] = this->genome[i];
	newInd->fitness = this->fitness;
	return newInd;
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
double Individual::calcFit() {
	switch (DAMAGE.type)
	{
	case 0:
		//attackType == 0 means fixed damage, so take the ceiling of 
		//the number of time health is divisable by damage
		fitness = ceil((double)genome[0] / (double) DAMAGE.mean);
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
	return fitness;
}
/**
 * Calculates the fitness of the individual when using a variable amount of damage
 * (currently either uniform or gaussian distributions). Loop doing the variable
 * amount of damage until the health is gone to determine the fitness.
 * @param calcDamage pointer to damage function
 */
void Individual::calcFit(double(*calcDamage)(double, double))
{
	//if the health has drifted (through mutation) below a value of 0,
	//set it to 1 so that the individual's fitness does not mess with 
	//overall analysis
	float health = (genome[0] > 0 ? genome[0] : 1);
	float armor = 0;
	if (genomeLength > 1)
		armor = (genome[1] > 0 ? genome[1] * ARMOR_SCALE : 0);
	//if using a Gaussian attack type, and the armor is greater than two
	//std. dev. from the mean damage, treat the individual as having
	//impenetrable armor
	if ((DAMAGE.type == 1 && exceedsMaxDamage(armor, 1)) ||
		(DAMAGE.type == 2 && exceedsMaxDamage(armor, 2)))
	{
		fitness = HIGH_FITNESS;
		return;
	}
	float damage;
	fitness = 0;
	while (health > 0) {
		damage = calcDamage(DAMAGE.mean, DAMAGE.range);
		//on the off chance it is negative, flip the sign
		damage = (damage < 0 ? -1 * damage : damage);
		//if there is armor in play, subtract that value from the damage
		//and then apply the damage to the health
		damage -= armor;
		if (damage > 0) {
			//if the armor has not completely eliminated the damage
			//then count the number of hits the individual can take
			health -= damage;
		}
		// one fitness per hit
		fitness++;
	}
}
/**
 * Check if the given value exceeds the "max" damage based off of the
 * mean, range, and a given factor.
 * @param value current armor value
 * @param factor amount to multiply by the range
 * @return boolean indicating if it exceeds or not
 */
bool Individual::exceedsMaxDamage(float value, int factor) {
	return (value >= ((factor * DAMAGE.range) + DAMAGE.mean));
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
	for (int i = 0; i < genomeLength; i++) {
		// 0 - uniform, may have different kind of mutation later
		if (i != MUTATE.skipGene && MUTATE.type == 0)
			genome[i] += (rand() % MUTATE.range - (MUTATE.range / 2));
	}
}