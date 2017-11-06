/**
 * This serves as the main file of the project. It controls the execution
 * of the GA for testing and data collection purposes.
 *
 * @author tsoule
 * @author trevmo
 */

#include "stdafx.h"
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<random>
#include <string>
#include <chrono>
#include <thread>
#include"indiv.h"
#include"pop.h"
#include "util.h"
#include "params.h"
using namespace std;

int attackType;
double rangeDamage;

int main() {
	time_t theTime;
	string filename;
	//uniform and Gaussian damage
	for (int type = 1; type < 3; type++) {
		attackType = type;
		//range of damage for uniform; std dev for Gaussian
		for (int range = 1; range < 6; range++) {
			//run the GA 5 times per combo
			for (int iter = 0; iter < 5; iter++) {
				filename = formFileName(&theTime, type, range);
				rangeDamage = range;
				Population p;
				p.openCsv(filename, theTime);
				p.printToCsv(0);
				//100 generations each
				for (int g = 0; g < 100; g++) {
					p.nextGen();
					p.printToCsv(g + 1);
				}
				p.closeCsv();
				this_thread::sleep_for(chrono::milliseconds(1000));
			}
		}
	}	
	return 0;
}