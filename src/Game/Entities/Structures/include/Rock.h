#pragma once

#ifndef ROCK_HEADER
#define ROCK_HEADER

#include "Entity.h"

class Rock : public Entity {
public:
    Rock(const string& entityName, int ox, int oy, int resistance);
    virtual ~Rock();

    void inOverworldDraw(void* camera) override;
    void inOverworldUpdate();

    ofImage getSprite();

private:
    int renderX = 0;
    int renderY = 0;
};

#endif