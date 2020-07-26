#include "SensorArray.h"
#include "Phenotype.h"
#include "PolygonCalculations.h"
#include "GlobalVariables.h"
#include <cmath>
#include <algorithm>
#include <iostream>

// double PI = 2*acos(0.0);

using namespace locks;

int numberOfSensors = 8; // 30 is the max for unknown reasons

std::vector<SensorDot> SensorArray::sensorDotArray;

SensorArray::SensorArray() {
    // nothing needed here yet, this class exists for organization
}

void SensorArray::recordIntersections(Phenotype *phenotype) {
    long cellsInPhenotype = sizeof(&phenotype->cellArray) / sizeof(Cell);
    
    for (int i = 0; i < cellsInPhenotype; i++) {
        if (isCellOverlappingWithPolygon(phenotype->cellArray[i])) {
            float tempTheta = phenotype->cellArray[i].genotype.theta;
            float theta;
            if (tempTheta < 0) { // add 2 PI to get rid of negative theta
                theta = tempTheta + (2 * M_PI);
            } else {
                theta = tempTheta;
            }
            printf("Cell %d\n", i);
            int sensorIndex = getIndexOfClosestSensorDotToTheta(theta);
            if (std::find(sensorDotArray[sensorIndex].connections.begin(),
                          sensorDotArray[sensorIndex].connections.end(),
                          i) == sensorDotArray[sensorIndex].connections.end()) {
                (sensorDotArray[sensorIndex].connections).push_back(i);
            }
        }
    }
//    while(i<cellsInPhenotype)
//        //spin
//        ;
//    locks::moveCellsLock = 0;
    printf("g");
    
}

float SensorArray::polygonalTriangleInnerAngle = 360 / numberOfSensors;
float SensorArray::polygonalTriangleOuterAngle = (180 - polygonalTriangleInnerAngle) / 2; // only used for sensors

void SensorArray::initializeSensors() {
    float lastX = 0;
    float lastY = 0;
    float x = 0;
    float y = 0;
    for (float i = 0; i < 360; i += polygonalTriangleInnerAngle) {
        lastX = x;
        lastY = y;
        x = polarXAngle(i);
        y = polarYAngle(i);
        
        int sensorArrayIndex = int(i/polygonalTriangleInnerAngle);
        sensorDotArray[sensorArrayIndex] = SensorDot(x, y);
    }
//    while(i<360);
    locks::moveCellsLock = 0;
}
