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
};
extern struct Damage DAMAGE;

struct Mutate {
	int type;
	int range;
	bool isVariable;
};
extern struct Mutate MUTATE;