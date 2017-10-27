#pragma once
const int genomeLength = 1;   // currently only one gene - health
const int maxInitHealth = 10;  // maximum initial health
const int mutateType = 0;  // 0-uniform
const int uniformMutateRange = 6; // -5 to 5
const int popSize = 100;
extern int attackType;  // 0 - Constant Damage, 1 - Uniform Damage, 2 - Gaussian Damage
const int damageAmount = 15;  // Constant Damage amount
const double meanDamage = 15;  // mean damage for uniform or Gaussian
extern double rangeDamage;  // range of damage for uniform or Gaussian (+/- this amount)
const int tournSize = 3;
