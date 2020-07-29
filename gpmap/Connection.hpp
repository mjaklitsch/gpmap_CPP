#include "Cell.hpp"
#include "CellArray.hpp"

#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

class Connection {
public:
    float connectionWeight;
    
    CellArray* cellArray;
    
    int cell1Index;
    int cell2Index;
    
    float xFrom;
    float yFrom;
    float xTo;
    float yTo;
    
    int cellFromIndex;
    int cellToIndex;
    
    bool hasUncheckedNeuronalConnection;
    bool connectionIsComplete;
    
    Connection(int tempCellFromIndex, int tempCellToIndex, CellArray* tempCellArray);
    
    void updateThisConnectionPosition();
    void setCellToAndCellFrom();
    
    bool isConnectionFromFirstToSecond(int first, int second);
    bool doesConnectionExist(int first, int second);
};

#endif
