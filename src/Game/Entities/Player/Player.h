#pragma once

#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "Animation.h"
#include "EntityFighter.h"

class Player : public EntityFighter {
private:
    int speed = 8;
    bool walking = false;
    Animation *walkUp;
    Animation *walkDown;
    Animation *walkLeft;
    Animation *walkRight;
    Animation *fighting;
    vector<char> pressedKeys;

    ofImage healthBar;
    ofImage buttonAttack;

    void* camera;

public:
    Player(const string& playerName, int health, int baseDamage);
    ~Player();

    void loadCamera(void* camera);

    void drawAttackList();

    void inOverworldUpdate();
    void fightingUpdate();
    
    void inOverworldDraw(void* camera) override;

    void keyPressed(int key);
    void keyReleased(int key);
    void reset();
};

#endif