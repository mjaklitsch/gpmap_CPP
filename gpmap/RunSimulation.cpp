#include "RunSimulation.h"
#include "Phenotype.h"
#include "SensorArray.h"
#include "Robot.h"
#include "GlobalVariables.h"
#include <iostream>
#include <mutex>          // std::mutex

using namespace timer;
using namespace locks;

std::mutex mtx;

void runSimulation(int minN, int maxN, int minP, int maxP,
                   int minIR, int maxIR, int minLM, int maxLM, int minRM,
                   int maxRM){
    
    //  int timer = 0;
    //  int currentTick = 0;
    //  int timerOverlap = actionSpread;
    
    Phenotype testPhenotype = Phenotype(minN, maxN, minP, maxP,
                                        minIR, maxIR, minLM, maxLM, minRM, maxRM);
    SensorArray testSensorArray = SensorArray();
    
    
    testSensorArray.initializeSensors();

    Phenotype *phenoPointer = &testPhenotype;
    
    for(timer::currentTick = 0; timer::currentTick < timer::ticks; timer::currentTick++){
        
//        while(locks::moveCellsLock == 1){};
        
        
        for(timer::currentFrame = 0; timer::currentFrame < timer::frames; timer::currentFrame++){
//            mtx.lock();
            testPhenotype.moveCells();
            testPhenotype.recordIntersections();
            testPhenotype.updateAllConnectionPositions();
            testSensorArray.recordIntersections(phenoPointer);
            printf("!");
            printf("%d \n",timer::currentFrame);
//            mtx.unlock();
        }
        
        printf("%d ticks completed of %d, %f%% complete\n", timer::currentTick, timer::ticks,((timer::currentTick*1.0/timer::ticks*1.0)*100.0));
        
    }
    
    for(int i = 0; i<numberOfCellsCreated; i++){
        
        std::cout<< testPhenotype.cellArray[i].genotype.cellType;
        printf(" :  %d.  ", i);
    
    }
    
    printf("\nBuild me a robot!\n");
    std::vector<Cell> testCellArray = testPhenotype.cellArray;
    Robot finalRobot = Robot(&testSensorArray, &testPhenotype, &testCellArray);
    finalRobot.printRobot();
}
