#include "Phenotype.hpp"
#include "GlobalVariables.hpp"
#include <iostream>
#include <iomanip>

void printIntegerMatrix(std::vector<std::vector<int> > integerMatrix) {
    if(global::printStuff){
        for (int i = 0; i < integerMatrix.size(); i++) {
            printf("%d: ", i);
            long innerSize = integerMatrix.at(i).size();
            for (int j = 0; j < innerSize; j++) {
                printf("[%d] ", integerMatrix.at(i).at(j));
            }
            printf("\n");
        }
        printf("\n");
    }
}

void printFloatMatrix(std::vector<std::vector<float> > floatMatrix) {
    if(global::printStuff){
        std::setw(2);
        for (int i = 0; i < floatMatrix.size(); i++) {
            printf("_%d_", i);
        }
        printf("\n");
        for (int i = 0; i < floatMatrix.size(); i++) {
            printf("%d: ", i);
            long innerSize = floatMatrix.at(i).size();
            for (int j = 0; j < innerSize; j++) {
                printf("[%f] ", floatMatrix.at(i).at(j));
            }
            printf("\n");
        }
        printf("\n");
    }
}

void printboolMatrix(std::vector<std::vector<bool> > boolMatrix) {
    if(global::printStuff){
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
            long innerSize = boolMatrix.at(i).size();
            for (int j = 0; j < innerSize; j++) {
                printf("%s", boolMatrix.at(i).at(j) ? " TRUE " : " false");
            }
            printf("\n");
        }
        printf("\n");
    }
}

Phenotype::Phenotype(SensorArray *tempSensorArray, Genotype *tempPhenotype, CellArray *tempCellArray) {
    sensorArray = tempSensorArray;
    phenotype = tempPhenotype;
    cellArray = tempCellArray;
    
    numberOfCells = 0;
    
    numberOfNeurons = 0;
    numberOfPhotoSensors = 0;
    numberOfIRSensors = 0;
    numberOfRightMotors = 0;
    numberOfLeftMotors = 0;
    
    for (int i = 0; i < global::numberOfCellsCreated; i++) {
        //        std::cout<< cellArray->getCell(i).getCellType();
        //        printf(" :  %d.  ", i);
        if(cellArray->getCell(i).getCellType() == "N") {
            numberOfNeurons++;
            numberOfCells++;
        } else if(cellArray->getCell(i).getCellType() == "R"){
            numberOfIRSensors++;
            numberOfCells++;
        } else if(cellArray->getCell(i).getCellType() == "P"){
            numberOfPhotoSensors++;
            numberOfCells++;
        } else if(cellArray->getCell(i).getCellType() == "LM"){
            numberOfLeftMotors++;
            numberOfCells++;
        } else if(cellArray->getCell(i).getCellType() == "RM"){
            numberOfRightMotors++;
            numberOfCells++;
        }
    }
    
    for (int i = 0; i < numberOfSensors; i++) {
        std::vector<int> connectionArray = sensorArray->sensorDotArray.at(i).connections;
        attachmentsBySensorIndex.push_back(connectionArray);
    }
    
    cellConnections.resize(numberOfCells);
    cellConnectionWeights.resize(numberOfCells);
    for (int x = 0; x < numberOfCells; x++) {
        for (int y = 0; y < numberOfCells; y++) {
            if (phenotype->hasSpecificDirectionalConnection(x, y)) {
                cellConnections.at(x).emplace_back(true);
                cellConnectionWeights.at(x).emplace_back(phenotype->getSpecificDirectionalConnectionWeight(x, y));
            } else {
                cellConnections.at(x).emplace_back(false);
                cellConnectionWeights.at(x).emplace_back(0.0);
            }
        }
    }
}


void Phenotype::printRobot() {
    if(global::printStuff){
        printf("Number of Cells: %d\n", numberOfCells);
        printf("Number of Neurons: %d\n", numberOfNeurons);
        printf("Number of IR Sensors: %d\n", numberOfIRSensors);
        printf("Number of Photo Sensors: %d\n", numberOfPhotoSensors);
        printf("Number of Right Motors: %d\n", numberOfRightMotors);
        printf("Number of Left Motors: %d\n", numberOfLeftMotors);
        printf("\nPhysical Sensor Attachments by Index: \n");
        printIntegerMatrix(attachmentsBySensorIndex);
        printf("Connections by Index, Y to X:\n");
        printboolMatrix(cellConnections);
        printf("Connection Weights by Index, Y to X:\n");
        printFloatMatrix(cellConnectionWeights);
    }
}
