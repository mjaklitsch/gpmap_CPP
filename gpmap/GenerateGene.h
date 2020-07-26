#include "Genotype.h"
#include <string>

#ifndef GENERATEGENE_H_INCLUDED
#define GENERATEGENE_H_INCLUDED
// double PI = 2*acos(0.0);
// Genotype Generation Variables
extern int minDuration;
extern int maxDuration;
extern int minDelay;
//int maxDelay = 0; // for testing
extern int maxDelay;
extern int minSpeed;
extern int maxSpeed;
extern int minGrowthRate;
extern int maxGrowthRate;

Genotype returnRandomNewGenotype(std::string cellType);

void printGenotype(Genotype genotype);

#endif
