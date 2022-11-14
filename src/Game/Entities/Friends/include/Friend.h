#pragma once

#ifndef FRIEND_HEADER
#define FRIEND_HEADER

#include "Animation.h"
#include "Entity.h"

enum FriendE {
    WIZZARD
};

class Friend : public Entity {
public:
    Friend(const string& name, FriendE friendType, int ox, int oy);
    ~Friend();

    void inOverworldUpdate();
    void inOverworldDraw(void* camera);

    void interact();
    void drawInteraction(void* camera);

    FriendE getType();

private:
    FriendE friendType;

    Animation *walkLeft;
    Animation *walkRight;
    Animation *idleRight;
    Animation *idleLeft;

    ofImage textNineSlice[9];

    glm::vec2 movementDirection;
    glm::vec2 timeDirectionCounter;

    int speed;
    int initialSpeed;
    int movingTime;
    int standingStillTime;

    int renderX = 0;
    int renderY = 0;
    int linePath = 0;
    int standingStillCounter = 0;

    bool walking = false;

    bool isInteracting = false;

    void drawSpeech(int x, int y, int w, int h, int borderSize);
    void obtainFramesOf(vector<ofImage>* frames, int frameCount, int imgWidth, int imgHeight, const string& path);
};

#endif