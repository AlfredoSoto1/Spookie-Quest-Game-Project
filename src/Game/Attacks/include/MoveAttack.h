#pragma once

#ifndef MOVE_ATTACK_HEADER
#define MOVE_ATTACK_HEADER

#include "Attack.h"
#include "Defenses.h"

class MoveAttack {
public:
    MoveAttack();

    int getNumberOfAttacks();
    int getAttackChoice();

    void setAttackChoice(int attackChoice);

    Attack& getAttack(int choice);
    void addAttack(const Attack& attack);

    Defenses& getDefenses();
    void addDefenses(const Defenses& defenses);

protected:
    int attackChoice;
    vector<Attack> attacks;
    vector<Defense> defenses;
};

#endif