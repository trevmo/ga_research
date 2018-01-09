/**
* This file contains the implementations of the methods for the Population class.
*
* @author tsoule
* @author trevmo
*/

#include "stdafx.h"
#include "pop.h"
#include "util.h"
#include <iostream>

/**
 * Base constructor for the population. Calculates the overall statistics
 * based off the array of randomly initialized individuals.
 */
Population::Population() {
	//initialize an array of individuals with NULL genomes
	individuals = new Individual *[POP_SIZE];
	for (int i = 0; i < POP_SIZE; i++)
		//initialize each individual in the array with a random genome
		individuals[i] = new Individual(GENOME_LENGTH);
	
	calcAvgs();
}
/**
 * Deconstruct the population.
 */
Population::~Population() {
	delete[] individuals;
}
/**
 * Re-calculate the fitness of the individuals and print out the stats of
 * the population.
 */
void Population::print() {
	for (int i = 0; i < POP_SIZE; i++)
		individuals[i]->calcFit();
	calcAvgs();
	printf("Average Fitness: %f Best Fitness: %f  Best Individual %d genes:", avgFit, bestFit, best);
	for (int g = 0; g < GENOME_LENGTH; g++) {
		printf(" %.3f", avgGenes[g]);
	}
	printf("\n");

}
/**
 * Open a csv for storing the stats of the population over the course
 * of multiple generations.
 * @param filename name of the file (including relative path and .csv extension)
 * @param time time at which the algorithm began
 */
void Population::openCsv(string filename, time_t time)
{
	csv = new ofstream;
	csv->open(filename.c_str(), fstream::out);
	if (csv->fail())
		cout << "fail";
	printHeader(*csv, time);
	*csv << "Generation,AvgFit,BestFit\n";
}
/**
 * Output the stats of the specified generation of the population to the
 * previously opened csv file.
 * @param generation current generation value
 */
void Population::printToCsv(int generation) {
	if (csv->is_open()) {
		for (int i = 0; i < POP_SIZE; i++)
			individuals[i]->calcFit();
		calcAvgs();
		*csv << generation << "," << avgFit << "," << bestFit << endl;
	}
	else
		cout << ".csv file has not yet been opened.\n";
}
/**
 * Close the csv.
 */
void Population::closeCsv()
{
	csv->close();
}
/**
 * Calculate the average fitness and genes of the population.
 */
void Population::calcAvgs() {
	best = 0;
	bestFit = individuals[0]->getFit();
	avgFit = individuals[0]->getFit();
	for (int i = 1; i < POP_SIZE; i++) {
		avgFit += individuals[i]->getFit();
		if (individuals[i]->getFit() > bestFit) {
			best = i;
			bestFit = individuals[i]->getFit();
		}
	}
	avgFit /= POP_SIZE;

	for (int g = 0; g < GENOME_LENGTH; g++) {
		avgGenes[g] = 0;
		for (int i = 1; i < POP_SIZE; i++) {
			avgGenes[g] += individuals[i]->getGene(g);
		}
		avgGenes[g] /= POP_SIZE;
	}
}
/**
 * Perform selection and mutation to form the next generation of the population.
 * Also, include two copies of the best fitness for elitism.
 */
void Population::nextGen() {
	Individual **tmp = new Individual *[POP_SIZE];
	tmp[0] = individuals[best]->copy();
	tmp[1] = individuals[best]->copy();
	int parent1;
	int parent2;
	for (int i = 2; i < POP_SIZE; i += 2) {
		parent1 = selectParent();
		parent2 = selectParent();
		tmp[i] = individuals[parent1]->copy();
		tmp[i + 1] = individuals[parent2]->copy();
		// no crossover currently
		tmp[i]->mutate();
		tmp[i + 1]->mutate();
	}
	for (int j = 0; j < POP_SIZE; j++)
		individuals[j] = tmp[j]->copy();
}
/**
 * Perform tournament-style selection to find parents for the
 * GA's.
 * @return index of the parent in the population
 */
int Population::selectParent() {
	int best, temp;
	int bestFit;
	best = rand() % POP_SIZE;
	bestFit = individuals[best]->getFit();
	for (int i = 1; i < TOURN_SIZE; i++) {
		temp = rand() % POP_SIZE;
		if (individuals[temp]->getFit() > bestFit) {
			best = temp;
			bestFit = individuals[best]->getFit();
		}
	}
	return best;
}