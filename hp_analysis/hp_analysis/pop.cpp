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
 * Base constructor for the population. Calculates the overal statistics
 * based off the array of randomly initialized individuals.
 */
Population::Population() {
	calcAvgs();
}
/**
 * Re-calculate the fitness of the individuals and print out the stats of
 * the population.
 */
void Population::print() {
	for (int i = 0; i < popSize; i++) {
		individuals[i].calcFit();
		//printf("%d ",i);
		//the_pop[i].print();
	}
	calcAvgs();
	printf("Average Fitness: %f Best Fitness: %f  Best Individual %d genes:", avgFit, bestFit, best);
	for (int g = 0; g < genomeLength; g++) {
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
		for (int i = 0; i < popSize; i++)
			individuals[i].calcFit();
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
	bestFit = individuals[0].getFit();
	avgFit = individuals[0].getFit();
	for (int i = 1; i < popSize; i++) {
		avgFit += individuals[i].getFit();
		if (individuals[i].getFit() > bestFit) {
			best = i;
			bestFit = individuals[i].getFit();
		}
	}
	avgFit /= popSize;

	for (int g = 0; g < genomeLength; g++) {
		avgGenes[g] = 0;
		for (int i = 1; i < popSize; i++) {
			avgGenes[g] += individuals[i].getGene(g);
		}
		avgGenes[g] /= popSize;
	}
}
/**
 * Perform selection and mutation to form the next generation of the population.
 * Also, include two copies of the best fitness for elitism.
 */
void Population::nextGen() {
	Individual temp[popSize];
	// elitism, make two copies of the best individual
	temp[0].copy(individuals[best]);  
	temp[1].copy(individuals[best]);
	int p1, p2;
	for (int i = 2; i < popSize; i += 2) {
		p1 = selectParent();
		p2 = selectParent();
		temp[i].copy(individuals[p1]);
		temp[i + 1].copy(individuals[p2]);
		// no crossover, because there's only one gene
		//temp[i].crossover(temp[i+1]);   
		temp[i].mutate();
		temp[i + 1].mutate();
	}
	for (int i = 0; i < popSize; i++) {
		individuals[i].copy(temp[i]);
	}
}
/**
 * Perform tournament-style selection to find parents for the
 * GA's.
 * @return index of the parent in the population
 */
int Population::selectParent() {
	int best, temp;
	int bestFit;
	best = rand() % popSize;
	bestFit = individuals[best].getFit();
	for (int i = 1; i < tournSize; i++) {
		temp = rand() % popSize;
		if (individuals[temp].getFit() > bestFit) {
			best = temp;
			bestFit = individuals[best].getFit();
		}
	}
	return best;
}