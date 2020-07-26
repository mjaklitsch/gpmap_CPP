#include "SensorDot.h"
#include <iostream>


  std::vector<int> SensorDot::connections;

  float SensorDot::xPos = 0;
  float SensorDot::yPos = 0;

  SensorDot::SensorDot(float tempxPos, float tempyPos){
    xPos = tempxPos;
    yPos = tempyPos;
  }
