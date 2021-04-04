#include "Gene.hpp"
#include <string>
#include <vector>

#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

class Cell {
private:
    int index;
    // ArrayList<Connection> cellConnections; // moved to Phenotype
    std::vector<int> connectedTo;
    
    Gene gene;
    float xPos;
    float yPos;
    float diameter;
    float radius;
    
    float xSpeed;
    float ySpeed;
    float growthRate;
    
    bool doneMoving;
    bool doneGrowing;
    bool connectedToSensor;
    
public:
    Cell();
    Cell(Gene tempGene, int tempIndex);
    Cell(std::string cellType, int tempIndex);
    
    bool isMotor();
    bool isSensor();
    bool isNeuron();
    
    void setCellSpeedAndGrowth();
    void moveAndMorphCell();
    void printGenes();
    
    int getIndex();
    std::string getCellType();
    Gene getGene();
    float getTheta();
    float getXPos();
    float getYPos();
    float getDiameter();
    float getRadius();
    float getXSpeed();
    float getYSpeed();
    float getGrowthRate();
    bool getDoneMoving();
    bool getDoneGrowing();
    bool getConnectedToSensor();
    bool isConnectedToIndex(int index);
    
    void setIndex(int i);
    void setGene(Gene g);
    void setXPos(float x);
    void setYPos(float y);
    void setDiameter(float d);
    void setRadius(float r);
    void setXSpeed(float dx);
    void setYSpeed(float dy);
    void setGrowthRate(float ds);
    void setDoneMoving(bool moving);
    void setDoneGrowing(bool growing);
    void setConnectedToSensor(bool connected);
    void addConnection(int cellIndex);
    void printCell(int index);
};

#endif
