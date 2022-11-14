#pragma once

#include "Enemy.h"
#include "Boss.h"
#include "Player.h"
#include "Structure.h"

enum AreaE {
    CAVE,
    FOREST,
    ICE_CAVE
};

class Area {
public:
    Area(AreaE type, Area *nextArea, string areaImagePath, string areaImageBoundryPath, string areaMusicPath, string areaStagePath, ofPoint entrancePosition, vector<Entity*> entitiesInArea);
    ~Area();
    
    bool inBossFight();
    int getDeadEnemies();
    int getRemainingEnemies();
    int getRemainingEntities();
    
    void setEntities(std::vector<Entity*> entitiesInArea);
    void setDefeatedBoss(bool defeatedBoss);
    void setInBossFight(bool bossFightActivated);

    void resetEnemies();
    void resetContent();
    void clearAllEntities();

    string getName();
    AreaE getType();
    
    ofPoint getEntrancePos();

    ofImage& getImage();
    ofImage& getStage();
    ofImage& getAreaImageBoundry();
    
    ofSoundPlayer& getMusic();
    
    vector<Entity*> getEntities();
    
    Area *getNextArea();
private:
    AreaE type;
    ofImage areaImage;
    ofImage areaImageBoundry;
    ofImage areaStage;
    
    ofSoundPlayer areaMusic;

    Area *nextArea;
    ofPoint entrancePosition;
    
    std::vector<Entity*> entitiesInArea;

    bool bossFightActivated;
};