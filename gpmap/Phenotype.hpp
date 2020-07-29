#include "Cell.hpp"
#include "Connection.hpp"
#include "CellArray.hpp"
#include <vector>

#ifndef PHENOTYPE_H_INCLUDED
#define PHENOTYPE_H_INCLUDED

class Phenotype {
public:
    static int numberOfCells;
    static std::vector<Connection> connectionVector;
    static CellArray cellArray;
    
    // float partCost; // later implementation
    
    Phenotype(int minNeurons, int maxNeurons, int minPhotoSensors,
              int maxPhotoSensors, int minIRSensors, int maxIRSensors,
              int minLeftMotors, int maxLeftMotors, int minRightMotors,
              int maxRightMotors, bool testMode);
    
    void addConnection(int i, int j);
    void moveCells();
    void recordIntersections();
    void updateAllConnectionPositions();
    bool hasSpecificDirectionalConnection(int cellFromIndex, int cellToIndex);
    bool hasConnection(int cell1Index, int cell2Index);
    float getSpecificDirectionalConnectionWeight(int cellFromIndex, int cellToIndex);
    
};

#endif
