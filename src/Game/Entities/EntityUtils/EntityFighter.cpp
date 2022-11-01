#include "EntityFighter.h"

EntityFighter::EntityFighter(const HitBox& hitBox, const HitBox& fightingHitbox, int health, int baseDamage)
    : Entity(hitBox, health), MoveAttack()
{
    this->fightingHitbox = fightingHitbox;
    this->baseDamage = baseDamage;
}

EntityFighter::~EntityFighter(){}

int EntityFighter::getBaseDamage() { 
    return baseDamage; 
}

void EntityFighter::setBaseDamage(int baseDamage) { 
    this->baseDamage = baseDamage; 
}

void EntityFighter::fightingDraw() {
    fightingSprite.draw(fightingHitbox.getX(), fightingHitbox.getY(), fightingHitbox.getWidth(), fightingHitbox.getHeight());
}