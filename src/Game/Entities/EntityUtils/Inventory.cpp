#include "Inventory.h"

#define BIAS_CENTER 5

Inventory::Inventory() {
    //prepare hotbar
    this->inventorySizePxls = 60;
    this->slotSelected = 0;
}

Inventory::~Inventory() {
    items.clear();
}

int Inventory::getCurrentSlot() {
    return slotSelected;
}

void Inventory::nextSlot() {
    slotSelected++;
    if(slotSelected == (int)items.size()) {
        slotSelected = 0;
    }
}

void Inventory::prevSlot() {
    slotSelected--;
    if(slotSelected < 0) {
        slotSelected = (int)items.size() - 1;
    }
}

void Inventory::draw() {

    if(items.empty()) {
        return;
    }
    int hotbarHeight = inventorySizePxls * items.size();
    int xRender = ofGetWidth() - inventorySizePxls;
    int yRender = ofGetHeight() / 2 - hotbarHeight / 2;

    //draw hotbar
    ofSetColor(0, 0, 0, 128); //semi transparent
    ofDrawRectangle(xRender, yRender, inventorySizePxls, hotbarHeight);
    ofSetColor(ofColor::white);

    //drawItems
    for(unsigned int i = 0; i < items.size(); i++) {
        int slotItemPos = inventorySizePxls * i + BIAS_CENTER;
        int slotRenderY = yRender + slotItemPos;
        int slotRenderX = xRender + BIAS_CENTER;
        items[i].getImage().getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        items[i].getImage().draw(slotRenderX, slotRenderY, inventorySizePxls - BIAS_CENTER * 2, inventorySizePxls - BIAS_CENTER * 2);
    }

    //draw selected item
    ofNoFill();
    ofSetLineWidth(BIAS_CENTER);
    ofDrawRectangle(xRender, yRender + slotSelected * inventorySizePxls, inventorySizePxls, inventorySizePxls);
    ofFill();
}

void Inventory::update() {
    
}

bool Inventory::hasItemSlot(ItemE type) {
    if(items.empty())
        return false;
    if(items[slotSelected].getType() == type) {
        return true;
    }
    return false;
}

void Inventory::addItem(const Item& item) {
    items.push_back(item);
}
void Inventory::removeItem(const int& slot) {
    int iterator = 0;
    while(items.size() != iterator) {
        if(iterator == slot) {
            items.erase(items.begin() + iterator);
        }else {
            iterator++;
        }
    }

    if(slotSelected == (int)items.size()) {
        slotSelected = 0;
    }
}