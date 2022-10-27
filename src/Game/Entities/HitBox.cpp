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

    ofSetColor(ofColor::white);
    ofDrawBitmapString("collision: false", 100, 60);

    if(!hitbox.isSolid)
        return xCollision && yCollision;

    if(!(xCollision && yCollision)){
        continueToUpdate = true;
        ofSetColor(ofColor::white);
        ofDrawBitmapString("collision: false", 100, 60);
        return false;
    }

    if(x + width >= hitbox.x && lastX + lastWidth < hitbox.lastX) {
        x = hitbox.x - width;
        continueToUpdate = false;
        ofSetColor(ofColor::white);
        ofDrawBitmapString("collision: true", 100, 60);
    } 
    // else 
    // if(x <= hitbox.x + hitbox.width && lastX > hitbox.lastX + hitbox.lastWidth) {
    //     ofSetColor(ofColor::blue);
    //     x = hitbox.x + hitbox.width;
    //     continueToUpdate = false;
    // }

    return true;
}