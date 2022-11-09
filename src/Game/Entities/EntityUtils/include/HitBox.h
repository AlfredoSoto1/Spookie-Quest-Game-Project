#pragma once

#ifndef HIX_BOX_HEADER
#define HIX_BOX_HEADER

#include "ofMain.h"

enum Direction {
    left,
    right,
    up,
    down
};

struct HitBox {
public:
    HitBox(int x, int y, int width, int height);
    HitBox(int x, int y, int widthRender, int heightRender, int width, int height);
    HitBox();
    ~HitBox();

    void setX(int x);    
    void setY(int y);    
    void setRenderWidth(int w);    
    void setRenderHeight(int h);
    void setWidth(int w);    
    void setHeight(int h);

    int getX() const;    
    int getY() const;   
    int getRenderX() const;    
    int getRenderY() const;    
    int getRenderWidth() const;    
    int getRenderHeight() const;

    int getWidth() const;
    int getHeight() const;

    void setDirection(const Direction& direction);
    Direction getDirection() const;

    void update();
    void setSolid(bool isSolid);    
    
    bool collides(const HitBox& hitBox);
    glm::vec4 collides(const ofColor& solid, const ofImage& boundryImage);
    
protected:
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    int widthRender = 0;
    int heightRender = 0;

    Direction direction = Direction::up;
private:
    volatile bool isSolid = false;

};

#endif