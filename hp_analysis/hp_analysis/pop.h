#pragma once
#include "indiv.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

/**
* This class defines the data members and methods for a Population.
* Each population is composed of an array of individuals along with
* members for storing stats about the population.
*
* @author tsoule
* @author trevmo
*/

const int POP_SIZE = 100;

class Population {
private:
	Individual individuals[POP_SIZE];
	int best;   // index of the most fit indivdual
	float bestFit;   // fitness of the most fit individual
	float avgFit;    // average fitness of the population
	float avgGenes[genomeLength];   // average value of each gene 

	const int TOURN_SIZE = 3;

	ofstream *csv;
public:
	Population();
	void calcAvgs();
	void print();
	void openCsv(string filename, time_t time);
	void printToCsv(int generation);
	void closeCsv();
	void nextGen();
	int selectParent();
};
