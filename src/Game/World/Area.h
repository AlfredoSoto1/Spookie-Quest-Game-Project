#pragma once

#include "Enemy.h"
#include "Boss.h"
#include "Player.h"
#include "Rock.h"
#include "OverworldCamera.h"

class Area {
public:
    Area(string name, Area *nextArea, string areaImagePath, string areaMusicPath, string areaStagePath, ofPoint entrancePosition, vector<Entity*> entitiesInArea);
    
    bool inBossFight();
    bool hasDefeatedBoss();
    
    int getRemainingEnemies();
    int getRemainingEntities();
    
    void setName(string name);
    void setEntities(std::vector<Entity*> entitiesInArea);
    void setDefeatedBoss(bool defeatedBoss);
    void setInBossFight(bool bossFightActivated);

    void resetEnemies();
    void clearAllEntities();

    string getName();
    ofImage getImage();
    ofImage getStage();
    ofSoundPlayer getMusic();
    ofPoint getEntrancePos();
    vector<Entity*> getEntities();
    
    Area *getNextArea();
private:
    string name;
    ofImage areaImage;
    ofImage areaStage;
    ofSoundPlayer areaMusic;

    Area *nextArea;
    ofPoint entrancePosition;
    
    std::vector<Entity*> entitiesInArea;

    bool defeatedBoss;
    bool bossFightActivated;
};