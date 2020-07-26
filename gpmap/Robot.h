#include "SensorArray.h"
#include "Phenotype.h" //includes "Cell.h"
#include <vector>

#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

// int[] toArray(ArrayList<Integer> arrayList);

void printIntegerMatrix(std::vector<std::vector<int> > integerMatrix);
void printFloatMatrix(std::vector<std::vector<float> > floatMatrix);
void printboolMatrix(std::vector<std::vector<bool> > boolMatrix);

class Robot {
public:
    static SensorArray* sensorArray;
    static Phenotype* phenotype;
    static int numberOfCells;
    static std::vector<Cell> *cellArray;
    
    static int numberOfNeurons;
    static int numberOfPhotoSensors;
    static int numberOfIRSensors;
    static int numberOfRightMotors;
    static int numberOfLeftMotors;
    
    static std::vector<std::vector<int> > attachmentsBySensorIndex; // x is sensor index, y will be an array of attachments by their cell array index
    static std::vector<std::vector<bool> > cellConnections;
    static std::vector<std::vector<float> > cellConnectionWeights;
    
    
    Robot(SensorArray* tempSensorArray, Phenotype* tempPhenotype,  std::vector<Cell> *tempCellArray);
    
    void printRobot();
};

#endif
