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
    
    int cellFromIndex;
    int cellToIndex;
    
//    bool connectionIsComplete;
    
    Connection(int tempCellFromIndex, int tempCellToIndex, CellArray* tempCellArray);
    
    void finalizeThisConnection();
    void setCellToAndCellFrom();
    
    bool isConnectionFromFirstToSecond(int first, int second);
    bool doesConnectionExist(int first, int second);
};

#endif
