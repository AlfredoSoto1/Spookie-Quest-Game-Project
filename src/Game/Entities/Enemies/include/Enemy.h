#pragma once

#ifndef ENEMY_HEADER
#define ENEMY_HEADER

#include "Animation.h"
#include "EntityFighter.h"

enum EnemyE {
    MUSHROOM, 

};

class Enemy : public EntityFighter {
public:
    Enemy(const string& name, EnemyE type, int health, int baseDamage, int ox, int oy);
    virtual ~Enemy();
    bool isDead();
    void kill();
    void revive();
    
    ofImage getSprite();
    Animation* getDeath();

    void reset();

    virtual void inOverworldUpdate();
    virtual void fightingUpdate();
    virtual void inOverworldDraw(void* camera) override;

private:
    int speed;
    int movingTime;
    int standingStillTime;

    int renderX = 1000;
    int renderY = 1000;
    int linePath = 0;
    int standingStillCounter = 0;
    
    glm::vec2 timeDirectionCounter;
    glm::vec2 movementDirection;

    bool walking = false;
    bool dead = false;
    
    // Animation *walkUp;
    // Animation *walkDown;
    Animation *walkLeft;
    Animation *walkRight;
    Animation *idleRight;
    Animation *idleLeft;

    Animation *fighting;
    Animation *death;
    ofImage sprite;
};

#endif