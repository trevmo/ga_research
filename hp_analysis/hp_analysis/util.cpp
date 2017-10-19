#include "stdafx.h"
#include "util.h"

double uniformDistDamage(double mean, double range)
{
	return mean - range + (rand() % (int)(2 * range + 1));
}
/**
* Generate values from a normal distribution using the Box-Muller Transform method.
* Adapted from: https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform#Implementation
* @param mean center of distribution curve
* @param stdDev range of the distribution curve
*/
double gaussianDamage(double mean, double stdDev) {
	//epsilon ~ 2.2x10^-308
	static const double epsilon = std::numeric_limits<double>::min();
	static const double twoPi = 2.0*3.14159265358979323846;

	thread_local double z1;
	thread_local bool generate;
	generate = !generate;

	//generate is maintained as a thread_local (similar to static) variable
	//so this condition alternates the return of the independent, random variables
	//per function call
	if (!generate)
		return z1 * stdDev + mean;

	double u1, u2;
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	} while (u1 <= epsilon);

	double z0;
	z0 = sqrt(-2.0 * log(u1)) * cos(twoPi * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(twoPi * u2);
	return z0 * stdDev + mean;
}