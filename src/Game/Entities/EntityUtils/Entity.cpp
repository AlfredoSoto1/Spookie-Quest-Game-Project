#include "Entity.h"

unsigned int Entity::universalId = 0;

Entity::Entity(const string& name, const HitBox& hitbox, int health) {
    this->name = name;
    this->hitbox = hitbox;
    this->health = health;
    this->id = universalId++;
}

Entity::~Entity(){}

void Entity::inOverworldDraw(void* camera) {
    overworldSprite.draw(hitbox.getX(), hitbox.getY(), hitbox.getWidth(), hitbox.getHeight());
}

void Entity::drawHealthBar(int x, int y, int width, int height, int health, int maxHealth) {
    double ratio = (double)health / maxHealth;
    float barGradient = 3.0;
    for (int i = 0; i < barGradient; i++) {
        if (ratio < 0)
            ratio = 0;
        else if (ratio < 1.0/3.0)
            ofSetColor(200 - i * 20, 60 - i * 20, 60 - i * 20);
        else if (ratio < 2.0/3.0)
            ofSetColor(180 - i * 20, 200 - i * 20, 60 - i * 20);
        else
            ofSetColor(60 - i * 20, 180 - i * 20, 80 - i * 20);

        ofDrawRectangle(x, y + i * height / barGradient, width * ratio, height / barGradient);
    }
    ofFill();
    ofSetColor(255, 255, 255);
}

int Entity::getId() {
    return id;
}

int Entity::getHealth() {
    return health;
}

void Entity::setHealth(int health) {
    this->health = health;
}

void Entity::setName(const string& name) {
    this->name = name;
}

string& Entity::getName() {
    return name;
}

HitBox& Entity::getHitBox() {
    return hitbox;
}
