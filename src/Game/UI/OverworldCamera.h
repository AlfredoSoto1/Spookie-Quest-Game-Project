#pragma once

#include "EntityManager.h"

// #define DIMENSIONX 640
// #define DIMENSIONY 480
#define OXDIMENSION 2688 //2688
#define OYDIMENSION 2560 //2560

class OverworldCamera {
private:
    Player *player;
    int cameraX, cameraY;
    int playerW, playerH;
    int leftCornerX;
    int rightCornerX;
    int topCornerY;
    int bottomCornerY;

public:
    OverworldCamera(Player *player);
    void update();

    int getCameraX() { return cameraX; };
    int getCameraY() { return cameraY; };
    int getDimensionX() { return ofGetWidth(); };
    int getDimensionY() { return ofGetHeight(); };
    int getLeftCornerX() { return leftCornerX; };
    int getRightCornerX() { return rightCornerX; };
    int getTopCornerY() { return topCornerY; };
    int getBottomCornerY() { return bottomCornerY; };
};