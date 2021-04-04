#include "Cell.hpp"
#include "GenerateGene.hpp"
#include "GlobalVariables.hpp"
#include <iostream>
#include <string>
#include <cmath>

using namespace timer;

Cell::Cell(){
}

Cell::Cell(Gene tempGene, int tempIndex){
    gene = tempGene;
    index = tempIndex;
    xPos = 0;
    yPos = 0;
    diameter = 0;
    radius = 0;
    
    xSpeed = 0;
    ySpeed = 0;
    growthRate = 0;
    
    doneMoving = false;
    doneGrowing = false;
    connectedToSensor = false;
}

Cell::Cell(std::string cellType, int tempIndex) {
    gene = returnRandomNewGenotype(cellType);
    index = tempIndex;
    xPos = 0;
    yPos = 0;
    diameter = 0;
    radius = 0;
    
    xSpeed = 0;
    ySpeed = 0;
    growthRate = 0;
    
    doneMoving = false;
    doneGrowing = false;
    connectedToSensor = false;
}

bool Cell::isMotor() {
    const std::string motors[] = {"LM", "RM"};
    
    return std::find(std::begin(motors), std::end(motors),
                     getCellType()) != std::end(motors);
}

bool Cell::isSensor() {
    const std::string sensors[] = {"R", "P"};
    
    return std::find(std::begin(sensors), std::end(sensors),
                     getCellType()) != std::end(sensors);
}

bool Cell::isNeuron() {
    return (getCellType() == "N");
}

void Cell::setCellSpeedAndGrowth() {
    if(growthRate == 0 && timer::currentTick > gene.getGrowthDelay()) {
        growthRate = (gene.getGrowthRate() / timer::actionSpread);
    }
    if (timer::currentTick > gene.getMovementDelay()) {
        float speed = (gene.getSpeed() / timer::actionSpread);
        // set x and y components of speed
        xSpeed = speed * cos(gene.getTheta());
        ySpeed = speed * sin(gene.getTheta());
    }
}

void Cell::moveAndMorphCell() {
    if (!doneMoving && (timer::currentTick - gene.getMovementDelay() < gene.getMovementDuration())) {
        xPos += xSpeed;
        yPos -= ySpeed;
    } else {
        doneMoving = true;
    }
    
    if (!doneGrowing && (timer::currentTick - gene.getGrowthDelay() < gene.getGrowthDuration())) {
        diameter += growthRate;
        radius = diameter/2;
    } else {
        doneGrowing = true;
    }
}

// Cell Sub-Gene getters/printers
void Cell::printGenes() {printGenotype(gene);}
std::string Cell::getCellType() {return gene.getCellType();}
Gene Cell::getGene() {return gene;}
float Cell::getTheta() {return gene.getTheta();}

// Cell getters
int Cell::getIndex() {return index;}
float Cell::getXPos() {return xPos;}
float Cell::getYPos() {return yPos;}
float Cell::getDiameter() {return diameter;}
float Cell::getRadius() {return radius;}
float Cell::getXSpeed() {return xSpeed;}
float Cell::getYSpeed() {return ySpeed;}
float Cell::getGrowthRate( ){return growthRate;}
bool Cell::getDoneMoving() {return doneMoving;}
bool Cell::getDoneGrowing() {return doneGrowing;}
bool Cell::getConnectedToSensor() {return connectedToSensor;}


bool Cell::isConnectedToIndex(int index){
    // connectedTo is a private Cell::vector<int>
    // if index is found in vector, return true, else false
    return (std::find(connectedTo.begin(), connectedTo.end(), index) != connectedTo.end());
}

void Cell::setIndex(int i) {index = i;}
void Cell::setGene(Gene g) {gene = g;}
void Cell::setXPos(float x) {xPos = x;}
void Cell::setYPos(float y) {yPos = y;}
void Cell::setDiameter(float d) {diameter = d;}
void Cell::setRadius(float r) {radius = r;}
void Cell::setXSpeed(float dx) {xSpeed = dx;}
void Cell::setYSpeed(float dy) {ySpeed = dy;}
void Cell::setGrowthRate(float ds) {growthRate = ds;}
void Cell::setDoneMoving(bool dmoving) {doneMoving = dmoving;}
void Cell::setDoneGrowing(bool dgrowing) {doneGrowing = dgrowing;}
void Cell::setConnectedToSensor(bool connected) {connectedToSensor = connected;}
void Cell::addConnection(int cellIndex) {connectedTo.push_back(cellIndex);}

void Cell::printCell(int index){
    printf("Gene G%d = Gene(\"%s\", ", index,gene.getCellType().c_str());
    printf("%f, ", gene.getTheta());
    printf("%f, ", gene.getGrowthDelay());
    printf("%f, ", gene.getGrowthRate());
    printf("%f, ", gene.getGrowthDuration());
    printf("%f, ", gene.getSpeed());
    printf("%f, ", gene.getMovementDelay());
    printf("%f);\n", gene.getMovementDuration());
    printf("Cell C%d = Cell(G%d, %d);\n",index, index, index);
}
