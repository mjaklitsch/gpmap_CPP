#include "Cell.h"
#include "GenerateGene.h"
#include "GlobalVariables.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace timer;

int Cell::index = -1;
// ArrayList<Connection> cellConnections = new ArrayList<Connection>();

Genotype Cell::genotype;
float Cell::xPos = 0;
float Cell::yPos = 0;
float Cell::diameter = 0;
float Cell::radius = 0;

float Cell::xSpeed = 0;
float Cell::ySpeed = 0;
float Cell::growthRate = 0;

bool Cell::doneMoving = false;
bool Cell::doneGrowing = false;

Cell::Cell(){
}

//Cell::Cell(const Cell &C2){ //copy
//    genotype = C2.genotype;
//    index = C2.index;
//}

Cell::Cell(std::string cellType, int tempIndex) {
  genotype = returnRandomNewGenotype(cellType);
  index = tempIndex;
}

//Cell::~Cell(){
//};

bool Cell::isMotor() {
  if (genotype.cellType == "LM" || genotype.cellType == "RM") {
    return true;
  } else {
    return false;
  }
}

bool Cell::isSensor() {
  if (genotype.cellType == "R" || genotype.cellType == "P") {
    return true;
  } else {
    return false;
  }
}

bool Cell::isNeuron() {
  if (genotype.cellType == "N") {
    return true;
  } else {
    return false;
  }
}

void Cell::setCellSpeedAndGrowth() {
  if (timer::currentTick > genotype.growthDelay) {
    growthRate = (genotype.growthRate / timer::actionSpread);
  }

  if (timer::currentTick > genotype.movementDelay) {
    float speed = (genotype.speed / timer::actionSpread);
    xSpeed = speed * cos(genotype.theta);
    ySpeed = speed * sin(genotype.theta);
  }
}

void Cell::moveAndMorphCell() {
  if (!doneMoving && (timer::currentTick - genotype.movementDelay < genotype.movementDuration)) {
    xPos += xSpeed;
    yPos -= ySpeed;
  } else {
    doneMoving = true;
  }

  if (!doneGrowing && (timer::currentTick - genotype.growthDelay < genotype.growthDuration)) {
    diameter += growthRate;
    radius = diameter/2;
  } else {
    doneGrowing = true;
  }
}

void Cell::printGenes() {
  printGenotype(genotype);
}
