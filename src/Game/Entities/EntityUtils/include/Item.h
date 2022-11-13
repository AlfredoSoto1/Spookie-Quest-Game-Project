#pragma once

#ifndef ITEM_HEADER
#define ITEM_HEADER

#include "ofMain.h"

class Item {
public:
    Item(const ofImage& image);
    ~Item();

    ofImage& getImage();

private:
    ofImage itemImage;
};

#endif