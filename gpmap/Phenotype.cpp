#include "Phenotype.h"
#include "random.h"
#include "GlobalVariables.h"
#include "PolygonCalculations.h"
#include <iostream>
#include <iomanip>

using namespace locks;



int Phenotype::numberOfCells = 0;
std::vector<Connection> Phenotype::connectionVector;
std::vector<Cell> Phenotype::cellArray;

// float partCost; // later implementation

Phenotype::Phenotype(int minNeurons, int maxNeurons, int minPhotoSensors,
                     int maxPhotoSensors, int minIRSensors, int maxIRSensors,
                     int minLeftMotors, int maxLeftMotors, int minRightMotors,
                     int maxRightMotors) {
    
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
    numberOfCellsCreated = numberOfCells;
    int arrayIndex = 0;
    
    printf("size of cellarray %lu\n", cellArray.size());
    printf("number of cells %d\n", numberOfCellsCreated);
    
    cellArray.resize(numberOfCellsCreated);
    
    
    for (int i = 0; i < neurons; i++) {
        cellArray.at(arrayIndex + i) = *(new Cell("N", (arrayIndex + i)));
//        cellArray.push_back(*(new Cell("N", (arrayIndex + i))));
//        cellArray.push_back(Cell("N", (arrayIndex + i)));
//        cellArray.emplace_back(Cell("N", (arrayIndex + i)));
    }
    arrayIndex += neurons;
    
    for (int i = 0; i < photoSensors; i++) {
        cellArray.at(arrayIndex + i) = *(new Cell("P", (arrayIndex + i)));
//        cellArray.push_back(*(new Cell("P", (arrayIndex + i))));
//        cellArray.push_back(Cell("P", (arrayIndex + i)));
//        cellArray.emplace_back(Cell("P", (arrayIndex + i)));
        
    }
    arrayIndex += photoSensors;
    
    for (int i = 0; i < irSensors; i++) {
        cellArray.at(arrayIndex + i) = *(new Cell("R", (arrayIndex + i)));
//        cellArray.push_back(*(new Cell("R", (arrayIndex + i))));
//        cellArray.push_back(Cell("R", (arrayIndex + i)));
//        cellArray.emplace_back(Cell("R", (arrayIndex + i)));
    }
    arrayIndex += irSensors;
    
    for (int i = 0; i < leftMotors; i++) {
        cellArray.at(arrayIndex + i) = *(new Cell("LM",(arrayIndex + i)));
//        cellArray.push_back(*(new Cell("LM", (arrayIndex + i))));
//        cellArray.push_back(Cell("LM", (arrayIndex + i)));
//        cellArray.emplace_back(Cell("LM", (arrayIndex + i)));
    }
    arrayIndex += leftMotors;
    
    for (int i = 0; i < rightMotors; i++) {
        cellArray.at(arrayIndex + i) = *(new Cell("RM", (arrayIndex + i)));
//        cellArray.push_back(*(new Cell("RM", (arrayIndex + i))));
//        cellArray.push_back(Cell("RM", (arrayIndex + i)));
//        cellArray.emplace_back(Cell("RM", (arrayIndex + i)));
    }
    arrayIndex += rightMotors;
    
    for(int i = 0; i < cellArray.size(); i++){
        printf("Cell %d", i);
        std::cout << cellArray.at(i).genotype.cellType << '\n';
    }
}

void Phenotype::addConnection(int i, int j) {
    Cell *celli = (&cellArray[i]); // if i did this right i deserve a cookie
    Cell *cellj = (&cellArray[j]); // because pointers confuse the hell outta me
    
    // trying to give Connection class softlinks to the Cells rather than copies
    
    Connection newConnection = Connection(i, j, celli, cellj);
    connectionVector.push_back(newConnection);
}

void Phenotype::moveCells() {
    for (int i = 0; i < numberOfCells; i++) {
        cellArray[i].moveAndMorphCell();
        cellArray[i].setCellSpeedAndGrowth();
    }
//    while(i<numberOfCells)
//        //spin
//    ;
//    locks::recordIntersectionsLock = 0;
    printf("b");
}

void Phenotype::recordIntersections() {
    for (int i = 0; i < numberOfCells; i++) {
        for (int j = i+1; j < numberOfCells; j++) {
            
            Cell *celli = &cellArray[i];
            Cell *cellj = &cellArray[j];
            
            float ixPos = celli->xPos;
            float iyPos = celli->yPos;
            float jxPos = cellj->xPos;
            float jyPos = cellj->yPos;
            
            // constant variables added for ease of readability
            
            if (!hasConnection(i, j)) { // if no connection has been recorded yet
                
                if (((celli->radius + cellj->radius) > distanceBetween(ixPos, iyPos, jxPos, jyPos)) &&
                    (celli->diameter > 0) &&
                    (cellj->diameter > 0)) { // if the two have spawned and are overlapping
                    //
                    // there are more concise and efficient ways of writing this but I have chosen this for ease of readability
                    if (celli->isNeuron()) {
                        if (cellj->isNeuron()) { // connect
                            addConnection(i, j);
                        } else if (cellj->isMotor()) { // connect
                            addConnection(i, j);
                        } else if (cellj->isSensor()) { // connect
                            addConnection(i, j);
                        }
                    } else if (celli->isMotor()) {
                        if (cellj->isNeuron()) { // connect
                            addConnection(i, j);
                        } else if (cellj->isMotor()) { // don't connect
                            // do nothing
                        } else if (cellj->isSensor()) { // connect
                            addConnection(i, j);
                        }
                    } else if (celli->isSensor()) {
                        if (cellj->isNeuron()) { // connect
                            addConnection(i, j);
                        } else if (cellj->isMotor()) { // connect
                            addConnection(i, j);
                        } else if (cellj->isSensor()) { // don't connect
                            // do nothing
                        }
                    }
                }
            }
        }
    }
//    while(i<numberOfCells)
//        //spin
//    ;
//    locks::updateAllConnectionPositionsLock = 0;
    printf("a");
    
}

void Phenotype::updateAllConnectionPositions() {
    long links = connectionVector.size();
    for (int i = 0; i < links; i++) {
        connectionVector[i].updateThisConnectionPosition();
        //links = connectionVector.size(); // recalculate as items will be added to list dynamically (should be unnecessary now)
    }
//    while(i<links)
//        //spin
//    ;
//    locks::recordSensorIntersectionsLock = 0;
    printf("n");
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
    long links = connectionVector.size();
    for (int i = 0; i < links; i++) {
        if ((connectionVector[i].isConnectionFromFirstToSecond(cell1Index, cell2Index)) || // if from cell1 to cell2
            (connectionVector[i].isConnectionFromFirstToSecond(cell2Index, cell1Index))) {// or if from cell2 to cell1
            //then there is a connection and we return true
            return true;
        }
        //links = connectionVector.size();// recalculate as items will be added to list dynamically (should be unnecessary now)
    }
    // else return false as no connection exists yet
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
