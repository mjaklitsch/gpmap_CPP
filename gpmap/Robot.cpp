#include "Robot.h"
#include "GlobalVariables.h"
#include <iostream>
#include <iomanip>

void printIntegerMatrix(std::vector<std::vector<int> > integerMatrix) {
    for (int i = 0; i < integerMatrix.size(); i++) {
        printf("%d: ", i);
        long innerSize = integerMatrix[i].size();
        for (int j = 0; j < innerSize; j++) {
            printf("[%d] ", integerMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printFloatMatrix(std::vector<std::vector<float> > floatMatrix) {
    std::setw(2);
    for (int i = 0; i < floatMatrix.size(); i++) {
        printf("_%d_", i);
    }
    printf("\n");
    for (int i = 0; i < floatMatrix.size(); i++) {
        printf("%d: ", i);
        long innerSize = floatMatrix[i].size();
        for (int j = 0; j < innerSize; j++) {
            printf("[%f] ", floatMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printboolMatrix(std::vector<std::vector<bool> > boolMatrix) {
    printf("    ");
    for (int i = 0; i < boolMatrix.size(); i++) {
        if(i<10){
            printf("__%d___", i);
        } else {
            printf("__%d__", i);
        }
    }
    printf("\n");
    for (int i = 0; i < boolMatrix.size(); i++) {
        printf("%d: ", i);
        long innerSize = boolMatrix[i].size();
        for (int j = 0; j < innerSize; j++) {
            printf("%s", boolMatrix[i][j] ? " TRUE" : " false");
        }
        printf("\n");
    }
    printf("\n");
}

SensorArray* Robot::sensorArray;
Phenotype* Robot::phenotype;
std::vector<Cell> *Robot::cellArray;
int Robot::numberOfCells = 0;

int Robot::numberOfNeurons = 0;
int Robot::numberOfPhotoSensors = 0;
int Robot::numberOfIRSensors = 0;
int Robot::numberOfRightMotors = 0;
int Robot::numberOfLeftMotors = 0;

std::vector<std::vector<int> > Robot::attachmentsBySensorIndex; // x is sensor index, y will be an array of attachments by their cell array index
std::vector<std::vector<bool> > Robot::cellConnections;
std::vector<std::vector<float> > Robot::cellConnectionWeights;


Robot::Robot(SensorArray *tempSensorArray, Phenotype *tempPhenotype, std::vector<Cell> *tempCellArray) {
    sensorArray = tempSensorArray;
    phenotype = tempPhenotype;
    cellArray = tempCellArray;
    
    for (int i = 0; i < numberOfCellsCreated; i++) {
        std::cout<< cellArray->at(i).genotype.cellType;
        printf(" :  %d.  ", i);
        if(cellArray->at(i).genotype.cellType == "N") {
            numberOfNeurons++;
            numberOfCells++;
        } else if(cellArray->at(i).genotype.cellType == "R"){
            numberOfIRSensors++;
            numberOfCells++;
        } else if(cellArray->at(i).genotype.cellType == "P"){
            numberOfPhotoSensors++;
            numberOfCells++;
        } else if(cellArray->at(i).genotype.cellType == "LM"){
            numberOfLeftMotors++;
            numberOfCells++;
        } else if(cellArray->at(i).genotype.cellType == "RM"){
            numberOfRightMotors++;
            numberOfCells++;
        }
    }
    
    for (int i = 0; i < numberOfSensors; i++) {
        std::vector<int> connectionArray = sensorArray->sensorDotArray[i].connections;
        attachmentsBySensorIndex.push_back(connectionArray);
        
    }
    
    // cellConnections = new bool[numberOfCells][numberOfCells];
    // cellConnectionWeights = new float[numberOfCells][numberOfCells];
    
    
    //    cellConnectionWeights.resize(numberOfCells);
    //    cellConnections.resize(numberOfCells);
    //    for (int x = 0; x < numberOfCells; x++) {
    //        cellConnectionWeights[x].resize(numberOfCells);
    //        cellConnections[x].resize(numberOfCells);
    //        for (int y = 0; y < numberOfCells; y++) {
    //            cellConnectionWeights[x][y] = 0.0;
    //            cellConnections[x][y] = false;
    //        }
    //    }
    
    cellConnectionWeights.resize(numberOfCells);
    cellConnections.resize(numberOfCells);
    for (int x = 0; x < numberOfCells; x++) {
        cellConnectionWeights[x].resize(numberOfCells);
        cellConnections[x].resize(numberOfCells);
        for (int y = 0; y < numberOfCells; y++) {
            if (phenotype->hasSpecificDirectionalConnection(x, y)) {
                cellConnections[x][y] = true;
                float connectionWeight = phenotype->getSpecificDirectionalConnectionWeight(x, y);
                cellConnectionWeights[x][y] = connectionWeight;
            } else if (phenotype->hasSpecificDirectionalConnection(y, x)) {
                cellConnections[y][x] = true;
                float connectionWeight = phenotype->getSpecificDirectionalConnectionWeight(y, x);
                cellConnectionWeights[y][x] = connectionWeight;
            } else {
                cellConnections[x][y] = false;
                cellConnectionWeights[x][y] = 0.0;
            }
        }
    }
}


void Robot::printRobot() {
    printf("Number of Cells: %d\n", numberOfCells);
    printf("Number of Neurons: %d\n", numberOfNeurons);
    printf("Number of IR Sensors: %d\n", numberOfIRSensors);
    printf("Number of Photo Sensors: %d\n", numberOfPhotoSensors);
    printf("Number of Right Motors: %d\n", numberOfRightMotors);
    printf("Number of Left Motors: %d\n", numberOfLeftMotors);
    printf("Physical Sensor Attachments by Index: \n");
    printIntegerMatrix(attachmentsBySensorIndex);
    printf("Connections by Index, X to Y:\n");
    printboolMatrix(cellConnections);
    printf("Connection Weights by Index, X to Y:\n");
    printFloatMatrix(cellConnectionWeights);
}
