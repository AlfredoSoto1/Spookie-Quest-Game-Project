#pragma once

#ifndef FRIEND_HEADER
#define FRIEND_HEADER

#include "Entity.h"

class Friend : public Entity {
public:
    Friend(const string& name, const string& path, int ox, int oy);

    void inOverworldUpdate();
    void inOverworldDraw(void* camera);

    void interact();

private:

};

#endif