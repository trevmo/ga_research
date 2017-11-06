/**
 * This file contains the implementations of the functions stubbed out in
 * util.h.
 * 
 * @author trevmo
 */

#include "stdafx.h"
#include "util.h"
#include "params.h"

/**
 * Return a random amount of damage from a uniform distribution.
 * @param mean middle of the range of damage
 * @param range amount of variance on either side of the mean
 * @return random value within [mean-range, mean+range]
 */
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
/**
 * Print out info related to the current run of the GA. Use these values
 * for reproducibility of the experiments.
 * @param fs filestream to send the output to
 * @param t time that the experiment was started at
 */
void printHeader(ofstream &fs, time_t t) {
	struct tm * timeinfo;
	timeinfo = localtime(&t);
	fs << "Seed " << t << endl;
	fs << asctime(timeinfo);
	fs << "Attack type: " << attackType << endl;
	fs << "Fixed damage amount: " << damageAmount << endl;
	fs << "Mean damage: " << meanDamage << endl;
	fs << "Range of damamge (+/- this amount): " << rangeDamage << endl;
	fs << "Mutation type: " << mutateType << endl;
	fs << "Mutation size: " << uniformMutateRange << endl;
	fs << "Pop size: " << popSize << endl;
	fs << "Tournament size: " << tournSize << endl;
}
/**
 * Form a filename based off of the time the experiment was started at,
 * the attack type used, and the range of damage used.
 * @param theTime initial time of the experiment (used to seed rand())
 * @param type attack type (see params.h)
 * @param range of damage
 * @return filename
 */
string formFileName(time_t *theTime, int type, int range)
{
	time(theTime);
	srand(*theTime);
	struct tm * timeinfo;
	timeinfo = localtime(theTime);
	string randTime = "";
	randTime += to_string(timeinfo->tm_year);
	randTime += to_string(timeinfo->tm_mon);
	randTime += to_string(timeinfo->tm_mday);
	randTime += to_string(timeinfo->tm_hour);
	randTime += to_string(timeinfo->tm_min);
	randTime += to_string(timeinfo->tm_sec);
	return to_string(type) + "_" + to_string(range) + "_" + randTime + ".csv";
}