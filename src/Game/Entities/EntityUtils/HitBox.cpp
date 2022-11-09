#include "HitBox.h"
#include "ofMain.h"

HitBox::HitBox(int x, int y, int widthRender, int heightRender) {
    this->x = x;
    this->y = y;
    this->width = widthRender;
    this->height = heightRender;
    this->widthRender= widthRender;
    this->heightRender = heightRender;
    this->isSolid = false;
}

HitBox::HitBox(int x, int y, int widthRender, int heightRender, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->widthRender= widthRender;
    this->heightRender = heightRender;
    this->isSolid = false;
}

HitBox::HitBox() {
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->widthRender = 0;
    this->heightRender = 0;
    this->isSolid = false;
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

void HitBox::setRenderWidth(int w) {
    this->widthRender = w;
}

void HitBox::setRenderHeight(int h) {
    this->heightRender = h;
}

int HitBox::getX() const {
    return x;
}

int HitBox::getY() const {
    return y;
}

int HitBox::getRenderX() const {
    return x - (widthRender - width) / 2;
}

int HitBox::getRenderY() const {
    return y - (heightRender - height) / 2;;
}

int HitBox::getRenderWidth() const {
    return widthRender;
}

int HitBox::getRenderHeight() const {
    return heightRender;
}

int HitBox::getWidth() const {
    return width;
}

int HitBox::getHeight() const {
    return height;
}

void HitBox::setDirection(const Direction& direction) {
    this->direction = direction;
}

Direction HitBox::getDirection() const {
    return this->direction;
}

void HitBox::setSolid(bool isSolid) {
    this->isSolid = isSolid;
}

bool HitBox::collides(const HitBox& hitbox) {

    bool xCollision = x + width  > hitbox.x && x < hitbox.x + hitbox.width;
    bool yCollision = y + height > hitbox.y && y < hitbox.y + hitbox.height;

    //checks if its a solid
    if(!hitbox.isSolid)
        return xCollision && yCollision;

    //if its not a solid, then check if it has collided
    if(!(xCollision && yCollision)){
        return false;
    }

    //check collision by direction
    if(direction == Direction::left || direction == Direction::right) {
        if(x + width > hitbox.x && x < hitbox.x)
            x = hitbox.x - width;
        else if(x < hitbox.x + hitbox.width && x + width > hitbox.x + hitbox.width)
            x = hitbox.x + hitbox.width;
    }else if(direction == Direction::up || direction == Direction::down) {
        if(y + height > hitbox.y && y < hitbox.y)
            y = hitbox.y - height;
        else if(y < hitbox.y + hitbox.height && y + height > hitbox.y + hitbox.height)
            y = hitbox.y + hitbox.height;
    }
    return true;
}

ofColor HitBox::collides(const ofColor& solid, const ofImage& boundryImage) {

    int verticalDif = 0;
    int horizontalDif = 0;

    //get Avrg color inside de collision
    //that is the color to return

    //horizontal dif
    for(int i = 0; i < height; i++) {
        int lastHorizontalDif = 0;
        for(int j = 0; j < width; j++) {
            if(boundryImage.getColor(x + j, y + i) == ofColor::white) {
                lastHorizontalDif++;
            }
        }
        //always pick the largest
        if(horizontalDif < lastHorizontalDif)
            horizontalDif = lastHorizontalDif;
    }
    //vertical dif
    for(int i = 0; i < width; i++) {
        int lastVerticalDif = 0;
        for(int j = 0; j < height; j++) {
            if(boundryImage.getColor(x + i, y + j) == ofColor::white) {
                lastVerticalDif++;
            }
        }
        //always pick the largest
        if(verticalDif < lastVerticalDif)
            verticalDif = lastVerticalDif;
    }

    if(solid == ofColor(0,0,0,0)){
        return boundryImage.getColor(x, y);//avrg color
    }

    if(horizontalDif != 0 && direction == Direction::right) {
        x = x - horizontalDif;
    } else if(horizontalDif != 0 && direction == Direction::left) {
        x = x + horizontalDif;
    }

    if(verticalDif != 0 && direction == Direction::down) {
        y = y - verticalDif;
    } else if(verticalDif != 0 && direction == Direction::up) {
        y = y + verticalDif;
    }

    return boundryImage.getColor(x, y);//avrg color
}