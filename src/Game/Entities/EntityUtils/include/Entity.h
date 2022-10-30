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

    HitBox& getHitBox();
    int getHealth() { return health; };
    void setHealth(int health) { this->health = health; };

protected:
    int health;
    ofImage overworldSprite;
    glm::vec2 velocity;

    HitBox hitbox;
};

#endif
