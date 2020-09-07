#include "SensorArray.hpp"
#include "Genotype.hpp"
#include "PolygonCalculations.hpp"
#include "GlobalVariables.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>


int numberOfSensors = 8;

//std::vector<SensorDot> SensorArray::sensorDotArray;

SensorArray::SensorArray() {
    // nothing needed here yet, this class exists for organization
}

void SensorArray::recordSensorAttachments(Genotype *genotype) {
    for (int i = 0; i < global::numberOfCellsCreated; i++) {
        if (!genotype->cellArray.getConnectedToSensor(i)){
            if (isCellOverlappingWithPolygon(i, &(genotype->cellArray))) {
                float tempTheta = genotype->cellArray.getTheta(i);
                float theta;
                if (tempTheta < 0) { // add 2 PI to get rid of negative theta
                    theta = tempTheta + (2 * M_PI);
                } else {
                    theta = tempTheta;
                }
                int sensorIndex = getIndexOfClosestSensorDotToTheta(theta);
                genotype->cellArray.setConnectedToSensor(i,true);
                (sensorDotArray[sensorIndex].connections).emplace_back(i);
            }
        }
    }
}

float SensorArray::polygonalTriangleInnerAngle = 360 / numberOfSensors;
float SensorArray::polygonalTriangleOuterAngle = (180 - polygonalTriangleInnerAngle) / 2; // only used for sensors

void SensorArray::initializeSensors() {
    // Build "numberOfSensors" sensor dots at even intervals around the polygon
    float lastX = 0;
    float lastY = 0;
    float x = 0;
    float y = 0;
    for (float i = 0; i < 360; i += polygonalTriangleInnerAngle) {
        lastX = x;
        lastY = y;
        x = polarXAngle(i);
        y = polarYAngle(i);
        
        sensorDotArray.emplace_back(SensorDot(x, y));
    }
}
