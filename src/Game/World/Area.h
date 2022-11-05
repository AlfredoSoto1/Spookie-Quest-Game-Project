#pragma once

#include "Enemy.h"
#include "OverworldCamera.h"
#include "Player.h"
#include "../Entities/Structures/include/Rock.h"

class Area {
public:
    Area(string name, Area *nextArea, string areaImagePath, string areaMusicPath, string areaStagePath, ofPoint entrancePosition, vector<Entity*> entitiesInArea);
    
    int getRemainingEnemies();
    int getRemainingEntities();
    
    string getName();
    ofImage getImage();
    ofImage getStage();
    ofSoundPlayer getMusic();
    ofPoint getEntrancePos();
    vector<Entity*> getEntities();
    
    Area *getNextArea();
   
    void setName(string name);
    void setEntities(std::vector<Entity*> entitiesInArea);

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
};