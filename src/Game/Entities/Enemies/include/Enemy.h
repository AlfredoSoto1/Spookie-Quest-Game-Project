#pragma once

#ifndef ENEMY_HEADER
#define ENEMY_HEADER

#include "Animation.h"
#include "EntityFighter.h"
#include "HealthBar.h"

class Enemy : public EntityFighter {
public:
    Enemy(string id, int health, int baseDamage, string entityName, int ox, int oy);
    ~Enemy();
    bool isDead();
    void kill();
    void revive();
    
    string getId();
    ofImage getSprite();

    void inOverworldUpdate();
    void fightingUpdate();
    void inOverworldDraw(void* camera) override;
    void reset();

private:
    int speed;
    int movingTime;
    int standingStillTime;

    int linePath = 0;
    int standingStillCounter = 0;
    glm::vec2 timeDirectionCounter;
    glm::vec2 movementDirection;

    bool walking = false;
    int renderX = 1000;
    int renderY = 1000;
    Animation *walkUp;
    Animation *walkDown;
    Animation *walkLeft;
    Animation *walkRight;
    Animation *fighting;
    string id;
    bool dead = false;
    string entityName;
    ofImage sprite;

    int lastXCam = 0;
    int lastYCam = 0;

    HealthBar healthBar;
};

#endif