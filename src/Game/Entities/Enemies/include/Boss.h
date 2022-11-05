#pragma once

#ifndef BOSS_HEADER
#define BOSS_HEADER

#include "Enemy.h"

class Boss : public Enemy {
public:
    Boss(const string& name, int health, int baseDamage, int ox, int oy);
    virtual ~Boss();

    // virtual void inOverworldUpdate();
    // virtual void fightingUpdate();
    // virtual void inOverworldDraw(void* camera) override;

private:

// Boss: Implement a Boss class. This class must inherit from the Enemy
// class. Bosses appear in an Area after all other Enemies of that area are
// defeated. A Boss Battle must have at least two phases. That is to say, you
// must deplete the Boss’s health bar twice in order to beat them. Defeating
// a Boss moves the Player to the next Area or a Win State if there are no
// remaining Areas. You must have at least one Boss instance per Area of
// the game

};

#endif