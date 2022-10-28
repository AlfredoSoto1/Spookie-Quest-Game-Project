#include "OverworldCamera.h"

OverworldCamera::OverworldCamera(Player *player) {
    this->player = player;

    HitBox& playerHitBox = this->player->getHitBox();
    this->playerW = playerHitBox.getWidth();
    this->playerH = playerHitBox.getHeight();

    //set camera to center of player sprite
    this->cameraX = OXDIMENSION * (playerHitBox.getX() + playerHitBox.getWidth() / 2) / ofGetWidth();
    this->cameraY = OYDIMENSION * (playerHitBox.getY() + playerHitBox.getHeight() / 2) / ofGetHeight();

    //set lenz corner in relation to camera
    this->leftCornerX = this->cameraX - ofGetWidth() / 2;
    this->rightCornerX = this->cameraX + ofGetWidth() / 2;

    this->topCornerY = this->cameraY - ofGetHeight() / 2;
    this->bottomCornerY = this->cameraY + ofGetHeight() / 2;

    //lenz cant move beyond the area is looking
    if (this->leftCornerX < 0) {
        this->leftCornerX = 0;
        this->rightCornerX = ofGetWidth();
    } else if (this->rightCornerX > OXDIMENSION) {
        this->rightCornerX = OXDIMENSION;
        this->leftCornerX = OXDIMENSION - ofGetWidth();
    }

    if (this->bottomCornerY > OYDIMENSION) {
        this->bottomCornerY = OYDIMENSION;
        this->topCornerY = OYDIMENSION - ofGetHeight();
    } else if (this->topCornerY < 0) {
        this->topCornerY = 0;
        this->bottomCornerY = ofGetHeight();
    }


    // this->cameraX = playerHitBox.getX() + (this->playerW / 2);
    // this->cameraY = playerHitBox.getY() + (this->playerH / 2);

    // this->leftCornerX = this->cameraX - (ofGetWidth() / 2);
    // this->rightCornerX = this->cameraX + (ofGetWidth() / 2);
    // if (this->leftCornerX < 0) {
    //     this->leftCornerX = 0;
    //     this->rightCornerX = ofGetWidth();
    // } else if (this->rightCornerX > OXDIMENSION) {
    //     this->rightCornerX = OXDIMENSION;
    //     this->leftCornerX = OXDIMENSION - ofGetWidth();
    // }

    // this->bottomCornerY = this->cameraY + (ofGetHeight() / 2);
    // this->topCornerY = this->cameraY - (ofGetHeight() / 2);

    // if (this->bottomCornerY > OYDIMENSION) {
    //     this->bottomCornerY = OYDIMENSION;
    //     this->topCornerY = OYDIMENSION - ofGetHeight();
    // } else if (this->topCornerY < 0) {
    //     this->topCornerY = 0;
    //     this->bottomCornerY = ofGetHeight();
    // }
}

void OverworldCamera::update() {
    HitBox& playerHitBox = this->player->getHitBox();

    //set camera to center of player sprite
    this->cameraX = OXDIMENSION * (playerHitBox.getX() + playerHitBox.getWidth() / 2) / ofGetWidth();
    this->cameraY = OYDIMENSION * (playerHitBox.getY() + playerHitBox.getHeight() / 2) / ofGetHeight();

    //set lenz corner in relation to camera
    this->leftCornerX = this->cameraX - ofGetWidth() / 2;
    this->rightCornerX = this->cameraX + ofGetWidth() / 2;

    this->topCornerY = this->cameraY - ofGetHeight() / 2;
    this->bottomCornerY = this->cameraY + ofGetHeight() / 2;

    //lenz cant move beyond the area is looking
    if (this->leftCornerX < 0) {
        this->leftCornerX = 0;
        this->rightCornerX = ofGetWidth();
    } else if (this->rightCornerX > OXDIMENSION) {
        this->rightCornerX = OXDIMENSION;
        this->leftCornerX = OXDIMENSION - ofGetWidth();
    }

    if (this->bottomCornerY > OYDIMENSION) {
        this->bottomCornerY = OYDIMENSION;
        this->topCornerY = OYDIMENSION - ofGetHeight();
    } else if (this->topCornerY < 0) {
        this->topCornerY = 0;
        this->bottomCornerY = ofGetHeight();
    }

    //////////////////////////////////////////////////////////////////////
    // this->playerX = playerHitBox.getX() + (this->playerW / 2);
    // this->playerY = playerHitBox.getY() + (this->playerH / 2);

    // this->leftCornerX = this->playerX - (ofGetWidth() / 2);
    // this->rightCornerX = this->playerX + (ofGetWidth() / 2);
    // if (this->leftCornerX < 0) {
    //     this->leftCornerX = 0;
    //     this->rightCornerX = ofGetWidth();
    // } else if (this->rightCornerX > OXDIMENSION) {
    //     this->rightCornerX = OXDIMENSION;
    //     this->leftCornerX = OXDIMENSION - ofGetWidth();
    // }

    // this->bottomCornerY = this->playerY + (ofGetHeight() / 2);
    // this->topCornerY = this->playerY - (ofGetHeight() / 2);

    // if (this->bottomCornerY > OXDIMENSION) {
    //     this->bottomCornerY = OXDIMENSION;
    //     this->topCornerY = OXDIMENSION - ofGetHeight();
    // } else if (this->topCornerY < 0) {
    //     this->topCornerY = 0;
    //     this->bottomCornerY = ofGetHeight();
    // }
}
