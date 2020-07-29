#include <atomic>

#ifndef TIMERVARIABLES_H_INCLUDED
#define TIMERVARIABLES_H_INCLUDED

namespace global {
extern int numberOfCellsCreated;
extern bool printStuff;
}


namespace timer{
extern int ticks;
extern int framesPerTick;
extern int frames;
extern int actionSpread;

extern int currentTick;
extern int currentFrame;
};


#endif
