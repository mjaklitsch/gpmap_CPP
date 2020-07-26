#include "Cell.h"

#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

class Connection {
public:
  static float x1;
  static float y1;
  static float x2;
  static float y2;
  static float connectionWeight;

  static Cell* cell1;
  static Cell* cell2;

  // int cell1Index;
  // int cell2Index;

  static float xFrom;
  static float yFrom;
  static float xTo;
  static float yTo;

  static Cell* cellFrom; // use this to figure out if a swap happened
  static Cell* cellTo;

  static int cellFromIndex;
  static int cellToIndex;

  static bool hasUncheckedNeuronalConnection;
  static bool connectionIsComplete;

  Connection(int tempCellFromIndex, int tempCellToIndex, Cell* tempCell1, Cell* tempCell2);

  void updateThisConnectionPosition();
  void setCellToAndCellFrom();

  bool isConnectionFromFirstToSecond(int first, int second);
};

#endif
