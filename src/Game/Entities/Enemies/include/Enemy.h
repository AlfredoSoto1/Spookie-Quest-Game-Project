#pragma once

#ifndef ENEMY_HEADER
#define ENEMY_HEADER

#include "Animation.h"
#include "EntityFighter.h"

class Enemy : public EntityFighter {
public:
    Enemy(const string& name, int health, int baseDamage, int ox, int oy);
    ~Enemy();
    bool isDead();
    void kill();
    void revive();
    
    ofImage getSprite();

    void inOverworldUpdate();
    void fightingUpdate();
    void inOverworldDraw(void* camera) override;
    void reset();

private:
    int speed;
    int movingTime;
    int standingStillTime;

    int renderX = 1000;
    int renderY = 1000;
    int lastXCam = 0;
    int lastYCam = 0;
    int linePath = 0;
    int standingStillCounter = 0;
    
    glm::vec2 timeDirectionCounter;
    glm::vec2 movementDirection;

    bool walking = false;
    bool dead = false;
    
    Animation *walkUp;
    Animation *walkDown;
    Animation *walkLeft;
    Animation *walkRight;
    Animation *fighting;
    ofImage sprite;
};

#endif