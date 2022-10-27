#include "Rock.h"

Rock::Rock(int ox, int oy, int resistance) : 
    Entity(HitBox(ox, oy, 50, 50), resistance) 
{
    overworldSprite.load("images/entities/inmovable/rock.png");
}

Rock::~Rock() {

}

void Rock::inOverworldDraw() {
    overworldSprite.draw(renderX, renderY, hitbox.getWidth(), hitbox.getHeight());
}

void Rock::inOverworldUpdate() {

}

ofImage Rock::getSprite() { 
    return overworldSprite;
}