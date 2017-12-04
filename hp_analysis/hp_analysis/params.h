#pragma once

/**
* This file contains global variables used for controlling aspects of the project.
*
* @author tsoule
* @author trevmo
*/

// currently two genes - health and armor
const int genomeLength = 2;
// maximum initial health
const int maxInitHealth = 10;
// maximum initial armor
const int maxInitArmor = 5;
// 0 - uniform
const int mutateType = 0;
// -5 to 5
const int uniformMutateRange = 6;
const int popSize = 100;
// 0 - Constant Damage, 1 - Uniform Damage, 2 - Gaussian Damage
extern int attackType;
// Constant Damage amount
const int damageAmount = 15;
// mean damage for uniform or Gaussian
const double meanDamage = 15;
// range of damage for uniform or Gaussian (+/- this amount)
extern double rangeDamage;
const int tournSize = 3;
