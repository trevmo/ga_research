#pragma once
#include"params.h"  // contains general parameters of the GA

class indiv {
private:
	int genome[genomeLength];
	double fitness;
public:
	indiv();
	void print();
	void mutate();
	double getFit() { return fitness; }
	double getGene(int i) { return genome[i]; }
	void calcFit();
	void copy(indiv);
};

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
	// attackType == 0 means fixed damage, so take the ceiling of the number of time health is divisable by damage
	if (attackType == 0) { // fixed damage
		fitness = ceil((double)genome[0] / (double)damageAmount);
	}
	// attackType == 1 means uniformly distributed random damage, so loop doing random damage until health is gone
	if (attackType == 1) {  // uniform distribution
		float health = genome[0];
		float damage;
		fitness = 0;
		while (health > 0) {
			damage = meanDamage - rangeDamage + (rand() % (int)(2 * rangeDamage + 1));
			health -= damage;
			fitness++; // one fitness per hit
		}
	}
	// an attackType with a gaussian distribution would be an interesting comparison
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