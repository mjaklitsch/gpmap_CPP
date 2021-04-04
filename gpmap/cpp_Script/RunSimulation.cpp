#include "RunSimulation.hpp"
#include "Genotype.hpp"
#include "SensorArray.hpp"
#include "Phenotype.hpp"
#include "GlobalVariables.hpp"
#include <iostream>
#include <cassert>
#include <mutex>          // std::mutex

#define assertm(exp, msg) assert(((void)msg, exp))
using namespace timer;

std::mutex mtx;
//Sim::Sim(){};

void runSimulation(int minN, int maxN, int minP, int maxP,
                   int minIR, int maxIR, int minLM, int maxLM, int minRM,
                   int maxRM, bool testMode){
    
    assertm((minN <= maxN)
            && (minP <= maxP)
            && (minIR <= maxIR)
            && (minLM <= maxLM)
            && (minRM <= maxRM),
            "Min values must be less than or \
            equal to their Max counterparts");
    
    assertm((minN >= 0)
            && (minP >= 0)
            && (minIR >= 0)
            && (minLM >= 0)
            && (minRM >= 0),
            "All input values must be greater than zero");
    
    Genotype testGenotype = Genotype(minN, maxN, minP, maxP, minIR, maxIR,
                                        minLM, maxLM, minRM, maxRM, testMode);
    SensorArray testSensorArray = SensorArray();
    
    
    testSensorArray.initializeSensors();

    Genotype *genotypePointer = &testGenotype;
    
    for(timer::currentTick = 0; timer::currentTick < timer::ticks; timer::currentTick++){
        
        for(timer::currentFrame = 0; timer::currentFrame < timer::actionSpread; timer::currentFrame++){
            testGenotype.moveCells();
            testGenotype.recordIntersections();
//            testSensorArray.recordSensorAttachments(genotypePointer);
        }
    }
    
    testGenotype.finalizeAllConnections();
    // record sensor attachments can be put inside the loop to keep the
    // order of attachment but if only the indexes are needed, keeping
    // it outside the loop is faster
    testSensorArray.recordSensorAttachments(genotypePointer);
    
    // Simulation complete
    
    testGenotype.cellArray.printCellArray();
    if(global::printStuff){
        printf("\nBuild me a robot!\n");
    }
    CellArray testCellArray = testGenotype.cellArray;
    Phenotype finalPhenotype = Phenotype(&testSensorArray, &testGenotype, &testCellArray);
    finalPhenotype.printRobot();
}
