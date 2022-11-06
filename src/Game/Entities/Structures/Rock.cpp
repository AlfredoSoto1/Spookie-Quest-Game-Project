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

    double xAspectDif = ofGetWidth() / 1280.0;
    double yAspectDif = ofGetHeight() / 720.0;

    int playerDistanceX = (hitbox.getX() - cameraPtr->getCameraX()) * xAspectDif;
    int playerDistanceY = (hitbox.getY() - cameraPtr->getCameraY()) * yAspectDif;

    if(cameraPtr->getLastMovingDirX() == 0)
        renderX = ofGetWidth() / 2 + playerDistanceX;
    if(cameraPtr->getLastMovingDirY() == 0)
        renderY = ofGetHeight() / 2 + playerDistanceY;
    overworldSprite.draw(renderX, renderY, hitbox.getWidth() * xAspectDif, hitbox.getHeight() * yAspectDif);
}

void Rock::inOverworldUpdate() {

}

ofImage Rock::getSprite() { 
    return overworldSprite;
}