#pragma once
#include "indiv.h"

class pop {
private:
	indiv the_pop[popSize];
	int best;   // index of the most fit indivdual
	float bestFit;   // fitness of the most fit individual
	float avgFit;    // average fitness of the population
	float avgGenes[genomeLength];   // average value of each gene 
public:
	pop();
	void calcAvgs();
	void print();
	void nextGen();
	int selectParent();
};
