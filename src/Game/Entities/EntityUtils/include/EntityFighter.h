#pragma once

#ifndef ENTITY_FIGHTER_HEADER
#define ENTITY_FIGHTER_HEADER

#include "Entity.h"
#include "MoveAttack.h"

class EntityFighter : public Entity, public MoveAttack {
public:
    EntityFighter(const HitBox& hitbox, const HitBox& fightingHitbox, int health, int baseDamage);
    virtual ~EntityFighter();

    virtual void fightingUpdate() = 0;
    virtual void fightingDraw();

    int getBaseDamage();
    void setBaseDamage(int baseDamage);

    HitBox& getFightingHitBox();

protected:
    int baseDamage;
    HitBox fightingHitbox;
    ofImage fightingSprite;
};

#endif