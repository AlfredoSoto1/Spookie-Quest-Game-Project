#include "Attack.h"

// Attack::Attack(const Animation& attackAnimation, int damage) :
//     attackAnimation(attackAnimation), damage(damage)
// {
    
// }

Attack::Attack(int damage, int coolDown) :
    damage(damage), maxCoolDown(coolDown)
{
    this->coolDown = 0;
    this->hasAttacked = false;
}

Attack::~Attack() {
    
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
