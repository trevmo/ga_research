/**
* This file contains the implementations of the methods for the GeneticAlgorithm class.
*
* @author trevmo
*/

#include "stdafx.h"
#include "GeneticAlgorithm.h"
#include "util.h"
#include <chrono>
#include <thread>

/**
 * Construct a new instance of a genetic algorithm to test the evolution
 * of an individual's fitness for a given attack type and range.
 * @param attackType 0-constant; 1-uniform; 2-gaussian
 * @param range range or std. dev. of damage for uniform or gaussian attack
 * @param delay number of ms to delay between runs
 */
GeneticAlgorithm::GeneticAlgorithm(int attackType, int range, int delay)
{
	population = new Population();
	this->attackType = attackType;
	this->range = range;
	this->delay = delay;
}
/**
 * Reset the GA's population to a new random array of individuals.
 */
void GeneticAlgorithm::reset()
{
	delete population;
	population = new Population();
}
/**
 * Run the GA for the specified number of generations.
 * @param iteration current iteration of testing the GA
 * @param generations number of generations to run over
 * @param printGenes bool indicating whether to print genes or fitness values
 */
void GeneticAlgorithm::run(int iteration, int generations, bool printGenes)
{
	time_t theTime;
	time(&theTime);
	srand(theTime);
	DAMAGE.range = range;
	population->openCsv(formFileName(iteration, attackType, range), theTime);
	population->printToCsv(0, printGenes);
	for (int g = 0; g < generations; g++) {
		population->nextGen();
		population->printToCsv(g + 1, printGenes);
	}
	population->closeCsv();
	this_thread::sleep_for(chrono::milliseconds(delay));
}
