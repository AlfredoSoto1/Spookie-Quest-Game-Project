#pragma once

#ifndef ROCK_HEADER
#define ROCK_HEADER

#include "Entity.h"

class Structure : public Entity {
public:
    Structure(const string& entityName, const string& path, int ox, int oy, int resistance);
    virtual ~Structure();

    void inOverworldDraw(void* camera) override;
    void inOverworldUpdate();

    ofImage getSprite();

private:
    int renderX = 0;
    int renderY = 0;
};

#endif