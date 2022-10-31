#pragma once

#ifndef ENTITY_FIGHTER_HEADER
#define ENTITY_FIGHTER_HEADER

#include "Entity.h"
#include "Attack.h"

class EntityFighter : public Entity {
public:
    EntityFighter(const HitBox& hitbox, const HitBox& fightingHitbox, int health, int baseDamage);
    virtual ~EntityFighter();

    virtual void fightingUpdate() = 0;
    virtual void fightingDraw();

    int getDamage();
    void setDamage(int baseDamage);

    Attack& getAttack();
    void setAttack(const Attack& attack);

protected:
    int baseDamage;
    HitBox fightingHitbox;

    ofImage fightingSprite;

    Attack attack;
};

#endif