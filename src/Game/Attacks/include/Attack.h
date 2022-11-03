#pragma once

#ifndef ATTACK_HEADER
#define ATTACK_HEADER

#include "Animation.h"

class Attack {
public:
    // Attack(const Animation& attackAnimation, int damage);
    Attack(int damage, int maxCoolDown);
    ~Attack();

    int getDamage();

    bool provokeAttack(int* health, int baseDamage);

    bool isOnCoolDown();

    void reset();

private:
    int damage;
    int coolDown;
    int maxCoolDown;

    bool hasAttacked;

    // Animation attackAnimation;

};

#endif