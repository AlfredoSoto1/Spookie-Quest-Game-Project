#include "OverworldCamera.h"

OverworldCamera::OverworldCamera(Player *player) {
    this->player = player;

    // this->playerW = this->player->getOW();
    // this->playerH = this->player->getOH();
    // this->playerX = this->player->getOX() + (this->playerW / 2);
    // this->playerY = this->player->getOY() + (this->playerH / 2);
    HitBox& playerHitBox = this->player->getHitBox();
    this->playerW = playerHitBox.getX();
    this->playerH = playerHitBox.getY();
    this->playerX = playerHitBox.getX() + (this->playerW / 2);
    this->playerY = playerHitBox.getY() + (this->playerH / 2);

    this->leftCornerX = this->playerX - (DIMENSIONX / 2);
    this->rightCornerX = this->playerX + (DIMENSIONX / 2);
    if (this->leftCornerX < 0) {
        this->leftCornerX = 0;
        this->rightCornerX = DIMENSIONX;
    } else if (this->rightCornerX > OXDIMENSION) {
        this->rightCornerX = OXDIMENSION;
        this->leftCornerX = OXDIMENSION - DIMENSIONX;
    }

    this->bottomCornerY = this->playerY + (DIMENSIONY / 2);
    this->topCornerY = this->playerY - (DIMENSIONY / 2);

    if (this->bottomCornerY > OYDIMENSION) {
        this->bottomCornerY = OYDIMENSION;
        this->topCornerY = OYDIMENSION - DIMENSIONY;
    } else if (this->topCornerY < 0) {
        this->topCornerY = 0;
        this->bottomCornerY = DIMENSIONY;
    }
}

void OverworldCamera::update() {
    HitBox& playerHitBox = this->player->getHitBox();
    // this->playerX = this->player->getOX() + (this->playerW / 2);
    // this->playerY = this->player->getOY() + (this->playerH / 2);
    this->playerX = playerHitBox.getX() + (this->playerW / 2);
    this->playerY = playerHitBox.getY() + (this->playerH / 2);

    this->leftCornerX = this->playerX - (DIMENSIONX / 2);
    this->rightCornerX = this->playerX + (DIMENSIONX / 2);
    if (this->leftCornerX < 0) {
        this->leftCornerX = 0;
        this->rightCornerX = DIMENSIONX;
    } else if (this->rightCornerX > OXDIMENSION) {
        this->rightCornerX = OXDIMENSION;
        this->leftCornerX = OXDIMENSION - DIMENSIONX;
    }

    this->bottomCornerY = this->playerY + (DIMENSIONY / 2);
    this->topCornerY = this->playerY - (DIMENSIONY / 2);

    if (this->bottomCornerY > OXDIMENSION) {
        this->bottomCornerY = OXDIMENSION;
        this->topCornerY = OXDIMENSION - DIMENSIONY;
    } else if (this->topCornerY < 0) {
        this->topCornerY = 0;
        this->bottomCornerY = DIMENSIONY;
    }
}
