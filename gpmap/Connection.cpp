#include "Connection.hpp"
#include "ConnectionWeight.hpp"
#include <iostream>

Connection::Connection(int tempCell1Index, int tempCell2Index, CellArray* tempCellArray) {
    cell1Index = tempCell1Index;
    cell2Index = tempCell2Index;
    
    cellArray = tempCellArray;
    
    hasUncheckedNeuronalConnection = false;
    connectionIsComplete = false;
}


void Connection::updateThisConnectionPosition() {
    
    if (!connectionIsComplete) {
        if ((cellArray->getCell(cell1Index).getDoneGrowing() == true && cellArray->getCell(cell1Index).getDoneMoving() == true) && // if both cells...
            (cellArray->getCell(cell2Index).getDoneGrowing() == true && cellArray->getCell(cell2Index).getDoneMoving() == true)) { // ...are done moving/growing
            setCellToAndCellFrom();
            connectionWeight = calculateConnectionWeight(cellFromIndex, cellToIndex, cellArray);
            connectionIsComplete = true;
        }
    }
}

void Connection::setCellToAndCellFrom() {
    if (cellArray->isSensor(cell1Index)) {
        cellFromIndex = cell1Index;
        cellToIndex = cell2Index;
    } else if (cellArray->isMotor(cell1Index)) {
        cellFromIndex = cell2Index;
        cellToIndex = cell1Index;
    } else if (cellArray->isNeuron(cell1Index)) {
        if (cellArray->isSensor(cell2Index)) {
            cellFromIndex = cell2Index;
            cellToIndex = cell1Index;
        } else if (cellArray->isMotor(cell2Index)) {
            cellFromIndex = cell1Index;
            cellToIndex = cell2Index;
        } else if (cellArray->isNeuron(cell2Index)) {
            if (cellArray->getDiameter(cell1Index) > cellArray->getDiameter(cell2Index)) {
                cellFromIndex = cell1Index;
                cellToIndex = cell2Index;
            } else if (cellArray->getDiameter(cell1Index) <= cellArray->getDiameter(cell2Index)) {
                cellFromIndex = cell2Index;
                cellToIndex = cell1Index;
            }
        }
    }
}

bool Connection::isConnectionFromFirstToSecond(int first, int second) {
    if (cellFromIndex == first && cellToIndex == second) {
        return true;
    } else {
        return false;
    }
}

bool Connection::doesConnectionExist(int first, int second){
    if ((cell1Index == first && cell2Index == second) || (cell1Index == second && cell2Index == first)) {
        return true;
    } else {
        return false;
    }
}
