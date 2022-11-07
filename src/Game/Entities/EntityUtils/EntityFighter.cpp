#include "EntityFighter.h"

EntityFighter::EntityFighter(const string& name, const HitBox& hitBox, const HitBox& fightingHitbox, int health, int baseDamage)
    : Entity(name, hitBox, health), MoveAttack()
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

HitBox& EntityFighter::getFightingHitBox() {
    return fightingHitbox;
} 

void EntityFighter::fightingDraw() {
    fightingSprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    fightingSprite.draw(fightingHitbox.getX(), fightingHitbox.getY(), fightingHitbox.getWidth(), fightingHitbox.getHeight());
}