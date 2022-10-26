#pragma once

#include "Entity.h"

class EntityFighter : public Entity {
public:
    EntityFighter(int ox, int oy, int ow, int oh, int fx, int fy, int fw, int fh, int health, int baseDamage);
    virtual ~EntityFighter();

    virtual void fightingUpdate() = 0;
    virtual void fightingDraw();

    int getDamage() { return baseDamage; };
    void setDamage(int baseDamage) { this->baseDamage = baseDamage; };

protected:
    int baseDamage;
    int fx, fy, fw, fh; // Fighting coordinates and dimensions

    ofImage fightingSprite;
};