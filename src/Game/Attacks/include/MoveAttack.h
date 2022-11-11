#pragma once

#ifndef MOVE_ATTACK_HEADER
#define MOVE_ATTACK_HEADER

#include "Attack.h"

class MoveAttack {
public:
    MoveAttack();

    int getNumberOfAttacks();
    int getAttackChoice();

    void setAttackChoice(int attackChoice);

    Attack& getAttack(int choice);
    void addAttack(const Attack& attack);

    vector<Attack>& getAttacks();

protected:
    int attackChoice;
    vector<Attack> attacks;
};

#endif