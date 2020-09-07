#include "ConnectionWeight.hpp"
#include <cmath>
#include <iostream>

bool inRange(float x, float range[]) {
    if (x >= range[0] && x < range[1]) {
        return true;
    } else {
        return false;
    }
}

int getConnectionDirection(int cellFromIndex, int cellToIndex, CellArray* cellArray) {
    
    float fromTheta = cellArray->getTheta(cellFromIndex);
    float toTheta = cellArray->getTheta(cellToIndex);
    
    // index: 0 = low, 1 = high
    // 4 range arrays, 2 for each direction, one extends to the maximum range(2PI or 0), the other restarts from the other side and accounts for the remainder
    // for example with angle of 270:
    // range 1: 270 - 360, range 2: 0 - 90, accounts for a full 180 degrees counterclockwise
    // range 3: 90 - 270, range 4: also 90 - 270 as no overlap with the boundary occurs, accounts for 180 degrees clockwise
    
    // A very angular unit circle diagram:
    //
    //        90
    //      / | \
    // 180 ------- 0/360
    //      \ | /
    //       270
    
    float rangeCounterClockwise[2];
    float rangeCounterClockwise2[2];
    float rangeClockwise[2];
    float rangeClockwise2[2];
    
    if (fromTheta <= M_PI) {
        rangeCounterClockwise[0] = fromTheta;
        rangeCounterClockwise[1] = fromTheta + M_PI;
        rangeCounterClockwise2[0] = fromTheta;
        rangeCounterClockwise2[1] = fromTheta + M_PI;
        
        rangeClockwise[0] = 0;
        rangeClockwise[1] = fromTheta;
        rangeClockwise2[0] = fromTheta + M_PI;
        rangeClockwise2[1] = 2*M_PI;
    } else {
        rangeCounterClockwise[0] = fromTheta;
        rangeCounterClockwise[1] = 2*M_PI;
        rangeCounterClockwise2[0] = 0;
        rangeCounterClockwise2[1] = fromTheta - M_PI;
        
        rangeClockwise[0] = fromTheta - M_PI;
        rangeClockwise[1] = fromTheta;
        rangeClockwise2[0] = fromTheta - M_PI;
        rangeClockwise2[1] = fromTheta;
    }
    
    if (inRange(toTheta, rangeCounterClockwise) || inRange(toTheta, rangeCounterClockwise2)) {
        return -1;
    } else {
        return 1;
    }
    //  } else if (inRange(toTheta, rangeClockwise) || inRange(toTheta, rangeClockwise2)) {
    //    return 1;
    //  } else {
    //    return 0; // should never return
    //  }
}

float getConnectionWeight(int cellFromIndex, int cellToIndex, CellArray* cellArray) {
    float weight;
    
    float cellToDiameter = cellArray->getDiameter(cellToIndex);
    float cellFromDiameter = cellArray->getDiameter(cellFromIndex);
    
    if (cellToDiameter < cellFromDiameter) {
        weight = cellToDiameter / cellFromDiameter;
    } else {
        weight = cellFromDiameter / cellToDiameter;
    }
    
    return weight;
}

float calculateConnectionWeight(int cellFromIndex, int cellToIndex, CellArray* cellArray) {
    
    float weight = getConnectionWeight(cellFromIndex, cellToIndex, cellArray);
    int direction = getConnectionDirection(cellFromIndex, cellToIndex, cellArray);
    
    return direction * weight;
}
