#include "EntityFighter.h"

EntityFighter::EntityFighter(int ox, int oy, int ow, int oh, int fx, int fy, int fw, int fh, int health, int baseDamage)
    : Entity(ox, oy, ow, oh, health)
{
    this->fx = fx;
    this->fy = fy;
    this->fh = fh;
    this->fw = fw;
    this->baseDamage = baseDamage;
}

EntityFighter::~EntityFighter(){}

void EntityFighter::fightingDraw() {
    fightingSprite.draw(fx, fy, fw, fh);
}