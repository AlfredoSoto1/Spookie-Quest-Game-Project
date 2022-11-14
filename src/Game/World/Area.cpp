#include "Area.h"

Area::Area(AreaE type, Area *nextArea, string areaImagePath, string areaImageBoundryPath, string areaMusicPath, string areaStagePath, ofPoint entrancePosition, vector<Entity*> entitiesInArea) {
    this->type = type;
    this->nextArea = nextArea;

    areaImage.load(areaImagePath);
    areaStage.load(areaStagePath);
    areaImageBoundry.load(areaImageBoundryPath);
    
    areaMusic.load(areaMusicPath);
    
    this->entrancePosition = entrancePosition;
    this->entitiesInArea = entitiesInArea;
    this->bossFightActivated = false;
}

Area::~Area() {
    // delete ambianceAnimation;
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

bool Area::inBossFight() {
    return bossFightActivated;
}

int Area::getRemainingEntities() {
    return entitiesInArea.size();
}

void Area::setEntities(std::vector<Entity*> entitiesInArea) {
    this->entitiesInArea = entitiesInArea;
}

void Area::setInBossFight(bool bossFightActivated) {
    this->bossFightActivated = bossFightActivated;
}

void Area::resetContent() {
    resetEnemies();
    setInBossFight(false);
}

void Area::resetEnemies() {
    for(Entity* entity : entitiesInArea) {
        Enemy* enemy = dynamic_cast<Enemy*>(entity);
        if(enemy != nullptr) {
            Boss* boss = dynamic_cast<Boss*>(enemy);
            if(boss != nullptr) {
                boss->reset();
                boss->revive();
            }else {
                enemy->revive();
            }
        }
    }
    // for (unsigned int i = 0; i < entitiesInArea.size(); i++) {
    //     Enemy* enemy = dynamic_cast<Enemy*>(entitiesInArea.at(i));
    //     if(enemy != nullptr)
    //         enemy->revive();
    // }
}

void Area::clearAllEntities() {
    for(Entity* entity : entitiesInArea) {
        delete entity;
    }
    entitiesInArea.clear();
}

string Area::getName() {
    if(type == AreaE::FOREST) {
        return "forest";
    } else if(type == AreaE::CAVE) {
        return "Cave";
    }else if(type == AreaE::ICE_CAVE) {
        return "Ice-Cave";
    }
}

AreaE Area::getType() {
    return type;
}

ofImage& Area::getImage() {
    return areaImage;
}

ofImage& Area::getAreaImageBoundry() {
    return areaImageBoundry;
}

ofImage& Area::getStage() {
    return areaStage;
}

ofSoundPlayer& Area::getMusic() {
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

