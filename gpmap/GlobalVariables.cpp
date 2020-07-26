#include "GlobalVariables.h"

int numberOfCellsCreated = 0;

using namespace timer;

int timer::ticks = 180;
int timer::framesPerTick = 6;
int timer::frames = 30;
int timer::actionSpread = frames / framesPerTick;

int timer::currentTick = 0;
int timer::currentFrame = 0;

using namespace locks;

std::atomic<int> locks::moveCellsLock = {1};
std::atomic<int> locks::recordIntersectionsLock = {1};
std::atomic<int> locks::updateAllConnectionPositionsLock = {1};
std::atomic<int> locks::recordSensorIntersectionsLock = {1};
