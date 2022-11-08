#pragma once

#include "Enemy.h"
#include "Boss.h"
#include "Player.h"
#include "Structure.h"
#include "Boundry.h"

class Area {
public:
    Area(string name, Area *nextArea, string areaImagePath, string areaImageBoundryPath, string areaMusicPath, string areaStagePath, string areaImageAmbiance, ofPoint entrancePosition, vector<Entity*> entitiesInArea);
    
    bool inBossFight();
    
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
    ofImage getAmbianceImage();
    ofImage getAreaImageBoundry();
    ofSoundPlayer getMusic();
    ofPoint getEntrancePos();
    vector<Entity*> getEntities();
    
    Area *getNextArea();
private:
    string name;
    ofImage areaAmbiance;
    ofImage areaImage;
    ofImage areaImageBoundry;

    ofImage areaStage;
    
    ofSoundPlayer areaMusic;

    Area *nextArea;
    ofPoint entrancePosition;
    
    std::vector<Entity*> entitiesInArea;

    bool bossFightActivated;
};