#pragma once

#ifndef ATTACK_HEADER
#define ATTACK_HEADER

#include "Animation.h"

enum AttackType {
    sword,
    magic,
    fire,
    sonicBeam
};

class Attack {
public:
    Attack(Animation* attackAnimation, int damage, int maxCoolDown);
    Attack(Animation* attackAnimation, Animation* projectileAnimation, int damage, int maxCoolDown, int projectileSpeed);
    ~Attack();
    
    void setAttackLooks(ofImage img);
    ofImage getAttackLooks();

    AttackType getAttackType();
    Animation* getAnimation();
    Animation* getProjectileAnimation();

    int getDamage();
    float getProjectileTraslation();

    bool provokeAttack(int* health, int baseDamage);
    bool isOnCoolDown();
    bool hasProjectile();
    
    void updateProjectileTraslation();
    void reset();

private:
    int damage;
    int coolDown;
    int maxCoolDown;

    float projectileSpeed;
    float projectileLifeTime;
    float currentProjectileLifeTime;
    float projectileTrajectory;

    bool hasAttacked;
    bool isProjectile;

    Animation* attackAnimation = nullptr;
    Animation* projectileAnimation = nullptr;

    AttackType attackType;

    ofImage attackLooks;

};

#endif