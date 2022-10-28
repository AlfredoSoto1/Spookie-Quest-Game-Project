#pragma once

#include "Entity.h"

class EntityFighter : public Entity {
public:
    // EntityFighter(int ox, int oy, int ow, int oh, int fx, int fy, int fw, int fh, int health, int baseDamage);
    EntityFighter(const HitBox& hitbox, const HitBox& fightingHitbox, int health, int baseDamage);
    virtual ~EntityFighter();

    virtual void fightingUpdate() = 0;
    virtual void fightingDraw();

    int getDamage();
    void setDamage(int baseDamage);

protected:
    int baseDamage;
    // int fx, fy, fw, fh; // Fighting coordinates and dimensions
    HitBox fightingHitbox;

    ofImage fightingSprite;
};