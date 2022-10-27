#include "EntityFighter.h"

// EntityFighter::EntityFighter(int ox, int oy, int ow, int oh, int fx, int fy, int fw, int fh, int health, int baseDamage)
//     : Entity(ox, oy, ow, oh, health)
// {
//     this->fx = fx;
//     this->fy = fy;
//     this->fh = fh;
//     this->fw = fw;
//     this->baseDamage = baseDamage;
// }

EntityFighter::EntityFighter(const HitBox& hitBox, const HitBox& fightingHitbox, int health, int baseDamage)
    : Entity(hitBox, health)
{
    this->fightingHitbox = fightingHitbox;
    this->baseDamage = baseDamage;
}

EntityFighter::~EntityFighter(){}

int EntityFighter::getDamage() { 
    return baseDamage; 
}

void EntityFighter::setDamage(int baseDamage) { 
    this->baseDamage = baseDamage; 
}

void EntityFighter::fightingDraw() {
    // fightingSprite.draw(fx, fy, fw, fh);
    fightingSprite.draw(fightingHitbox.getX(), fightingHitbox.getY(), fightingHitbox.getWidth(), fightingHitbox.getHeight());
}