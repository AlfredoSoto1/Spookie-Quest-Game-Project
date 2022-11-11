#include "OverworldCamera.h"

OverworldCamera::OverworldCamera(Player *player, Area* area) {
    this->player = player;
    this->player->loadCamera(this);

    HitBox& playerHitBox = this->player->getHitBox();
    this->playerW = playerHitBox.getRenderWidth();
    this->playerH = playerHitBox.getRenderHeight();

    this->currentAreaWidth = area->getImage().getWidth();
    this->currentAreaHeight = area->getImage().getHeight();
    update();
}

double OverworldCamera::getLenzWidth() {
    return lenzWidth;
}

double OverworldCamera::getLenzHeight() {
    return lenzHeight;
}

void OverworldCamera::update() {
    HitBox& playerHitBox = this->player->getHitBox();

    //set camera to center of player sprite
    this->cameraX = playerHitBox.getX() + playerHitBox.getRenderWidth() / 2;
    this->cameraY = playerHitBox.getY() + playerHitBox.getRenderHeight() / 2;

    //set lenz corner in relation to camera
    this->leftCornerX  = this->cameraX - lenzWidth / 2;
    this->rightCornerX = this->cameraX + lenzWidth / 2;

    this->topCornerY    = this->cameraY - lenzHeight / 2;
    this->bottomCornerY = this->cameraY + lenzHeight / 2;

    //lenz cant move beyond the area is looking
    if (this->leftCornerX < 0) {
        this->leftCornerX = 0;
        this->rightCornerX = lenzWidth;
        this->cameraX = lenzWidth / 2;
    } else if (this->rightCornerX > currentAreaWidth) {
        this->rightCornerX = currentAreaWidth;
        this->leftCornerX = currentAreaWidth - lenzWidth;
        this->cameraX = currentAreaWidth - lenzWidth / 2;
    }

    if (this->bottomCornerY > currentAreaHeight) {
        this->bottomCornerY = currentAreaHeight;
        this->topCornerY = currentAreaHeight - lenzHeight;
        this->cameraY = currentAreaHeight - lenzHeight / 2;
    } else if (this->topCornerY < 0) {
        this->topCornerY = 0;
        this->bottomCornerY = lenzHeight;
        this->cameraY = lenzHeight / 2;
    }
}
