#pragma once

/**
 * This file contains the interface for various utility functions used
 * throughout the project.
 *
 * @author trevmo
 */

#include <cstdlib>
#include <cmath>
#include <limits>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

double uniformDistDamage(double mean, double range);
double gaussianDamage(double mean, double stdDev);

void printHeader(ofstream &fs, time_t);
string formFileName(time_t *theTime, int type, int range);