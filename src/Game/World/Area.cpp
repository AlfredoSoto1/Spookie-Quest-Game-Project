#include "Area.h"

Area::Area(string name, Area *nextArea, string areaImagePath, string areaMusicPath, string areaStagePath, ofPoint entrancePosition, vector<Entity*> entitiesInArea) {
    this->name = name;
    this->nextArea = nextArea;
    areaImage.load(areaImagePath);
    areaMusic.load(areaMusicPath);
    areaStage.load(areaStagePath);
    this->entrancePosition = entrancePosition;
    this->entitiesInArea = entitiesInArea;
}

string Area::getName() {
    return name;
}
ofImage Area::getImage() {
    return areaImage;
}

ofImage Area::getStage() {
    return areaStage;
}

ofSoundPlayer Area::getMusic() {
    return areaMusic;
}

ofPoint Area::getEntrancePos() {
    return entrancePosition;
}

vector<Entity*> Area::getEntities() {
    return entitiesInArea;
}

Area *Area::getNextArea() {
    return nextArea;
}

void Area::setName(string name) {
    this->name = name;
}
void Area::setEntities(std::vector<Entity*> entitiesInArea) {
    this->entitiesInArea = entitiesInArea;
}

void Area::resetEnemies() {
    for (unsigned int i = 0; i < entitiesInArea.size(); i++) {
        Enemy* enemy = dynamic_cast<Enemy*>(entitiesInArea.at(i));
        if(enemy != nullptr)
            enemy->revive();
    }
}

int Area::getRemainingEnemies() {
    int count = 0;
    for (unsigned int i = 0; i < entitiesInArea.size(); i++) {
        Enemy* enemy = dynamic_cast<Enemy*>(entitiesInArea.at(i));
        if(enemy != nullptr) {
            if (!enemy->isDead())
                count++;
        }
    }
    return count;
}

int Area::getRemainingEntities() {
    return entitiesInArea.size();
}

void Area::clearAllEntities() {
    
}
