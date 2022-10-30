#pragma once

#ifndef PLAYER_ATTACK_HEADER
#define PLAYER_ATTACK_HEADER

#include "Attack.h"

class PlayerAttack {
public:
    PlayerAttack();

    int getNumberOfAttacks();
    int getCurrentAttack();

    void setCurrentAttack(int currentAttack);

    void drawAttackList();

protected:
    void addAttack(const Attack& attack);

private:
    ofImage buttonAttack;

    int currentAttack;

    vector<Attack> attacks;
};

#endif