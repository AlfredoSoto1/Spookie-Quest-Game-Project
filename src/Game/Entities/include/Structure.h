#pragma once

#ifndef STRUCTURE_HEADER
#define STRUCTURE_HEADER

#include "Entity.h"

class Structure : public Entity {
public:
    Structure(const HitBox& hitbox, int resistance);
    virtual ~Structure();

protected:

private:

};

#endif