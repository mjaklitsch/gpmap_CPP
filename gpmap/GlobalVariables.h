#include <atomic>

#ifndef TIMERVARIABLES_H_INCLUDED
#define TIMERVARIABLES_H_INCLUDED

extern int numberOfCellsCreated;

namespace timer{
extern int ticks;
extern int framesPerTick;
extern int frames;
extern int actionSpread;

extern int currentTick;
extern int currentFrame;
};

namespace locks{
extern std::atomic<int> moveCellsLock;
extern std::atomic<int> recordIntersectionsLock;
extern std::atomic<int> updateAllConnectionPositionsLock;
extern std::atomic<int> recordSensorIntersectionsLock;
}

#endif
