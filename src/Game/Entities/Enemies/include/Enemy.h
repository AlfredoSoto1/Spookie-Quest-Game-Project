#pragma once

#ifndef ENEMY_HEADER
#define ENEMY_HEADER

#include "Animation.h"
#include "EntityFighter.h"

class Enemy : public EntityFighter {
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

public:
    Enemy(string id, int health, int baseDamage, string entityName, int ox, int oy);
    ~Enemy();
    bool isDead() { return dead; };
    void kill() { this->dead = true; };
    void revive() { this->dead = false; };
    void inOverworldUpdate();
    void fightingUpdate();
    void inOverworldDraw(void* camera) override;
    void reset();
    string getId() { return id; };
    ofImage getSprite() { return overworldSprite; };
};

#endif