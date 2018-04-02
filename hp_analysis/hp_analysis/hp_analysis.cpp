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
	int generations = 250;
	GeneticAlgorithm *ga = NULL;
	//use uniform mutation
	MUTATE.type = 0;
	MUTATE.skipGene = -1;
	MUTATE.isVariable = true;

	//uniform and Gaussian damage
	DAMAGE.mean = 15;
	for (int type = 1; type < 3; type++) {
		DAMAGE.type = type;
		cout << "Damage type: " << type << endl;
		//range for uniform mutation
		for (int mrange = 7; mrange < 8; mrange += 2) {
			MUTATE.range = mrange;
			cout << "\tMutate range: " << mrange << endl;
			//range of damage for uniform; std dev for Gaussian
			for (int drange = 0; drange < 16; drange++) {
				DAMAGE.range = drange;
				cout << "\t\tDamage range: " << drange << endl;
				ga = new GeneticAlgorithm(DAMAGE.type, DAMAGE.range, 1000);
				for (int iter = 0; iter < iterations; iter++) {
					cout << "\t\t\tTrial: " << iter << endl;
					ga->run(iter, generations, true);
					ga->reset();
				}
			}
		}
	}
	return 0;
}
