// hp_analysis.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<random>
#include"indiv.h"
#include"pop.h"
using namespace std;

void printHeader(time_t);

int main() {
	time_t theTime;
	time(&theTime);
	srand(theTime);
	printHeader(theTime);  // record the time, which is the random seed, so experiments can be rerun.
	pop p;
	p.print();
	for (int g = 0; g < 100; g++) {  // 100 generations
		p.nextGen();
		p.print();
	}
	return 0;
}

// prints information about the run into the data header
void printHeader(time_t t) {
	struct tm * timeinfo;
	timeinfo = localtime(&t);
	printf("Seed %d\n", t);
	printf("%s", asctime(timeinfo));
	printf("Attack type: %d\n", attackType);
	printf("Fixed damage amount: %d\n", damageAmount);
	printf("Mean damage: %f\n", meanDamage);
	printf("Range of damage (+/- this amount): %f\n", rangeDamage);
	printf("Mutation type: %d\n", mutateType);
	printf("Mutation size: %d\n", uniformMutateRange);
	printf("Pop size: %d\n", popSize);
	printf("Tournament size: %d\n", tournSize);

}