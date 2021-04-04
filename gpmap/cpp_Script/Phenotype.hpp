#include "SensorArray.hpp"
#include "Genotype.hpp" //includes "Cell.h"
#include <vector>

#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

// int[] toArray(ArrayList<Integer> arrayList);

void printIntegerMatrix(std::vector<std::vector<int> > integerMatrix);
void printFloatMatrix(std::vector<std::vector<float> > floatMatrix);
void printboolMatrix(std::vector<std::vector<bool> > boolMatrix);

class Phenotype {
public:
     SensorArray* sensorArray;
     Genotype* phenotype;
     int numberOfCells;
     CellArray *cellArray;
    
     int numberOfNeurons;
     int numberOfPhotoSensors;
     int numberOfIRSensors;
     int numberOfRightMotors;
     int numberOfLeftMotors;
    
     std::vector<std::vector<int> > attachmentsBySensorIndex; // x is sensor index, y will be an array of attachments by their cell array index
     std::vector<std::vector<bool> > cellConnections;
     std::vector<std::vector<float> > cellConnectionWeights;
    
    
    Phenotype(SensorArray* tempSensorArray, Genotype* tempPhenotype, CellArray *tempCellArray);
    
    void printRobot();
};

#endif
