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
    // Entity(int ox, int oy, int ow, int oh, int health);
    Entity(const HitBox& hitbox, int health);
    virtual ~Entity();
    virtual void inOverworldUpdate() = 0;
    virtual void inOverworldDraw();

    HitBox& getHitBox();
    // int getOX() { return ox; };
    // int getOY() { return oy; };
    // int getOW() { return ow; };
    // int getOH() { return oh; };
    // ofRectangle getBounds();
    // ofRectangle getBounds(int ox, int oy);
    // bool collides(Entity* entity);
    // void setOX(int ox) { this->ox = ox; };
    // void setOY(int oy) { this->oy = oy; };
    int getHealth() { return health; };
    void setHealth(int health) { this->health = health; };

protected:
    int health;
    // int ox, oy, ow, oh; // Overworld Coordinates and dimensions
    ofImage overworldSprite;
    glm::vec2 velocity;

    HitBox hitbox;
};