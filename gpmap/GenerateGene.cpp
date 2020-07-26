#include "GenerateGene.h"
#include "random.h"
#include "PolygonCalculations.h"
#include "GlobalVariables.h"
#include <cmath>
#include <iostream>

using namespace timer;

// Genotype Generation Variables
int minDuration = 20;
int maxDuration = 40;
int minDelay = 0;
int maxDelay = 0; // for testing
//int maxDelay = timer::ticks - maxDuration;
int minSpeed = 4;
int maxSpeed = 12;
int minGrowthRate = 3;
int maxGrowthRate = 7;

Genotype returnRandomNewGenotype(std::string cellType) {
  std::string type = "";

  if (cellType != "") {
    type = cellType;
  } else {
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

  Genotype newGenotype(type, theta, growthDelay, growthRate, growthDuration, speed, movementDelay, movementDuration);
  printGenotype(newGenotype);
  return newGenotype;
}

void printGenotype(Genotype genotype) {
  // std::cout << "=============================" << '\n';
  // std::cout << "/* message */" << '\n';
  // std::cout << "/* message */" << '\n';
  // std::cout << "/* message */" << '\n';
  // std::cout << "/* message */" << '\n';
  // std::cout << "/* message */" << '\n';
  // std::cout << "/* message */" << '\n';
  // std::cout << "/* message */" << '\n';
  printf("=============================");
  printf("type: %s\n", genotype.cellType.c_str());
  if(degrees(genotype.theta) < 0){
    printf("angle: %f\n", (degrees(genotype.theta) + 360));
  } else {
    printf("angle: %f\n", degrees(genotype.theta));
  }
  printf("growthDelay: %f\n", genotype.growthDelay);
  printf("growthRate: %f\n", genotype.growthRate);
  printf("growthDuration: %f\n", genotype.growthDuration);
  printf("speed: %f\n", genotype.speed);
  printf("movementDelay: %f\n", genotype.movementDelay);
  printf("movementDuration: %f\n", genotype.movementDuration);
}
