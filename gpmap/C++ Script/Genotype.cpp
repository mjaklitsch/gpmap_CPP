#include "Genotype.hpp"
#include "random.hpp"
#include "GlobalVariables.hpp"
#include "PolygonCalculations.hpp"
#include "CellArrayScaffold.hpp"
#include <iostream>
#include <iomanip>


int Genotype::numberOfCells;
std::vector<Connection> Genotype::connectionVector;
CellArray Genotype::cellArray;

// float partCost; // later implementation

Genotype::Genotype(int minNeurons, int maxNeurons, int minPhotoSensors,
                     int maxPhotoSensors, int minIRSensors, int maxIRSensors,
                     int minLeftMotors, int maxLeftMotors, int minRightMotors,
                     int maxRightMotors, bool testMode) {
    if(testMode){
        cellArray = cellArrayScaffold();
        numberOfCells = cellArray.getSize();
        global::numberOfCellsCreated = numberOfCells; //global record
    } else{
        
        int neurons = intRandom(minNeurons, maxNeurons);
        int photoSensors = intRandom(minPhotoSensors, maxPhotoSensors);
        int irSensors = intRandom(minIRSensors, maxIRSensors);
        int leftMotors = intRandom(minLeftMotors, maxLeftMotors);
        int rightMotors = intRandom(minRightMotors, maxRightMotors);
        
        numberOfCells = neurons + photoSensors + irSensors + leftMotors + rightMotors;
        global::numberOfCellsCreated = numberOfCells; //global record
        int arrayIndex = 0;
        
        for (int i = 0; i < neurons; i++) {
//            Cell nextCell = Cell("N", (arrayIndex + i));
//            cellArray.add(nextCell);
            cellArray.emplace("N", (arrayIndex + i));
        }
        arrayIndex += neurons;
        
        for (int i = 0; i < photoSensors; i++) {
//            Cell nextCell = Cell("P", (arrayIndex + i));
//            cellArray.add(nextCell);
            cellArray.emplace("P", (arrayIndex + i));
        }
        arrayIndex += photoSensors;
        
        for (int i = 0; i < irSensors; i++) {
//            Cell nextCell = Cell("R", (arrayIndex + i));
//            cellArray.add(nextCell);
            cellArray.emplace("R", (arrayIndex + i));
        }
        arrayIndex += irSensors;
        
        for (int i = 0; i < leftMotors; i++) {
//            Cell nextCell = Cell("LM", (arrayIndex + i));
//            cellArray.add(nextCell);
            cellArray.emplace("LM", (arrayIndex + i));
        }
        arrayIndex += leftMotors;
        
        for (int i = 0; i < rightMotors; i++) {
//            Cell nextCell = Cell("RM", (arrayIndex + i));
//            cellArray.add(nextCell);
            cellArray.emplace("RM", (arrayIndex + i));
        }
        arrayIndex += rightMotors;
    }
}

void Genotype::addConnection(int i, int j) {
    cellArray.addIndicesOfConnectionToCells(i, j);
    connectionVector.emplace_back(Connection(i, j, &cellArray));
}

void Genotype::moveCells() {
    for (int i = 0; i < numberOfCells; i++) {
        cellArray.moveAndMorphCell(i);
        cellArray.setCellSpeedAndGrowth(i);
    }
}

void Genotype::recordIntersections() {
    for (int i = 0; i < numberOfCells; i++) {
        for (int j = i+1; j < numberOfCells; j++) {
            if(((!cellArray.getCell(i).getDoneMoving() || !cellArray.getCell(i).getDoneGrowing()) || // If both have not stopped moving and growing
                 (!cellArray.getCell(j).getDoneMoving() || !cellArray.getCell(j).getDoneGrowing())) &&
                ((cellArray.getCell(i).getDiameter() > 0) && (cellArray.getCell(j).getDiameter() > 0)) && // and if both have spawned
               !((cellArray.isMotor(i) && cellArray.isMotor(j)) ||
                 (cellArray.isSensor(i) && cellArray.isSensor(j)))){ // and if a connection between types is possible
                
                float ixPos = cellArray.getXPos(i);
                float iyPos = cellArray.getYPos(i);
                float jxPos = cellArray.getXPos(j);
                float jyPos = cellArray.getYPos(j);
                
                if ((cellArray.getRadius(i) + cellArray.getRadius(j)) > distanceBetween(ixPos, iyPos, jxPos, jyPos)) {
                    // if the two are overlapping
                    if (!hasConnection(i, j)) { // if no connection has been recorded yet
                        addConnection(i, j);
                    }
                }
            }
        }
    }
}

void Genotype::finalizeAllConnections() {
    long links = connectionVector.size();
    for (int i = 0; i < links; i++) {
        connectionVector.at(i).finalizeThisConnection();
    }
}


bool Genotype::hasSpecificDirectionalConnection(int cellFromIndex, int cellToIndex) {
    long links = connectionVector.size();
    for (int i = 0; i < links; i++) {
        if (connectionVector.at(i).isConnectionFromFirstToSecond(cellFromIndex, cellToIndex)) {
            //then there is a connection and we return true
            return true;
        }
    }
    // else return false as no connection exists yet
    return false;
}

bool Genotype::hasConnection(int cell1Index, int cell2Index) {
    if(cellArray.isFirstIndexConnectedToSecondIndex(cell1Index, cell2Index)){
        return true;
    }
    // else return false as no connection exists yet
    return false;
}

float Genotype::getSpecificDirectionalConnectionWeight(int cellFromIndex, int cellToIndex) {
    long links = connectionVector.size();
    for (int i = 0; i < links; i++) {
        if (connectionVector.at(i).isConnectionFromFirstToSecond(cellFromIndex, cellToIndex)) {
            return connectionVector.at(i).connectionWeight;
        }
    }
    printf("This should never print, check getSpecificDirectionalConnectionWeight() for mistakes"); 
    return 0;
}
