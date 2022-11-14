#include "Attack.h"

Attack::Attack(Animation* attackAnimation, int damage, int coolDown)
    : attackAnimation(attackAnimation), damage(damage), maxCoolDown(coolDown)
{
    this->coolDown = 0;
    this->hasAttacked = false;
    this->isProjectile = false;
}

Attack::Attack(Animation* attackAnimation, Animation* projectileAnimation, int damage, int coolDown, int projectileLifeTime)
    : attackAnimation(attackAnimation), projectileAnimation(projectileAnimation),
     damage(damage), maxCoolDown(coolDown), projectileLifeTime(projectileLifeTime)
{
    this->coolDown = 0;
    this->hasAttacked = false;
    this->isProjectile = true;
    this->currentProjectileLifeTime = projectileLifeTime;
    this->projectileTrajectory = 0;
}

Attack::~Attack() {
    
}

void Attack::setAttackLooks(ofImage img) {
    this->attackLooks = img;
}

ofImage Attack::getAttackLooks() {
    return attackLooks;
}

Animation* Attack::getProjectileAnimation() {
    if(isProjectile)
        return projectileAnimation;
    else
        return nullptr;
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

bool Attack::hasProjectile() {
    return isProjectile;
}

float Attack::getProjectileTraslation() {
    return projectileTrajectory;
}

void Attack::updateProjectileTraslation() {
    projectileTrajectory += currentProjectileLifeTime;
    currentProjectileLifeTime *= 0.9;
}

void Attack::reset() {
    hasAttacked = false;
    coolDown = 0;
    projectileTrajectory = 0;
    currentProjectileLifeTime = projectileLifeTime;

    if(isProjectile) {
        projectileAnimation->resetTime();
    }
}
