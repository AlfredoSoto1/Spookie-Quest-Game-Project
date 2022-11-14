#pragma once

#ifndef INVENTORY_HEADER
#define INVENTORY_HEADER

#include "Item.h"

class Inventory {
public:
    Inventory();
    ~Inventory();

    int getCurrentSlot();
    void draw();
    void update();

    void addItem(const Item& item);
    void removeItem(const int& slot);
    bool hasItemSlot(ItemE type);

    void nextSlot();
    void prevSlot();
private:
    int inventorySizePxls;

    int slotSelected;

    vector<Item> items;    
};

#endif