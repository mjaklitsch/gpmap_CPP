#include "Genotype.h"
#include <iostream>


std::string Genotype::cellType = "";
float Genotype::theta = 0;
float Genotype::growthDelay = 0;
float Genotype::growthRate = 0;
float Genotype::growthDuration = 0;
float Genotype::speed = 0;
float Genotype::movementDelay = 0;
float Genotype::movementDuration = 0;

Genotype::Genotype(){
    
}

Genotype::Genotype(std::string tempCellType, float tempTheta, float tempGrowthDelay,
  float tempGrowthRate, float tempGrowthDuration, float tempSpeed,
  float tempMovementDelay, float tempMovementDuration) {

  cellType = tempCellType;
  theta = tempTheta;
  growthDelay = tempGrowthDelay;
  growthRate = tempGrowthRate;
  growthDuration = tempGrowthDuration;
  speed = tempSpeed;
  movementDelay = tempMovementDelay;
  movementDuration = tempMovementDuration;
}
