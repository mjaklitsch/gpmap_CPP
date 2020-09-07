#include "SensorDot.hpp"
#include "Genotype.hpp"
#include <vector>

#ifndef SENSORARRAY_H_INCLUDED
#define SENSORARRAY_H_INCLUDED

extern int numberOfSensors;

class SensorArray {
public:
    std::vector<SensorDot> sensorDotArray;
    
    SensorArray();
    
    void recordSensorAttachments(Genotype *phenotype);
    
    static float polygonalTriangleInnerAngle;
    static float polygonalTriangleOuterAngle; // only used for sensors
    
    void initializeSensors();
};

#endif
