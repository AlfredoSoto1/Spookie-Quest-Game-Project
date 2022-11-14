#pragma once

#include "Enemy.h"
#include "Boss.h"
#include "Player.h"
#include "Structure.h"

class Area {
public:
    Area(string name, Area *nextArea, string areaImagePath, string areaImageBoundryPath, string areaMusicPath, string areaStagePath, vector<ofImage> ambianceFrames, ofPoint entrancePosition, vector<Entity*> entitiesInArea);
    ~Area();
    
    bool inBossFight();
    int getDeadEnemies();
    int getRemainingEnemies();
    int getRemainingEntities();
    
    void setName(string name);
    void setEntities(std::vector<Entity*> entitiesInArea);
    void setDefeatedBoss(bool defeatedBoss);
    void setInBossFight(bool bossFightActivated);

    void resetEnemies();
    void resetContent();
    void clearAllEntities();

    string getName();
    
    ofImage& getImage();
    ofImage& getStage();
    ofImage& getAreaImageBoundry();
    Animation* getAmbianceAnimation();
    
    ofSoundPlayer getMusic();
    ofPoint getEntrancePos();
    
    vector<Entity*> getEntities();
    
    Area *getNextArea();
private:
    string name;
    ofImage areaImage;
    ofImage areaImageBoundry;
    ofImage areaStage;
    Animation* ambianceAnimation;
    
    ofSoundPlayer areaMusic;

    Area *nextArea;
    ofPoint entrancePosition;
    
    std::vector<Entity*> entitiesInArea;

    bool bossFightActivated;
};