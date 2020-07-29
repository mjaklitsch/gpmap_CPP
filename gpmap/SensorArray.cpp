#include "SensorArray.hpp"
#include "Phenotype.hpp"
#include "PolygonCalculations.hpp"
#include "GlobalVariables.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>


int numberOfSensors = 8; // 30 is the max for unknown reasons

//std::vector<SensorDot> SensorArray::sensorDotArray;

SensorArray::SensorArray() {
    // nothing needed here yet, this class exists for organization
}

void SensorArray::recordIntersections(Phenotype *phenotype) {
    for (int i = 0; i < global::numberOfCellsCreated; i++) {
        if (!phenotype->cellArray.getConnectedToSensor(i)){
            if (isCellOverlappingWithPolygon(i, &(phenotype->cellArray))) {
                float tempTheta = phenotype->cellArray.getTheta(i);
                float theta;
                if (tempTheta < 0) { // add 2 PI to get rid of negative theta
                    theta = tempTheta + (2 * M_PI);
                } else {
                    theta = tempTheta;
                }
                int sensorIndex = getIndexOfClosestSensorDotToTheta(theta);
//                if (std::find(sensorDotArray[sensorIndex].connections.begin(),
//                              sensorDotArray[sensorIndex].connections.end(),
//                              i) == sensorDotArray[sensorIndex].connections.end()) { // if we dont find i in the connections that have been made
                
                phenotype->cellArray.setConnectedToSensor(i,true);
                (sensorDotArray[sensorIndex].connections).push_back(i);
//                }
            }
        }
    }
    //    while(i<cellsInPhenotype)
    //        //spin
    //        ;
    //    locks::moveCellsLock = 0;
//    printf("g");
    
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
        
        sensorDotArray.push_back(SensorDot(x, y));
    }
}
