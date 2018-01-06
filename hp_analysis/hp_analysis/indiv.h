#pragma once
#include"params.h"  // contains general parameters of the GA

/**
 * This class defines the data members and methods for an Individual.
 * Each individual is composed of a genome (currently a single value for
 * its health).
 * 
 * @author tsoule
 * @author trevmo
 */

class Individual {
private:
	int genome[genomeLength];
	double fitness;

	const int MAX_INIT_VAL = 10;
	const double ARMOR_SCALE = 0.1;
	const int HIGH_FITNESS = 1000;

	void calcFit(double(*calcDamage)(double, double));
public:
	Individual();
	void print();
	void mutate();
	double getFit() { return fitness; }
	double getGene(int i) { return genome[i]; }
	void calcFit();
	void copy(Individual);
};
