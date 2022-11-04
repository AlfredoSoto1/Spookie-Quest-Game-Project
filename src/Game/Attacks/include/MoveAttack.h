#pragma once

#ifndef MOVE_ATTACK_HEADER
#define MOVE_ATTACK_HEADER

#include "Attack.h"
#include "Defense.h"

class MoveAttack {
public:
    MoveAttack();

    int getNumberOfAttacks();
    int getAttackChoice();

    void setAttackChoice(int attackChoice);

    Attack& getAttack(int choice);
    void addAttack(const Attack& attack);

    Defense& getDefenses(int choice);
    void addDefenses(const Defense& defense);

protected:
    int attackChoice;
    vector<Attack> attacks;
    vector<Defense> defenses;
};

#endif