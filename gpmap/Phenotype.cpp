#include "Phenotype.hpp"
#include "random.hpp"
#include "GlobalVariables.hpp"
#include "PolygonCalculations.hpp"
#include "CellArrayScaffold.hpp"
#include <iostream>
#include <iomanip>


int Phenotype::numberOfCells;
std::vector<Connection> Phenotype::connectionVector;
CellArray Phenotype::cellArray;

// float partCost; // later implementation

Phenotype::Phenotype(int minNeurons, int maxNeurons, int minPhotoSensors,
                     int maxPhotoSensors, int minIRSensors, int maxIRSensors,
                     int minLeftMotors, int maxLeftMotors, int minRightMotors,
                     int maxRightMotors, bool testMode) {
    if(testMode){
        cellArray = cellArrayScaffold();
        numberOfCells = cellArray.getSize();
        global::numberOfCellsCreated = numberOfCells;
    } else{
        
        int neurons = intRandom(minNeurons, maxNeurons);
        printf("neurons %d ",neurons);
        int photoSensors = intRandom(minPhotoSensors, maxPhotoSensors);
        printf("photoSensors %d ",photoSensors);
        int irSensors = intRandom(minIRSensors, maxIRSensors);
        printf("irSensors %d ",irSensors);
        int leftMotors = intRandom(minLeftMotors, maxLeftMotors);
        printf("leftMotors %d ",leftMotors);
        int rightMotors = intRandom(minRightMotors, maxRightMotors);
        printf("rightMotors %d\n",rightMotors);
        
        numberOfCells = neurons + photoSensors + irSensors + leftMotors + rightMotors;
        global::numberOfCellsCreated = numberOfCells; //global record
        int arrayIndex = 0;
        
//        printf("size of cellarray %d\n", cellArray.getSize());
//        printf("number of cells %d\n", numberOfCellsCreated);
        
        //    cellArray.resize(numberOfCellsCreated);
        
        for (int i = 0; i < neurons; i++) {
            Cell nextCell = Cell("N", (arrayIndex + i));
            cellArray.add(nextCell);
        }
        
        arrayIndex += neurons;
        
        for (int i = 0; i < photoSensors; i++) {
            Cell nextCell = Cell("P", (arrayIndex + i));
            cellArray.add(nextCell);
        }
        
        arrayIndex += photoSensors;
        
        for (int i = 0; i < irSensors; i++) {
            Cell nextCell = Cell("R", (arrayIndex + i));
            cellArray.add(nextCell);
        }
        
        arrayIndex += irSensors;
        
        for (int i = 0; i < leftMotors; i++) {
            Cell nextCell = Cell("LM", (arrayIndex + i));
            cellArray.add(nextCell);
        }
        arrayIndex += leftMotors;
        
        for (int i = 0; i < rightMotors; i++) {
            Cell nextCell = Cell("RM", (arrayIndex + i));
            cellArray.add(nextCell);
        }
//        printf("cell index at cellArray index 0: ");
        std::cout << cellArray.getCell(0).getIndex()  <<'\n';
//        printf("size of cellarray %d\n", cellArray.getSize());
        
        arrayIndex += rightMotors;
    }
}

void Phenotype::addConnection(int i, int j) {
    cellArray.addIndexesOfConnectionToCells(i, j);
    Connection newConnection = Connection(i, j, &cellArray);
    connectionVector.push_back(newConnection);
}

void Phenotype::moveCells() {
    for (int i = 0; i < numberOfCells; i++) {
        cellArray.moveAndMorphCell(i);
        cellArray.setCellSpeedAndGrowth(i);
    }
}

void Phenotype::recordIntersections() {
    for (int i = 0; i < numberOfCells; i++) {
        for (int j = i+1; j < numberOfCells; j++) {
            if(((!cellArray.getCell(i).getDoneMoving() || !cellArray.getCell(i).getDoneGrowing())|| // If both have not stopped moving and growing
                 (!cellArray.getCell(j).getDoneMoving() || !cellArray.getCell(j).getDoneGrowing())) &&
                ((cellArray.getCell(i).getDiameter() > 0) && // and if both have spawned
                (cellArray.getCell(j).getDiameter() > 0)) &&
               !((cellArray.isMotor(i) && cellArray.isMotor(j)) || // and if a connection between types is possible
                 (cellArray.isSensor(i) && cellArray.isSensor(j)))){ // this is a major optimization over prior versions
                
                float ixPos = cellArray.getCell(i).getXPos();
                float iyPos = cellArray.getCell(i).getYPos();
                float jxPos = cellArray.getCell(j).getXPos();
                float jyPos = cellArray.getCell(j).getYPos();
                
                if ((cellArray.getCell(i).getRadius() + cellArray.getCell(j).getRadius()) > distanceBetween(ixPos, iyPos, jxPos, jyPos)) { // if the two have spawned and are overlapping
                    if (!hasConnection(i, j)) { // if no connection has been recorded yet
                        addConnection(i, j);
                    }
                }
            }
        }
    }
}

void Phenotype::updateAllConnectionPositions() {
    long links = connectionVector.size();
    for (int i = 0; i < links; i++) {
        connectionVector[i].updateThisConnectionPosition();
    }
}


bool Phenotype::hasSpecificDirectionalConnection(int cellFromIndex, int cellToIndex) {
    long links = connectionVector.size();
    for (int i = 0; i < links; i++) {
        if (connectionVector[i].isConnectionFromFirstToSecond(cellFromIndex, cellToIndex)) {
            //then there is a connection and we return true
            return true;
        }
    }
    // else return false as no connection exists yet
    return false;
}

bool Phenotype::hasConnection(int cell1Index, int cell2Index) {
    if(cellArray.isFirstIndexConnectedToSecondIndex(cell1Index, cell2Index)){
        return true;
    }
    // else return false as no connection exists yet
//    printf("Not yet a connection from %d to %d\n", cell1Index, cell2Index);
    return false;
}

float Phenotype::getSpecificDirectionalConnectionWeight(int cellFromIndex, int cellToIndex) {
    long links = connectionVector.size();
    for (int i = 0; i < links; i++) {
        if (connectionVector[i].isConnectionFromFirstToSecond(cellFromIndex, cellToIndex)) {
            return connectionVector[i].connectionWeight;
        }
    }
    printf("This should never print, check getSpecificDirectionalConnectionWeight() for mistakes"); 
    return 0;
}
