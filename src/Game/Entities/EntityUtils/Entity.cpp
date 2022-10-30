#include "Entity.h"

Entity::Entity(const HitBox& hitbox, int health) {
    this->hitbox = hitbox;
    this->health = health;
}

Entity::~Entity(){}

void Entity::inOverworldDraw(void* camera) {
    overworldSprite.draw(hitbox.getX(), hitbox.getY(), hitbox.getWidth(), hitbox.getHeight());
}

HitBox& Entity::getHitBox(){
    return hitbox;
}
