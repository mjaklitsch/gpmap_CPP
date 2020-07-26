#include <string>
#ifndef GENOTYPE_H_INCLUDED
#define GENOTYPE_H_INCLUDED

class Genotype {
public:
    static std::string cellType;
    static float theta;
    static float growthDelay;
    static float growthRate;
    static float growthDuration;
    static float speed;
    static float movementDelay;
    static float movementDuration;
    
    Genotype();
    Genotype(std::string tempCellType, float tempTheta, float tempGrowthDelay,
             float tempGrowthRate, float tempGrowthDuration, float tempSpeed,
             float tempMovementDelay, float tempMovementDuration);
};

#endif
