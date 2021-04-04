#include "Connection.hpp"
#include "ConnectionWeight.hpp"
#include <iostream>

Connection::Connection(int tempCell1Index, int tempCell2Index, CellArray* tempCellArray) {
    cell1Index = tempCell1Index;
    cell2Index = tempCell2Index;
    
    cellArray = tempCellArray;
}


void Connection::finalizeThisConnection() {
    setCellToAndCellFrom(); // determine direction now that position and size are finalized
    connectionWeight = calculateConnectionWeight(cellFromIndex, cellToIndex, cellArray); // set weight
}

void Connection::setCellToAndCellFrom() {
    if (cellArray->isSensor(cell1Index)||cellArray->isMotor(cell2Index)) { // sensors are always cellFrom, motors are always cellTo
        cellFromIndex = cell1Index;
        cellToIndex = cell2Index;
    } else if (cellArray->isSensor(cell2Index)||cellArray->isMotor(cell1Index)) { // sensors appear more often so check first
        cellFromIndex = cell2Index;
        cellToIndex = cell1Index;
    } else if (cellArray->getDiameter(cell1Index) > cellArray->getDiameter(cell2Index)) { // neurons depend on size
        cellFromIndex = cell1Index;
        cellToIndex = cell2Index;
//    } else if (cellArray->getDiameter(cell1Index) <= cellArray->getDiameter(cell2Index)) {
    } else { // prior commented line implied
        cellFromIndex = cell2Index;
        cellToIndex = cell1Index;
    }
}

bool Connection::isConnectionFromFirstToSecond(int first, int second) {
    return cellFromIndex == first && cellToIndex == second;
}

bool Connection::doesConnectionExist(int first, int second){
    return (cell1Index == first && cell2Index == second)
            || (cell1Index == second && cell2Index == first);
}
