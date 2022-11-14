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

    FriendE getType();

private:
    FriendE friendType;

    Animation *walkLeft;
    Animation *walkRight;
    Animation *idleRight;
    Animation *idleLeft;

    glm::vec2 movementDirection;
    glm::vec2 timeDirectionCounter;

    int speed;
    int movingTime;
    int standingStillTime;

    int renderX = 0;
    int renderY = 0;
    int linePath = 0;
    int standingStillCounter = 0;

    bool walking = false;

    void obtainFramesOf(vector<ofImage>* frames, int frameCount, int imgWidth, int imgHeight, const string& path);
};

#endif