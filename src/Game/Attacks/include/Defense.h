#pragma once

#ifndef DEFENSE_HEADER
#define DEFENSE_HEADER

#include "Animation.h"

class Defense {
public:
    Defense(int defensePoint, int maxCoolDown);
    ~Defense();

    int getDefensePoint();

    bool isOnCoolDown();

    void reset();

private:
    int maxCoolDown;
    int defensePoint;
};

#endif