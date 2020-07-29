#include "Gene.hpp"
#include <iostream>


//std::string Gene::cellType;
//float Gene::theta;
//float Gene::growthDelay;
//float Gene::growthRate;
//float Gene::growthDuration;
//float Gene::speed;
//float Gene::movementDelay;
//float Gene::movementDuration;

Gene::Gene(){
    
}

Gene::Gene(std::string tempCellType, float tempTheta, float tempGrowthDelay,
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

std::string Gene::getCellType(){
    return cellType;
}
float Gene::getTheta(){
    return theta;
}
float Gene::getGrowthDelay(){
    return growthDelay;
}
float Gene::getGrowthRate(){
    return growthRate;
}
float Gene::getGrowthDuration(){
    return growthDuration;
}
float Gene::getSpeed(){
    return speed;
}
float Gene::getMovementDelay(){
    return movementDelay;
}
float Gene::getMovementDuration(){
    return movementDuration;
}

void Gene::setCellType(std::string type){
    cellType = type;
}
void Gene::setTheta(float t){
    theta = t;
}
void Gene::setGrowthDelay(float gde){
    growthDelay = gde;
}
void Gene::setGrowthRate(float gr){
    growthRate = gr;
}
void Gene::setGrowthDuration(float gdu){
    growthDuration = gdu;
}
void Gene::setSpeed(float s){
    speed = s;
}
void Gene::setMovementDelay(float mde){
    movementDelay = mde;
}
void Gene::setMovementDuration(float mdu){
    movementDuration = mdu;
}
