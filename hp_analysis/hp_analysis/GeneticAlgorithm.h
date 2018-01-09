#pragma once
#include "pop.h"

/**
* This class defines a genetic algorithm for testing the affects of different
* attack/damage types on the health and/or armor of an individual.
*
* @author trevmo
*/
class GeneticAlgorithm
{
private:
	Population *population;
	int attackType;
	int range;
	int delay;
public:
	GeneticAlgorithm(int attackType, int range, int delay);
	void reset();
	void run(int iteration, int generations);
};

