#pragma once

#ifndef OVERWORLD_CAMERA_HEADER
#define OVERWORLD_CAMERA_HEADER

//Area image resolution
#define OXDIMENSION 2688
#define OYDIMENSION 2560

#include "Player.h"

class OverworldCamera {
private:
    Player *player;
    int cameraX, cameraY;
    int playerW, playerH;
    int leftCornerX;
    int rightCornerX;
    int topCornerY;
    int bottomCornerY;

    //this values should be larger or equal to
    //window scale
    double lenzWidth = 1280.0;
    double lenzHeight = 720.0;

    int lastMovingDirX = 0;
    int lastMovingDirY = 0;

public:
    OverworldCamera(Player *player);
    void update();

    //returns the direction of movement before stoping
    int getLastMovingDirX() { return lastMovingDirX;}
    int getLastMovingDirY() { return lastMovingDirY;}

    int getCameraX() { return cameraX; };
    int getCameraY() { return cameraY; };

    int getLeftCornerX() { return leftCornerX; };
    int getRightCornerX() { return rightCornerX; };

    double getLenzWidth();
    double getLenzHeight();

    int getTopCornerY() { return topCornerY; };
    int getBottomCornerY() { return bottomCornerY; };
};

#endif 