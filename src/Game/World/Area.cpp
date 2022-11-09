#include "Area.h"

Area::Area(string name, Area *nextArea, string areaImagePath, string areaMusicPath, string areaStagePath, ofPoint entrancePosition, vector<Entity*> entitiesInArea) {
    this->name = name;
    this->nextArea = nextArea;
    areaImage.load(areaImagePath);
    areaMusic.load(areaMusicPath);
    areaStage.load(areaStagePath);
    this->entrancePosition = entrancePosition;
    this->entitiesInArea = entitiesInArea;
    this->bossFightActivated = false;
}

int Area::getRemainingEnemies() {
    int count = 0;
    for (unsigned int i = 0; i < entitiesInArea.size(); i++) {
        Enemy* enemy = dynamic_cast<Enemy*>(entitiesInArea.at(i));
        if(enemy != nullptr) {
            Boss* boss = dynamic_cast<Boss*>(enemy);
            if(boss != nullptr)
                continue;
            if (!enemy->isDead())
                count++;
        }
    }
    return count;
}

int Area::getDeadEnemies() {
    int count = 0;
    for (unsigned int i = 0; i < entitiesInArea.size(); i++) {
        Enemy* enemy = dynamic_cast<Enemy*>(entitiesInArea.at(i));
        if(enemy != nullptr) {
            Boss* boss = dynamic_cast<Boss*>(enemy);
            if(boss != nullptr)
                continue;
            if (enemy->isDead())
                count++;
        }
    }
    return count;
}

bool Area::inBossFight() {
    return bossFightActivated;
}

int Area::getRemainingEntities() {
    return entitiesInArea.size();
}

void Area::setName(string name) {
    this->name = name;
}
void Area::setEntities(std::vector<Entity*> entitiesInArea) {
    this->entitiesInArea = entitiesInArea;
}

void Area::setInBossFight(bool bossFightActivated) {
    this->bossFightActivated = bossFightActivated;
}

void Area::resetEnemies() {
    for (unsigned int i = 0; i < entitiesInArea.size(); i++) {
        Enemy* enemy = dynamic_cast<Enemy*>(entitiesInArea.at(i));
        if(enemy != nullptr)
            enemy->revive();
    }
}

void Area::clearAllEntities() {
    for(Entity* entity : entitiesInArea) {
        delete entity;
    }
    entitiesInArea.clear();
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

