#include "RunSimulation.hpp"
#include <iostream>
#include <chrono>



int main(int argc, char* argv[]){
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    
    srand((int)time(NULL));
    // Phenotype Generation Variables
    int minNeurons = 2;
    int minPhotosensors = 2;
    int minIRSensors = 2;
    int minLeftMotors = 1;
    int minRightMotors = 1;
    
    int maxNeurons = 4;
    int maxPhotosensors = 4;
    int maxIRSensors = 4;
    int maxLeftMotors = 1;
    int maxRightMotors = 1;
    bool testMode;
    if(argc > 1){
        testMode = true;
        printf("TEST MODE!%d\n",argc);
    } else {
        testMode = false;
    }
    
    runSimulation(minNeurons, maxNeurons, minPhotosensors,
                  maxPhotosensors, minIRSensors, maxIRSensors,
                  minLeftMotors, maxLeftMotors, minRightMotors,
                  maxRightMotors, testMode);
    
    if(testMode){
        printf("TEST MODE!\n");
    }
    
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    
    printf("Execution time of program is %f seconds\n", time_span.count());
    return 0;
}
