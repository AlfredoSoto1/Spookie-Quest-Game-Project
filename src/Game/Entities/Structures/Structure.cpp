#include "Structure.h"
#include "OverworldCamera.h"

Structure::Structure(const string& name, const string& path, int ox, int oy, int resistance) : 
    Entity(name, HitBox(ox, oy, 50, 50), resistance) 
{
    hitbox.setSolid(true);
    overworldSprite.load(path);
}

Structure::~Structure() {

}

void Structure::inOverworldDraw(void* camera) {
    OverworldCamera* cameraPtr = static_cast<OverworldCamera*>(camera);

    double xAspectDif = ofGetWidth() / cameraPtr->getLenzWidth();
    double yAspectDif = ofGetHeight() / cameraPtr->getLenzHeight();

    int playerDistanceX = (hitbox.getRenderX() - cameraPtr->getCameraX()) * xAspectDif;
    int playerDistanceY = (hitbox.getRenderY() - cameraPtr->getCameraY()) * yAspectDif;

    renderX = ofGetWidth() / 2 + playerDistanceX;
    renderY = ofGetHeight() / 2 + playerDistanceY;

    overworldSprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    overworldSprite.draw(renderX, renderY, hitbox.getRenderWidth() * xAspectDif, hitbox.getRenderHeight() * yAspectDif);
}

void Structure::inOverworldUpdate() {

}

ofImage Structure::getSprite() { 
    return overworldSprite;
}