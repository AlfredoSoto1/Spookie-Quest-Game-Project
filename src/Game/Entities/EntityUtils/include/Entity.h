#pragma once

#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include "ofMain.h"
#include "HitBox.h"

class Entity {
public:
    Entity(const HitBox& hitbox, int health);
    virtual ~Entity();
    virtual void inOverworldUpdate() = 0;
    virtual void inOverworldDraw(void* camera);
    virtual void drawHealthBar(int x, int y, int width, int height, int health, int maxHealth);

    HitBox& getHitBox();

    int getHealth();
    void setHealth(int health);

protected:
    int health;
    ofImage overworldSprite;
    glm::vec2 velocity;

    HitBox hitbox;
};

#endif
