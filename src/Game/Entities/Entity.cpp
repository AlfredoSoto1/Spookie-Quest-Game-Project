#include "Entity.h"

Entity::Entity(int ox, int oy, int ow, int oh, int health) {
    this->ox = ox;
    this->oy = oy;
    this->oh = oh;
    this->ow = ow;
    this->health = health;
}

Entity::~Entity(){}

void Entity::inOverworldDraw() {
    overworldSprite.draw(ox, oy, ow, oh);
}

bool Entity::collides(Entity* entity){
    return this->getBounds().intersects(entity->getBounds());
}

ofRectangle Entity::getBounds(){
    return ofRectangle(ox, oy, ow, oh);
}

ofRectangle Entity::getBounds(int x, int y){
    return ofRectangle(x, y, ow, oh);
}
