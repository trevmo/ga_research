#pragma once

/**
* This file contains global variables used for controlling aspects of the project.
*
* @author tsoule
* @author trevmo
*/

struct Damage {
	int type;
	double mean;
	double range;
	bool isVariable;
};
extern struct Damage DAMAGE;

struct Mutate {
	int type; // currently only uniform (0) is supported
	int range; // set for the range of mutation values
	int skipGene; // set to index of gene to skip; -1, otherwise
	bool isVariable;
};
extern struct Mutate MUTATE;