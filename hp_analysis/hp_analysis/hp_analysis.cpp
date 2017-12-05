/**
 * This serves as the main file of the project. It controls the execution
 * of the GA for testing and data collection purposes.
 *
 * @author tsoule
 * @author trevmo
 */

#include "stdafx.h"
#include <cstdlib>
#include "GeneticAlgorithm.h"
#include "params.h"
using namespace std;

int attackType;
double rangeDamage;

int main() {
	int iterations = 1;
	GeneticAlgorithm *ga = NULL;
	//uniform and Gaussian damage
	for (int type = 1; type < 3; type++) {
		attackType = type;
		//range of damage for uniform; std dev for Gaussian
		for (int range = 0; range < 15; range++) {
			ga = new GeneticAlgorithm(attackType, range, 1000);
			for (int iter = 0; iter < iterations; iter++) {
				ga->run(iter, 100);
				ga->reset();
			}
		}
	}
	return 0;
}
