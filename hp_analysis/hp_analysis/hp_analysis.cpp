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

struct Damage DAMAGE;
struct Mutate MUTATE;

int main() {
	int iterations = 20;
	GeneticAlgorithm *ga = NULL;
	//use uniform mutation with a constant range for now
	MUTATE.type = 0;
	MUTATE.range = 6;
	//uniform and Gaussian damage
	DAMAGE.mean = 15;
	for (int type = 0; type < 3; type++) {
		DAMAGE.type = type;
		//range of damage for uniform; std dev for Gaussian
		for (int range = 0; range < 16; range++) {
			DAMAGE.range = range;
			ga = new GeneticAlgorithm(DAMAGE.type, DAMAGE.range, 1000);
			for (int iter = 0; iter < iterations; iter++) {
				ga->run(iter, 100);
				ga->reset();
			}
		}
	}
	return 0;
}
