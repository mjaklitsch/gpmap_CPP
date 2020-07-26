#include "SensorDot.h"
#include "Phenotype.h"
#include <vector>

#ifndef SENSORARRAY_H_INCLUDED
#define SENSORARRAY_H_INCLUDED

extern int numberOfSensors;

class SensorArray {
public:
  static std::vector<SensorDot> sensorDotArray;

  SensorArray();

  void recordIntersections(Phenotype *phenotype);

  static float polygonalTriangleInnerAngle;
  static float polygonalTriangleOuterAngle; // only used for sensors

  void initializeSensors();
};

#endif
