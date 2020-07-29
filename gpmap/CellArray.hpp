//
//  CellArray.hpp
//  
//
//  Created by Michael Jaklitsch on 7/27/20.
//

#ifndef CellArray_hpp
#define CellArray_hpp

#include "Cell.hpp"
#include <stdio.h>


using namespace std;
class CellArray {
    
    static vector<Cell> subArray;
public:
    int getSize();
    void add(Cell& cell);
    Cell getCell(int index);
    bool isMotor(int index);
    bool isSensor(int index);
    bool isNeuron(int index);
    bool getConnectedToSensor(int index);
    bool isFirstIndexConnectedToSecondIndex(int index1, int index2);
    
    void setCellSpeedAndGrowth(int index);
    void setConnectedToSensor(int index, bool connected);
    void moveAndMorphCell(int index);
    void printGenes(int index);
    void addIndexesOfConnectionToCells(int index1, int index2);
    void printCellArray();
    
    float getTheta(int index);
    float getDiameter(int index);
    float getRadius(int index);
    float getXPos(int index);
    float getYPos(int index);
};
#endif /* CellArray_hpp */
