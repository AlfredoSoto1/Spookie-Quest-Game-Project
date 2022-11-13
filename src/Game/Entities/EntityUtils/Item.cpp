#include "Item.h"

Item::Item(const ofImage& itemImage) {
    this->itemImage = itemImage;
}

Item::~Item() {
    
}

ofImage& Item::getImage() {
    return this->itemImage;
}