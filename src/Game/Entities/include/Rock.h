#pragma once

#ifndef ROCK_HEADER
#define ROCK_HEADER

#include "Structure.h"

class Rock : public Structure {
public:
    Rock(int ox, int oy, int resistance);
    virtual ~Rock();

    void inOverworldDraw() override;
    void inOverworldUpdate();

    ofImage getSprite();

    void setRenderX(int x) { renderX = x; };
    void setRenderY(int y) { renderY = y; };
protected:

private:
    int renderX = 0;
    int renderY = 0;
};

#endif