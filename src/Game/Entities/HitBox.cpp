#include "HitBox.h"

HitBox::HitBox(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

HitBox::HitBox() {
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
}

HitBox::~HitBox() {}

void HitBox::setX(int x) {
    this->x = x;
}

void HitBox::setY(int y) {
    this->y = y;
}

void HitBox::setWidth(int w) {
    this->width = w;
}

void HitBox::setHeight(int h) {
    this->height = h;
}

int HitBox::getX() {
    return x;
}

int HitBox::getY() {
    return y;
}

int HitBox::getWidth() {
    return width;
}

int HitBox::getHeight() {
    return height;
}

void HitBox::setSolid(bool isSolid) {
    this->isSolid = isSolid;
}

bool HitBox::collides(const HitBox& hitBox) {
    bool xCollision = x + width > hitBox.x && x < hitBox.x + hitBox.width;
    bool yCollision = y + height > hitBox.y && y < hitBox.y + hitBox.height;
    return xCollision && yCollision; 
}