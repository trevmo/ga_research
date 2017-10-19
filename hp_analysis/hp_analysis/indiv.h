#pragma once
#include"params.h"  // contains general parameters of the GA

class indiv {
private:
	int genome[genomeLength];
	double fitness;

	void calcFit(double(*calcDamage)(double, double), double arg1, double arg2);
public:
	indiv();
	void print();
	void mutate();
	double getFit() { return fitness; }
	double getGene(int i) { return genome[i]; }
	void calcFit();
	void copy(indiv);
};
