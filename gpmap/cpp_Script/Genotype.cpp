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
            cellArray.emplace("N", (arrayIndex + i));
        }
        arrayIndex += neurons;
        
        for (int i = 0; i < photoSensors; i++) {
            cellArray.emplace("P", (arrayIndex + i));
        }
        arrayIndex += photoSensors;
        
        for (int i = 0; i < irSensors; i++) {
            cellArray.emplace("R", (arrayIndex + i));
        }
        arrayIndex += irSensors;
        
        for (int i = 0; i < leftMotors; i++) {
            cellArray.emplace("LM", (arrayIndex + i));
        }
        arrayIndex += leftMotors;
        
        for (int i = 0; i < rightMotors; i++) {
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
            
            // snake case was much more readable here
            Cell cell_i = cellArray.getCell(i);
            Cell cell_j = cellArray.getCell(j);
            
            // if cell_i has not stopped moving and growing
            // or cell_j has not stopped moving and growing
            bool isMovingOrGrowing = (!cell_i.getDoneMoving() || !cell_i.getDoneGrowing()
                                      || !cell_j.getDoneMoving() || !cell_j.getDoneGrowing());
            
            // if both have started growing
            bool bothHaveSpawned = (cell_i.getDiameter() > 0) && (cell_j.getDiameter() > 0);
            
            // if a connection between types is possible
            bool isConnectionPossible = !((cell_i.isMotor() && cell_j.isMotor()) ||
                                          (cell_i.isSensor() && cell_j.isSensor()));
            
            if(isMovingOrGrowing && bothHaveSpawned && isConnectionPossible){
                
                float ixPos = cell_i.getXPos();
                float iyPos = cell_i.getYPos();
                float jxPos = cell_j.getXPos();
                float jyPos = cell_j.getYPos();
                
                if ((cell_i.getRadius() + cell_j.getRadius()) > distanceBetween(ixPos, iyPos, jxPos, jyPos)) {
                    // if the two are overlapping, connect them
                    if (!hasConnection(i, j)) {addConnection(i, j);}
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
    // this function just really needed a Genotype class shorthand
    return cellArray.isFirstIndexConnectedToSecondIndex(cell1Index, cell2Index);
}

float Genotype::getSpecificDirectionalConnectionWeight(int cellFromIndex, int cellToIndex) {
    long links = connectionVector.size();
    for (int i = 0; i < links; i++) {
        Connection thisConnection = connectionVector.at(i);
        if (thisConnection.isConnectionFromFirstToSecond(cellFromIndex, cellToIndex)) {
            return thisConnection.connectionWeight;
        }
    }
    printf("This should never print, check getSpecificDirectionalConnectionWeight() for mistakes"); 
    return 0;
}
