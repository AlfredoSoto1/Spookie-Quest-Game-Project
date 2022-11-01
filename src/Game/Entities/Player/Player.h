#pragma once

#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "Animation.h"
#include "EntityFighter.h"

#define INIT_X 100
#define INIT_Y 100

#define INIT_BATTLE_X 64
#define INIT_BATTLE_Y 164

#define OXDIMENSION 2688
#define OYDIMENSION 2560

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

public:
    Player(int health, int baseDamage);
    ~Player();

    ofImage& getHealthBar();

    void drawAttackList();

    void inOverworldUpdate();
    void fightingUpdate();
    
    void inOverworldDraw(void* camera) override;

    void keyPressed(int key);
    void keyReleased(int key);
    void reset();
};

#endif