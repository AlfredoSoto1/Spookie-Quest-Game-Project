#pragma once

#ifndef DEFENSE_HEADER
#define DEFENSE_HEADER

#include "Animation.h"

enum DefenseType {
    sword,
    magic,
    fire,
    sonicBeam
};

class Defense {
public:
    Defense(int defensePoint, int maxCoolDown);
    ~Defense();

    DefenseType getDefenseType();

    int getDefensePoint();
    bool isOnCoolDown();
    void reset();

private:
    int coolDown;
    int maxCoolDown;
    int defensePoint;

    bool hasDefended;

    DefenseType defenseType;
};

#endif