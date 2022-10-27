#pragma once

#include "ofMain.h"
#include "HitBox.h"

enum Direction {
    left,
    right,
    up,
    down
};

class Entity {
public:
    Entity(const HitBox& hitbox, int health);
    virtual ~Entity();
    virtual void inOverworldUpdate() = 0;
    virtual void inOverworldDraw();

    HitBox& getHitBox();
    int getHealth() { return health; };
    void setHealth(int health) { this->health = health; };

protected:
    int health;
    ofImage overworldSprite;
    glm::vec2 velocity;

    HitBox hitbox;
};