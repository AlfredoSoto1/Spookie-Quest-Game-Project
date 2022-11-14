#pragma once

#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "Animation.h"
#include "EntityFighter.h"
#include "Inventory.h"

class Player : public EntityFighter {

public:
    Player(const string& playerName, int health, int baseDamage);
    ~Player();

    Inventory* getInventory();
    Animation* getDeath();
    Animation* getHit();

    void loadCamera(void* camera);

    void drawAttackList();

    void inOverworldUpdate();
    void fightingUpdate();
    
    void inOverworldDraw(void* camera) override;

    void keyPressed(int key);
    void keyReleased(int key);
    void reset();
private:
    int speed = 8;
    bool walking = false;
    Animation *walkUp;
    Animation *walkDown;
    Animation *walkLeft;
    Animation *walkRight;
    Animation *fighting;
    Animation *death;
    Animation *hit;

    vector<char> pressedKeys;

    ofImage healthBar;

    Inventory* inventory;

    void* camera;

    void obtainFramesOf(vector<ofImage>* frames, int frameCount, int imgWidth, int imgHeight, const string& path);
};

#endif