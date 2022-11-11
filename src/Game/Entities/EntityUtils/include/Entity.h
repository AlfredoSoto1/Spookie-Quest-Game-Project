#pragma once

#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include "ofMain.h"
#include "HitBox.h"

class Entity {
public:
    Entity(const string& name, const HitBox& hitbox, int health);
    virtual ~Entity();
    virtual void inOverworldUpdate() = 0;
    virtual void inOverworldDraw(void* camera);
    virtual void drawHealthBar(int x, int y, int width, int height, int health, int maxHealth);

    int getId();
    int getHealth();
    int getMaxHealth();
    
    string& getName();
    HitBox& getHitBox();

    void setHealth(int health);
    void setName(const string& name);

protected:
    static unsigned int universalId;

    int id;
    int health;
    int maxHealth;

    string name;

    HitBox hitbox;
    glm::vec2 velocity;
    ofImage overworldSprite;

};

#endif
