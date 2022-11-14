#include "Item.h"

Item::Item(ItemE type, const ofImage& itemImage) {
    this->itemImage = itemImage;
    this->type = type;
}

Item::~Item() {
    
}

ItemE Item::getType() {
    return type;
}

ofImage& Item::getImage() {
    return this->itemImage;
}