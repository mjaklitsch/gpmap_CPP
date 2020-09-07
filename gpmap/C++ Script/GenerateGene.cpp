#include "GenerateGene.hpp"
#include "random.hpp"
#include "PolygonCalculations.hpp"
#include "GlobalVariables.hpp"
#include <cmath>
#include <iostream>

using namespace timer;

// Genotype Generation Variables
int minDuration = 20;
int maxDuration = 40;
int minDelay = 0;
//int maxDelay = 0; // for testing
int maxDelay = timer::ticks - maxDuration;
int minSpeed = 4;
int maxSpeed = 12;
int minGrowthRate = 3;
int maxGrowthRate = 7;

Gene returnRandomNewGenotype(std::string cellType) {
    std::string type = "";
    
    if (cellType != "") {
        type = cellType;
    } else { // on empty string input
        int typeNumber = intRandom(0,4);
        switch(typeNumber) {
            case 0:
                type = "N";
                break;
            case 1:
                type = "P";
                break;
            case 2:
                type = "R";
                break;
            case 3:
                type = "LM";
                break;
            case 4:
                type = "RM";
                break;
        }
    }
    
    float theta;
    
    if (type == "LM") {
        theta = floatRandom((M_PI / 2), (3 * (M_PI / 2)));
    } else if (type == "RM") {
        theta = floatRandom(-(M_PI / 2), (M_PI / 2));
        if(theta < 0){
            theta+=(2*M_PI);
        }
    } else {
        theta = floatRandom(0, (2*M_PI));
    }
    // these are defined in the main file
    int speed = intRandom(minSpeed, maxSpeed);
    int movementDelay = intRandom(minDelay, maxDelay);
    int movementDuration = intRandom(minDuration, maxDuration);
    int growthDelay = intRandom(movementDelay - 5, movementDelay + 5);
    int growthRate = intRandom(minGrowthRate, maxGrowthRate);
    int growthDuration = intRandom(minDuration, maxDuration);
    
    Gene newGenotype(type, theta, growthDelay, growthRate, growthDuration, speed, movementDelay, movementDuration);
    printGenotype(newGenotype);
    return newGenotype;
}

void printGenotype(Gene gene) {
    if(global::printStuff){
        printf("=============================\n");
        printf("type: %s\n", gene.getCellType().c_str());
        if(degrees(gene.getTheta()) < 0){
            printf("angle: %f\n", degrees(gene.getTheta() + 360));
            printf("theta: %f\n", gene.getTheta() + (2*M_PI));
        } else {
            printf("angle: %f\n", degrees(gene.getTheta()));
            printf("theta: %f\n", gene.getTheta());
        }
        printf("growthDelay: %f\n", gene.getGrowthDelay());
        printf("growthRate: %f\n", gene.getGrowthRate());
        printf("growthDuration: %f\n", gene.getGrowthDuration());
        printf("speed: %f\n", gene.getSpeed());
        printf("movementDelay: %f\n", gene.getMovementDelay());
        printf("movementDuration: %f\n", gene.getMovementDuration());
    }
}
