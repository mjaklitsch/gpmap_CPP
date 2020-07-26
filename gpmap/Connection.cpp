#include "Connection.h"
#include "ConnectionWeight.h"
#include <iostream>

float Connection::x1 = 0;
float Connection::y1 = 0;
float Connection::x2 = 0;
float Connection::y2 = 0;
float Connection::connectionWeight = 0;

Cell* Connection::cell1;
Cell* Connection::cell2;

// int cell1Index;
// int cell2Index;

float Connection::xFrom = 0;
float Connection::yFrom = 0;
float Connection::xTo = 0;
float Connection::yTo = 0;

Cell *Connection::cellFrom; // use this to figure out if a swap happened
Cell *Connection::cellTo;

int Connection::cellFromIndex = 0;
int Connection::cellToIndex = 0;

bool Connection::hasUncheckedNeuronalConnection = false;
bool Connection::connectionIsComplete = false;

Connection::Connection(int tempCell1Index, int tempCell2Index, Cell *tempCell1, Cell *tempCell2) {
  // temporary values which will be corrected later
  cellFromIndex = tempCell1Index; // these will be checked for existence of a connection
  cellToIndex = tempCell2Index; // however the details of that connection won't matter yet
  // so it is fine that the values may be reversed

  cell1 = tempCell1;
  cell2 = tempCell2;

  x1 = cell1->xPos;
  y1 = cell1->yPos;
  x2 = cell2->xPos;
  y2 = cell2->yPos;
}

//void swapConnectionToFrom() {
//  Cell tempCellFrom = cellFrom;
//  cellFrom = cellTo;
//  cellTo = tempCellFrom;
//}

void Connection::updateThisConnectionPosition() {

  if (!connectionIsComplete) {
    x1 = cell1->xPos;
    y1 = cell1->yPos;
    x2 = cell2->xPos;
    y2 = cell2->yPos;
    if ((cell1->doneGrowing == true && cell1->doneMoving == true) && // if both cells...
      (cell2->doneGrowing == true && cell2->doneMoving == true)) { // ...are done moving/growing
      setCellToAndCellFrom();
      connectionWeight = calculateConnectionWeight(cellFrom, cellTo);
      connectionIsComplete = true;
    }
  }
}

void Connection::setCellToAndCellFrom() {
  if (cell1->isSensor()) {
    cellTo = cell2;
    cellFrom = cell1;
    cellFromIndex = cellFrom->index;
    cellToIndex = cellTo->index;
    xTo = cellTo->xPos;
    yTo = cellTo->yPos;
    xFrom = cellFrom->xPos;
    yFrom = cellFrom->yPos;
  } else if (cell1->isMotor()) {
    cellTo = cell1;
    cellFrom = cell2;
    cellFromIndex = cellFrom->index;
    cellToIndex = cellTo->index;
    xTo = cellTo->xPos;
    yTo = cellTo->yPos;
    xFrom = cellFrom->xPos;
    yFrom = cellFrom->yPos;
  } else if (cell1->isNeuron()) {
    if (cell2->isSensor()) {
      cellTo = cell1;
      cellFrom = cell2;
      cellFromIndex = cellFrom->index;
      cellToIndex = cellTo->index;
      xTo = cellTo->xPos;
      yTo = cellTo->yPos;
      xFrom = cellFrom->xPos;
      yFrom = cellFrom->yPos;
    } else if (cell2->isMotor()) {
      cellTo = cell2;
      cellFrom = cell1;
      cellFromIndex = cellFrom->index;
      cellToIndex = cellTo->index;
      xTo = cellTo->xPos;
      yTo = cellTo->yPos;
      xFrom = cellFrom->xPos;
      yFrom = cellFrom->yPos;
    } else if (cell2->isNeuron()) {
      if (cell1->diameter > cell2->diameter) {
        cellTo = cell2;
        cellFrom = cell1;
        cellFromIndex = cellFrom->index;
        cellToIndex = cellTo->index;
        xTo = cellTo->xPos;
        yTo = cellTo->yPos;
        xFrom = cellFrom->xPos;
        yFrom = cellFrom->yPos;
      } else if (cell1->diameter <= cell2->diameter) {
        cellTo = cell1;
        cellFrom = cell2;
        cellFromIndex = cellFrom->index;
        cellToIndex = cellTo->index;
        xTo = cellTo->xPos;
        yTo = cellTo->yPos;
        xFrom = cellFrom->xPos;
        yFrom = cellFrom->yPos;
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
