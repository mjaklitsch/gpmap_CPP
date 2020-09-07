#include <string>
#ifndef GENOTYPE_H_INCLUDED
#define GENOTYPE_H_INCLUDED

class Gene {
private:
    std::string cellType;
    float theta;
    float growthDelay;
    float growthRate;
    float growthDuration;
    float speed;
    float movementDelay;
    float movementDuration;
public:
    
    Gene();
    Gene(std::string tempCellType, float tempTheta, float tempGrowthDelay,
         float tempGrowthRate, float tempGrowthDuration, float tempSpeed,
         float tempMovementDelay, float tempMovementDuration);
    
    std::string getCellType();
    float getTheta();
    float getGrowthDelay();
    float getGrowthRate();
    float getGrowthDuration();
    float getSpeed();
    float getMovementDelay();
    float getMovementDuration();
    
    void setCellType(std::string type);
    void setTheta(float t);
    void setGrowthDelay(float gde);
    void setGrowthRate(float ge);
    void setGrowthDuration(float gdu);
    void setSpeed(float s);
    void setMovementDelay(float mde);
    void setMovementDuration(float mdu);
};

#endif
