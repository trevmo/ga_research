#pragma once
#include "params.h"  // contains general parameters of the GA

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
	int *genome;
	double fitness;
	int genomeLength;

	void calcFit(double(*calcDamage)(double, double));
	bool exceedsMaxDamage(float value, int factor);
public:
	static const int MAX_INIT_VAL = 10;
	static const int HIGH_FITNESS = 1000;
	static const double ARMOR_SCALE;

	Individual();
	Individual(int genomeLength);
	~Individual();
	void print();
	void mutate();
	double getFit() { return fitness; }
	double getGene(int i) { return genome[i]; }
	void calcFit();
	Individual* copy();
	void copy(Individual);
};
