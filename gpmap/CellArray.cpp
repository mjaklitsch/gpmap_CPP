//
//  CellArray.cpp
//  
//
//  Created by Michael Jaklitsch on 7/27/20.
//

#include "CellArray.hpp"
#include "GlobalVariables.hpp"
#include <vector>

vector<Cell> CellArray::subArray;

int CellArray::getSize(){
    return (int)subArray.size();
}

void CellArray::add(Cell& cell){
    subArray.push_back(cell);
}

Cell CellArray::getCell(int index){
    return subArray.at(index);
}

bool CellArray::isMotor(int index) {
    return subArray.at(index).isMotor();
}

bool CellArray::isSensor(int index) {
    return subArray.at(index).isSensor();
}

bool CellArray::isNeuron(int index) {
    return subArray.at(index).isNeuron();
}

bool CellArray::getConnectedToSensor(int index){
    return subArray.at(index).getConnectedToSensor();
}

bool CellArray::isFirstIndexConnectedToSecondIndex(int index1, int index2){
    return subArray.at(index1).isConnectedToIndex(index2);
}

void CellArray::setCellSpeedAndGrowth(int index) {
    subArray.at(index).setCellSpeedAndGrowth();
}

void CellArray::setConnectedToSensor(int index, bool connected){
    subArray.at(index).setConnectedToSensor(connected);
}

void CellArray::moveAndMorphCell(int index) {
    subArray.at(index).moveAndMorphCell();
}

void CellArray::printGenes(int index) {
    subArray.at(index).printGenes();
}

void CellArray::addIndexesOfConnectionToCells(int index1, int index2){
    subArray.at(index1).addConnection(index2);
    subArray.at(index2).addConnection(index1);
}

void CellArray::printCellArray(){
    if(global::printStuff){
        printf("CellArray scaffoldCellArray;\n\n");
        for (int i =0; i<subArray.size(); i++) {
            subArray.at(i).printCell(i);
            printf("scaffoldCellArray.add(C%d);\n", i);
        }
        printf("\nreturn scaffoldCellArray;\n");
    }
}

float CellArray::getTheta(int index){
    return subArray.at(index).getTheta();
}

float CellArray::getDiameter(int index){
    return subArray.at(index).getDiameter();
}

float CellArray::getRadius(int index){
    return subArray.at(index).getRadius();
}

float CellArray::getXPos(int index){
    return subArray.at(index).getXPos();
}

float CellArray::getYPos(int index){
    return subArray.at(index).getYPos();
}


