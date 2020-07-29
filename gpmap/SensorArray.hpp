#include "SensorDot.hpp"
#include "Phenotype.hpp"
#include <vector>

#ifndef SENSORARRAY_H_INCLUDED
#define SENSORARRAY_H_INCLUDED

extern int numberOfSensors;

class SensorArray {
public:
    std::vector<SensorDot> sensorDotArray;
    
    SensorArray();
    
    void recordIntersections(Phenotype *phenotype);
    
    static float polygonalTriangleInnerAngle;
    static float polygonalTriangleOuterAngle; // only used for sensors
    
    void initializeSensors();
};

#endif
