#include "Attack.h"

Attack::Attack(Animation* attackAnimation, int damage, int coolDown)
    : attackAnimation(attackAnimation), damage(damage), maxCoolDown(coolDown)
{
    this->coolDown = 0;
    this->hasAttacked = false;
}

Attack::~Attack() {
    
}

Animation* Attack::getAnimation() {
    return attackAnimation;
}

AttackType Attack::getAttackType() {
    return attackType;
}

int Attack::getDamage() {
    return damage;
}

bool Attack::provokeAttack(int* health, int baseDamage) {
    if(!hasAttacked) {
        (*health) -= damage * baseDamage;
        hasAttacked = true;
    }
    coolDown++;

    return hasAttacked;
}

bool Attack::isOnCoolDown() {
    return coolDown < maxCoolDown;
}

void Attack::reset() {
    hasAttacked = false;
    coolDown = 0;
}
