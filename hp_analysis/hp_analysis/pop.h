#pragma once
#include "indiv.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class pop {
private:
	indiv the_pop[popSize];
	int best;   // index of the most fit indivdual
	float bestFit;   // fitness of the most fit individual
	float avgFit;    // average fitness of the population
	float avgGenes[genomeLength];   // average value of each gene 

	ofstream *csv;
public:
	pop();
	void calcAvgs();
	void print();
	void openCsv(string filename, time_t time);
	void printToCsv(int generation);
	void closeCsv();
	void nextGen();
	int selectParent();
};
