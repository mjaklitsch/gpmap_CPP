#include <vector>

#ifndef SENSORDOT_H_INCLUDED
#define SENSORDOT_H_INCLUDED

class SensorDot{
public:
  static std::vector<int> connections;

  static float xPos;
  static float yPos;

  SensorDot(float tempxPos, float tempyPos);
};

#endif
