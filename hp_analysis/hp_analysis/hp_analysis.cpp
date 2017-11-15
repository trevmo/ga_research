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

void runGA(int iter, int type, int range);

int main() {
	int iterations = 20;
	//run just on constant damage as a control test
	attackType = 0;
	for (int c = 0; c < iterations; c++)
		runGA(c, attackType, 0);
	//uniform and Gaussian damage
	for (int type = 1; type < 3; type++) {
		attackType = type;
		//range of damage for uniform; std dev for Gaussian
		for (int range = 1; range < 6; range++) {
			//run the GA 5 times per combo
			for (int iter = 0; iter < iterations; iter++) {
				runGA(iter, type, range);
			}
		}
	}	
	return 0;
}

void runGA(int iter, int type, int range) {
	time_t theTime;
	time(&theTime);
	srand(theTime);
	rangeDamage = range;
	Population p;
	p.openCsv(formFileName(iter, type, range), theTime);
	p.printToCsv(0);
	int generations = 100;
	for (int g = 0; g < generations; g++) {
		p.nextGen();
		p.printToCsv(g + 1);
	}
	p.closeCsv();
	this_thread::sleep_for(chrono::milliseconds(1000));
}