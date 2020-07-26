#include "Genotype.h"
#include <string>

#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

class Cell {
public:
    static int index;
    // ArrayList<Connection> cellConnections; // moved to Phenotype
    
    static Genotype genotype;
    static float xPos;
    static float yPos;
    static float diameter;
    static float radius;
    
    static float xSpeed;
    static float ySpeed;
    static float growthRate;
    
    static bool doneMoving;
    static bool doneGrowing;
    Cell();
//    Cell(const Cell &C2);
    Cell(std::string cellType, int tempIndex);
//    ~Cell();
    
    bool isMotor();
    bool isSensor();
    bool isNeuron();
    
    void setCellSpeedAndGrowth();
    void moveAndMorphCell();
    void printGenes();
};

#endif
