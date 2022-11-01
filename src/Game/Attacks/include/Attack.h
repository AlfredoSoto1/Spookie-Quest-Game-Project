#pragma once

#ifndef ATTACK_HEADER
#define ATTACK_HEADER

#include "Animation.h"

class Attack {
public:
    // Attack(const Animation& attackAnimation, int damage);
    Attack(int damage, int maxAttackTime);
    ~Attack();

    int getDamage();

    bool hasDone();

    void reset();
    void execute();
private:
    int damage;
    int attackTime;
    int maxAttackTime;
    // Animation attackAnimation;

};

#endif