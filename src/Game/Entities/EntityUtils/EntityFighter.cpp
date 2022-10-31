#include "EntityFighter.h"

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
    fightingSprite.draw(fightingHitbox.getX(), fightingHitbox.getY(), fightingHitbox.getWidth(), fightingHitbox.getHeight());
}

Attack& EntityFighter::getAttack() {
    return attack;
}

void EntityFighter::setAttack(const Attack& attack) {
    this->attack = attack;
}