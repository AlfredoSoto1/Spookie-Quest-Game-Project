#include "Rock.h"
#include "OverworldCamera.h"

Rock::Rock(const string& name, int ox, int oy, int resistance) : 
    Entity(name, HitBox(ox, oy, 50, 50), resistance) 
{
    hitbox.setSolid(true);
    overworldSprite.load("images/entities/inmovable/rock.png");
}

Rock::~Rock() {

}

void Rock::inOverworldDraw(void* camera) {
    OverworldCamera* cameraPtr = static_cast<OverworldCamera*>(camera);

    int playerDistanceX = hitbox.getX() - cameraPtr->getCameraX();
    int playerDistanceY = hitbox.getY() - cameraPtr->getCameraY();

    if(cameraPtr->getLastMovingDirX() == 0)
        renderX = ofGetWidth()  / 2 + playerDistanceX;
    if(cameraPtr->getLastMovingDirY() == 0)
        renderY = ofGetHeight() / 2 + playerDistanceY;
    overworldSprite.draw(renderX, renderY, hitbox.getWidth(), hitbox.getHeight());
}

void Rock::inOverworldUpdate() {

}

ofImage Rock::getSprite() { 
    return overworldSprite;
}