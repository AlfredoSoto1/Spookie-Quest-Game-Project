#pragma once

#ifndef ATTACK_HEADER
#define ATTACK_HEADER

#include "Animation.h"

class Attack {
public:
    // Attack(const Animation& attackAnimation, int damage);
    Attack(int damage);
    ~Attack();

protected:
    

private:
    int damage;

    // Animation attackAnimation;

};

#endif