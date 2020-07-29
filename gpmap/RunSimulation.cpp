#include "RunSimulation.hpp"
#include "Phenotype.hpp"
#include "SensorArray.hpp"
#include "Robot.hpp"
#include "GlobalVariables.hpp"
#include <iostream>
#include <mutex>          // std::mutex

using namespace timer;

std::mutex mtx;

void runSimulation(int minN, int maxN, int minP, int maxP,
                   int minIR, int maxIR, int minLM, int maxLM, int minRM,
                   int maxRM, bool testMode){
    
    //  int timer = 0;
    //  int currentTick = 0;
    //  int timerOverlap = actionSpread;
    
    Phenotype testPhenotype = Phenotype(minN, maxN, minP, maxP, minIR, maxIR,
                                        minLM, maxLM, minRM, maxRM, testMode);
    SensorArray testSensorArray = SensorArray();
    
    
    testSensorArray.initializeSensors();

    Phenotype *phenoPointer = &testPhenotype;
    
    for(timer::currentTick = 0; timer::currentTick < timer::ticks; timer::currentTick++){
        
        
        for(timer::currentFrame = 0; timer::currentFrame < timer::actionSpread; timer::currentFrame++){
//            mtx.lock();
            testPhenotype.moveCells();
            testPhenotype.recordIntersections();
            testPhenotype.updateAllConnectionPositions();
            testSensorArray.recordIntersections(phenoPointer);
//            printf("!");
//            printf(" frame: %d \n",timer::currentFrame);
//            mtx.unlock();
        }
        
//        printf("%d ticks completed of %d, %f%% complete\n", timer::currentTick, timer::ticks,((timer::currentTick*1.0/timer::ticks*1.0)*100.0));
        
    }
    testPhenotype.cellArray.printCellArray();
    if(global::printStuff){
        printf("\nBuild me a robot!\n");
    }
    CellArray testCellArray = testPhenotype.cellArray;
    Robot finalRobot = Robot(&testSensorArray, &testPhenotype, &testCellArray);
    finalRobot.printRobot();
}
