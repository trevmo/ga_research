#pragma once

class pop {
private:
	indiv the_pop[popSize];
	int best;   // index of the most fit indivdual
	float bestFit;   // fitness of the most fit individual
	float avgFit;    // average fitness of the population
	float avgGenes[genomeLength];   // average value of each gene 
public:
	pop();
	void calcAvgs();
	void print();
	void nextGen();
	int selectParent();
};

pop::pop() {
	calcAvgs();
}

void pop::print() {
	for (int i = 0; i < popSize; i++) {
		the_pop[i].calcFit();
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

void pop::calcAvgs() {
	best = 0;
	bestFit = the_pop[0].getFit();
	avgFit = the_pop[0].getFit();
	for (int i = 1; i < popSize; i++) {
		avgFit += the_pop[i].getFit();
		if (the_pop[i].getFit() > bestFit) {
			best = i;
			bestFit = the_pop[i].getFit();
		}
	}
	avgFit /= popSize;

	for (int g = 0; g < genomeLength; g++) {
		avgGenes[g] = 0;
		for (int i = 1; i < popSize; i++) {
			avgGenes[g] += the_pop[i].getGene(g);
		}
		avgGenes[g] /= popSize;
	}
}

void pop::nextGen() {
	indiv temp[popSize];
	temp[0].copy(the_pop[best]);  // elitism, make two copies of the best individual
	temp[1].copy(the_pop[best]);
	int p1, p2;
	for (int i = 2; i < popSize; i += 2) {
		p1 = selectParent();
		p2 = selectParent();
		temp[i].copy(the_pop[p1]);
		temp[i + 1].copy(the_pop[p2]);
		//temp[i].crossover(temp[i+1]);   // no crossover, because there's only one gene
		temp[i].mutate();
		temp[i + 1].mutate();
	}
	for (int i = 0; i < popSize; i++) {
		the_pop[i].copy(temp[i]);
	}
}

int pop::selectParent() {
	int best, temp;
	int bestFit;
	best = rand() % popSize;
	bestFit = the_pop[best].getFit();
	for (int i = 1; i < tournSize; i++) {
		temp = rand() % popSize;
		if (the_pop[temp].getFit() > bestFit) {
			best = temp;
			bestFit = the_pop[best].getFit();
		}
	}
	return best;
}
