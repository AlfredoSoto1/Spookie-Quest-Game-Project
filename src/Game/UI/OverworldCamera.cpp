#include "OverworldCamera.h"

OverworldCamera::OverworldCamera(Player *player) {
    this->player = player;

    HitBox& playerHitBox = this->player->getHitBox();
    this->playerW = playerHitBox.getWidth();
    this->playerH = playerHitBox.getHeight();

    update();
}

int OverworldCamera::getLenzWidth() {
    return lenzWidth;
}

int OverworldCamera::getLenzHeight() {
    return lenzHeight;
}

void OverworldCamera::update() {
    HitBox& playerHitBox = this->player->getHitBox();

    //set camera to center of player sprite
    this->cameraX = playerHitBox.getX() + playerHitBox.getWidth() / 2;
    this->cameraY = playerHitBox.getY() + playerHitBox.getHeight() / 2;

    //set lenz corner in relation to camera
    this->leftCornerX  = this->cameraX - lenzWidth / 2;
    this->rightCornerX = this->cameraX + lenzWidth / 2;

    this->topCornerY    = this->cameraY - lenzHeight / 2;
    this->bottomCornerY = this->cameraY + lenzHeight / 2;

    //lenz cant move beyond the area is looking
    if (this->leftCornerX < 0) {
        this->leftCornerX = 0;
        this->rightCornerX = lenzWidth;
    } else if (this->rightCornerX > OXDIMENSION) {
        this->rightCornerX = OXDIMENSION;
        this->leftCornerX = OXDIMENSION - lenzWidth;
    }

    if (this->bottomCornerY > OYDIMENSION) {
        this->bottomCornerY = OYDIMENSION;
        this->topCornerY = OYDIMENSION - lenzHeight;
    } else if (this->topCornerY < 0) {
        this->topCornerY = 0;
        this->bottomCornerY = lenzHeight;
    }
}
