#include "Entity.h"

Entity::Entity(const HitBox& hitbox, int health) {
    this->hitbox = hitbox;
    this->health = health;
}

Entity::~Entity(){}

void Entity::inOverworldDraw(void* camera) {
    overworldSprite.draw(hitbox.getX(), hitbox.getY(), hitbox.getWidth(), hitbox.getHeight());
}

int Entity::getHealth() {
    return health;
}

void Entity::setHealth(int health) {
    this->health = health;
}

HealthBar& Entity::getHealthBar() {
    return healthBar;
}

HitBox& Entity::getHitBox() {
    return hitbox;
}
