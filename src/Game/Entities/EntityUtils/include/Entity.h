#pragma once

#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include "ofMain.h"
#include "HitBox.h"
#include "HealthBar.h"

class Entity {
public:
    Entity(const HitBox& hitbox, int health);
    virtual ~Entity();
    virtual void inOverworldUpdate() = 0;
    virtual void inOverworldDraw(void* camera);

    HitBox& getHitBox();
    HealthBar& getHealthBar();

    int getHealth();
    void setHealth(int health);

protected:
    int health;
    ofImage overworldSprite;
    glm::vec2 velocity;

    HitBox hitbox;
    HealthBar healthBar;
};

#endif
