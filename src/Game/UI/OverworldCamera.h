#pragma once

#ifndef OVERWORLD_CAMERA_HEADER
#define OVERWORLD_CAMERA_HEADER

//Area image resolution
// #define OXDIMENSION 2688
// #define OYDIMENSION 2560

#include "Player.h"
#include "Area.h"

class OverworldCamera {
private:
    Player *player;
    int cameraX, cameraY;
    int playerW, playerH;
    int leftCornerX;
    int rightCornerX;
    int topCornerY;
    int bottomCornerY;

    int currentAreaWidth;
    int currentAreaHeight;

    //this values should be larger or equal to
    //window scale
    double lenzWidth = 1280.0;
    double lenzHeight = 720.0;
    // double lenzWidth = 16 * 8;
    // double lenzHeight = 9 * 8;
public:
    OverworldCamera(Player *player, Area* area);
    void update();

    int getCameraX() { return cameraX; };
    int getCameraY() { return cameraY; };

    int getLeftCornerX() { return leftCornerX; };
    int getRightCornerX() { return rightCornerX; };

    double getLenzWidth();
    double getLenzHeight();

    int getCurrentAreaWidth() { return currentAreaWidth; };
    int getCurrentAreaHeight() { return currentAreaHeight; };

    int getTopCornerY() { return topCornerY; };
    int getBottomCornerY() { return bottomCornerY; };
};

#endif 