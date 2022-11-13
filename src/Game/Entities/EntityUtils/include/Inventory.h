#pragma once

#ifndef INVENTORY_HEADER
#define INVENTORY_HEADER

#include "Item.h"

class Inventory {
public:
    Inventory();
    ~Inventory();

    void draw();
    void update();

    void addItem(const Item& item);
    void removeItem(const int& slot);

    void nextSlot();
    void prevSlot();
private:
    int inventorySizePxls;

    int slotSelected;

    vector<Item> items;    
};

#endif