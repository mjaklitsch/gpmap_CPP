//
//  CellArrayScaffold.cpp
//
//
//  Created by Michael Jaklitsch on 7/28/20.
//

#include "CellArrayScaffold.hpp"

CellArray cellArrayScaffold(){
    CellArray scaffoldCellArray;

    Gene G0 = Gene("N", 0.960873, -1.000000, 4.000000, 32.000000, 5.000000, 0.000000, 27.000000);
    Cell C0 = Cell(G0, 0);
    scaffoldCellArray.add(C0);
    Gene G1 = Gene("P", 3.522930, 4.000000, 6.000000, 28.000000, 8.000000, 0.000000, 39.000000);
    Cell C1 = Cell(G1, 1);
    scaffoldCellArray.add(C1);
    Gene G2 = Gene("P", 1.246024, 3.000000, 5.000000, 33.000000, 5.000000, 0.000000, 30.000000);
    Cell C2 = Cell(G2, 2);
    scaffoldCellArray.add(C2);
    Gene G3 = Gene("P", 5.344616, -3.000000, 3.000000, 36.000000, 10.000000, 0.000000, 25.000000);
    Cell C3 = Cell(G3, 3);
    scaffoldCellArray.add(C3);
    Gene G4 = Gene("R", 4.476335, 2.000000, 5.000000, 37.000000, 7.000000, 0.000000, 22.000000);
    Cell C4 = Cell(G4, 4);
    scaffoldCellArray.add(C4);
    Gene G5 = Gene("R", 6.245012, -1.000000, 3.000000, 39.000000, 5.000000, 0.000000, 38.000000);
    Cell C5 = Cell(G5, 5);
    scaffoldCellArray.add(C5);
    Gene G6 = Gene("LM", 2.140894, -5.000000, 3.000000, 27.000000, 4.000000, 0.000000, 33.000000);
    Cell C6 = Cell(G6, 6);
    scaffoldCellArray.add(C6);
    Gene G7 = Gene("RM", 0.013736, -2.000000, 3.000000, 22.000000, 11.000000, 0.000000, 26.000000);
    Cell C7 = Cell(G7, 7);
    scaffoldCellArray.add(C7);

    return scaffoldCellArray;
}
