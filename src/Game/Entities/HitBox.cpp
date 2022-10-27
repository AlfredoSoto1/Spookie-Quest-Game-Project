#include "HitBox.h"
#include "ofMain.h"

HitBox::HitBox(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->isSolid = false;
    this->continueToUpdate = true;
}

HitBox::HitBox() {
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->isSolid = false;
    this->continueToUpdate = true;
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

int HitBox::getX() const {
    return x;
}

int HitBox::getY() const {
    return y;
}

int HitBox::getWidth() const {
    return width;
}

int HitBox::getHeight() const {
    return height;
}

void HitBox::setSolid(bool isSolid) {
    this->isSolid = isSolid;
}

void HitBox::update() {
    if(!continueToUpdate)
        return;
    lastX = x;
    lastY = y;
    lastWidth = width;
    lastHeight = height;
}

bool HitBox::collides(const HitBox& hitbox) {
    bool xCollision = x + width > hitbox.x && x < hitbox.x + hitbox.width;
    bool yCollision = y + height > hitbox.y && y < hitbox.y + hitbox.height;

    //checks if its a solid
    if(!hitbox.isSolid) {
        continueToUpdate = true;
        return xCollision && yCollision;
    }

    //if its not a solid, then check if it has collided
    if(!(xCollision && yCollision)){
        continueToUpdate = true;
        ofSetColor(ofColor::white);
        return false;
    }

    if(x + width > hitbox.x && lastX + lastWidth < hitbox.x) {
        x = hitbox.x - width;
        ofSetColor(ofColor::red);
        continueToUpdate = false;
    }

    else {
        ofSetColor(ofColor::white);
        continueToUpdate = true;
    }

    // else 
    // if(x <= hitbox.x + hitbox.width && lastX > hitbox.lastX + hitbox.lastWidth) {
    //     ofSetColor(ofColor::blue);
    //     x = hitbox.x + hitbox.width;
    //     continueToUpdate = false;
    // }

    return true;
}