#pragma once

#ifndef ITEM_HEADER
#define ITEM_HEADER

#include "ofMain.h"

enum ItemE {
    ELIXIR
};

class Item {
public:
    Item(ItemE type, const ofImage& image);
    Item() {}
    ~Item();

    ofImage& getImage();
    ItemE getType();

private:
    ItemE type;
    ofImage itemImage;
};

#endif