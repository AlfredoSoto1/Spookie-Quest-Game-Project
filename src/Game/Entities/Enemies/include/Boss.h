#pragma once

#ifndef BOSS_HEADER
#define BOSS_HEADER

#include "Enemy.h"

class Boss : public Enemy {
public:
    Boss(const string& name, int health, int baseDamage, int phases, int ox, int oy);
    virtual ~Boss();

    int getPhasesCount();
    int getCurrentPhase();

    void reset();
    void reHeal();
    bool hasPhasesLeft();
    bool passToNextPhase();

private:
    int maxPhases;
    int currentPhase;

    bool hasPassedNextPhase;
};

#endif