#include <vector>

#ifndef SENSORDOT_H_INCLUDED
#define SENSORDOT_H_INCLUDED

class SensorDot{
public:
    std::vector<int> connections;
    
    float xPos;
    float yPos;
    SensorDot();
    SensorDot(float tempxPos, float tempyPos);
};

#endif
