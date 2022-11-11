#include "Defense.h"

Defense::Defense(int defensePoint, int maxCooldDown) 
    : defensePoint(defensePoint), maxCoolDown(coolDown)
{
    this->coolDown = 0;
    this->hasDefended = false;
}

Defense::~Defense() {
    
}

// DefenseType Defense::getDefenseType() {
//     return defenseType;
// }

int Defense::getDefensePoint() {
    return defensePoint;
}

bool Defense::isOnCoolDown() {
    return coolDown < maxCoolDown;
}

void Defense::reset() {
    hasDefended = false;
    coolDown = 0;
}