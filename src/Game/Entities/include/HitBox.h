#pragma once

#ifndef HIX_BOX_HEADER
#define HIX_BOX_HEADER

struct HitBox {
public:
    HitBox(int x, int y, int width, int height);
    HitBox();
    ~HitBox();

    void setX(int x);    
    void setY(int y);    
    void setWidth(int w);    
    void setHeight(int h);
    int getX();    
    int getY();    
    int getWidth();    
    int getHeight();

    bool collides(const HitBox& hitBox);

    void setSolid(bool isSolid);    
    
protected:
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

private:
    bool isSolid = false;
};

#endif