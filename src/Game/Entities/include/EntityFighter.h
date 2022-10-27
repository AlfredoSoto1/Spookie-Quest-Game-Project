#pragma once

#include "Entity.h"

class EntityFighter : public Entity {
public:
    EntityFighter(const HitBox& hitbox, const HitBox& fightingHitbox, int health, int baseDamage);
    virtual ~EntityFighter();

    virtual void fightingUpdate() = 0;
    virtual void fightingDraw();

    int getDamage();
    void setDamage(int baseDamage);

protected:
    int baseDamage;
    HitBox fightingHitbox;

    ofImage fightingSprite;
};