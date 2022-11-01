#include "Attack.h"

// Attack::Attack(const Animation& attackAnimation, int damage) :
//     attackAnimation(attackAnimation), damage(damage)
// {
    
// }

Attack::Attack(int damage, int maxAttackTime) :
    damage(damage), maxAttackTime(maxAttackTime), attackTime(maxAttackTime)
{

}

Attack::~Attack() {
    
}

int Attack::getDamage() {
    return damage;
}

bool Attack::hasDone() {
    return attackTime == 0;
}

void Attack::reset() {
    attackTime = maxAttackTime;
}

void Attack::execute() {
    attackTime--;
    if(attackTime < 0)
        attackTime = 0;
}