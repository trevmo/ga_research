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
