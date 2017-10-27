// hp_analysis.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<random>
#include <string>
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
			filename = formFileName(&theTime, type, range);
			rangeDamage = range;
			pop p;
			p.openCsv(filename, theTime);
			p.printToCsv(0);
			//100 generations each
			for (int g = 0; g < 100; g++) {
				p.nextGen();
				p.printToCsv(g+1);
			}
			p.closeCsv();
		}
	}	
	return 0;
}