#include "Cell.hpp"
#include "CellArray.hpp"

#ifndef CONNECTIONWEIGHT_H_INCLUDED
#define CONNECTIONWEIGHT_H_INCLUDED

float calculateConnectionWeight(int cellFromIndex, int cellToIndex, CellArray* cellArray);
float getConnectionWeight(int cellFromIndex, int cellToIndex, CellArray* cellArray);

int getConnectionDirection(int cellFromIndex, int cellToIndex, CellArray* cellArray);

bool inRange(float x, float range[]);

#endif
