#pragma once

#include "Enemy.h"
#include "Boss.h"
#include "Player.h"
#include "Rock.h"
#include "OverworldCamera.h"

class Area {
public:
    Area(string name, Area *nextArea, string areaImagePath, string areaMusicPath, string areaStagePath, ofPoint entrancePosition, vector<Entity*> entitiesInArea);
    
    int getRemainingEnemies();
    int getRemainingEntities();
    int getDeadEnemies();
    
    string getName();
    ofImage getImage();
    ofImage getStage();
    ofSoundPlayer getMusic();
    ofPoint getEntrancePos();
    vector<Entity*> getEntities();
    
    Area *getNextArea();
   
    void setName(string name);
    void setEntities(std::vector<Entity*> entitiesInArea);

    void increaseDeadEnemyCount();

    void resetEnemies();
    void clearAllEntities();

private:
    string name;
    ofImage areaImage;
    ofImage areaStage;
    ofSoundPlayer areaMusic;

    Area *nextArea;
    ofPoint entrancePosition;
    
    std::vector<Entity*> entitiesInArea;

    int deadEnemies;
};