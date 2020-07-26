#include "RunSimulation.h"
#include <iostream>



int main(void){

    // Phenotype Generation Variables
    int minNeurons = 1;
    int minPhotosensors = 2;
    int minIRSensors = 2;
    int minLeftMotors = 1;
    int minRightMotors = 1;
    
    int maxNeurons = 4;
    int maxPhotosensors = 4;
    int maxIRSensors = 4;
    int maxLeftMotors = 1;
    int maxRightMotors = 1;
    
    runSimulation(minNeurons, maxNeurons, minPhotosensors,
                  maxPhotosensors, minIRSensors, maxIRSensors,
                  minLeftMotors, maxLeftMotors, minRightMotors,
                  maxRightMotors);
    
    return 0;
}
// g++ TimerVariables.o RunSimulation.o Cell.o ConnectionWeight.o SensorDot.o SensorArray.o Robot.o random.o PolygonCalculations.o Phenotype.o Connection.o Genotype.o GenerateGene.o main.o -o gpmap
