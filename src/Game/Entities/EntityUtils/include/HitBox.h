#pragma once

#ifndef HIX_BOX_HEADER
#define HIX_BOX_HEADER

enum Direction {
    left,
    right,
    up,
    down
};

struct HitBox {
public:
    HitBox(int x, int y, int width, int height);
    HitBox();
    ~HitBox();

    void setX(int x);    
    void setY(int y);    
    void setWidth(int w);    
    void setHeight(int h);
    int getX() const;    
    int getY() const;    
    int getWidth() const;    
    int getHeight() const;

    void setDirection(const Direction& direction);
    Direction getDirection() const;

    void update();
    void setSolid(bool isSolid);    
    
    bool collides(const HitBox& hitBox);
    
protected:
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    Direction direction = Direction::up;
private:
    volatile bool isSolid = false;

};

#endif