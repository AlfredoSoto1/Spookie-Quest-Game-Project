#pragma once

#ifndef ENEMY_HEADER
#define ENEMY_HEADER

#include "Animation.h"
#include "EntityFighter.h"

enum EnemyE {
    MUSHROOM, 
    GOBLIN,
    SKELETON,
    EVIL_WIZZARD,
    DARK_WIZZARD,
    FIRE_WORM,
    FLYING_EYE
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
    Animation* getHit();

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
    
    Animation *walkLeft;
    Animation *walkRight;
    Animation *idleRight;
    Animation *idleLeft;

    Animation *fighting;
    Animation *death;
    Animation *hit;
    ofImage sprite;

    void obtainFramesOf(vector<ofImage>* frames, int frameCount, int imgWidth, int imgHeight, const string& path);
};

#endif